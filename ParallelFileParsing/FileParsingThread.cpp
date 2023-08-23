#include "FileParsingThread.h"
#include <iostream>
#include <exception>

using namespace std;

FileParsingThread::FileParsingThread(const string& filename, IStorage& storage, IObserver& observer) noexcept(false) :
	Thread(WORK_QUANTUM, OVERLOAD_REST_QUANTUM), mIFStream(filename), mStorage(storage), mFilename(filename), mObserver(observer)
{
	if (false == mIFStream.good())
	{
		throw invalid_argument("error opening " + filename);
	}
}

bool FileParsingThread::processing()
{
	string item;
	while (mIFStream >> item)
	{
		mParsedData.emplace_back(move(item));
	}
	return true;
}

void FileParsingThread::postscriptum()
{
	mStorage.flush(mParsedData);

	ostringstream os;
	os << mFilename << SUCCESFULLY_PROCESSED << endl;
	cout << os.str();

	mObserver.onObserve();
}