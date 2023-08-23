// ParallelFileParsing.cpp: определяет точку входа для приложения.
//

#include "ParallelFileParsing.h"
#include "FileParsingThread.h"
#include "StorageImplementation.h"

auto getFileList(string_view directory)
{
	list<string> retValue;

	for (auto& p : directory_iterator(directory))
	{
		if (p.is_regular_file())
		{
			retValue.emplace_back(p.path().string());
		}
	}
		
	return retValue;
}

int main(int count, char** args)
{
	if (count != 4)
	{
		cout << "error program call" << endl;
		cout << "Usage: ParallelFileParsing InputDataDir ResultFile NumberOfParsingThreads" << endl;
		exit(1);
	}

	int threadsNumber(0);
	int threadsNumberAdvise(static_cast<int>(1.5 * thread::hardware_concurrency()));
	if (threadsNumberAdvise < 1)
	{
		threadsNumberAdvise = 1;
	}
	auto [ptr, ec](from_chars(args[3], args[3] + strlen(args[3]), threadsNumber));
	if ((0 == threadsNumber) || (threadsNumber > threadsNumberAdvise))
	{
		cout << "error program call" << endl;
		cout << "improper threads number parameter, should be number from 1 to " << threadsNumberAdvise << endl;
		exit(1);
	}

	StorageImplementation si(args[2]);
	unique_ptr<ThreadsHolder> th(make_unique<ThreadsHolder>(threadsNumber, getFileList(args[1]), si));
	try
	{
		th->start();
		th->join();
	}
	catch (exception&)
	{
		cout << "Error while start processing. Possibly, too many threads in system." << endl;
		cout << "Please, try later." << endl;
		exit(1);
	}

	return 0;
}
