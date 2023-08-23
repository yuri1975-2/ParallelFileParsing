#include "ThreadsHolder.h"

ThreadsHolder::ThreadsHolder(const int numberOfThreads, list<string>&& inputFiles, FileParsingThread::IStorage& storage) : 
	mNumberOfThreads((numberOfThreads <= inputFiles.size()) ? numberOfThreads : static_cast<int>(inputFiles.size())),
	mInputFiles(forward<list<string>>(inputFiles)), mStorage(storage)
{
}

bool ThreadsHolder::startThread(unique_ptr<FileParsingThread>& thread) const
{
	if (nullptr == thread)
	{
		return false;
	}
	
	// run thread (possibly, with several attempts, if we'd faced with error of launch)
	// this paranoic additional attempts-subject to discuss
	auto isRunError(false);
	auto numberOfAttempts(0);
	for (;;)
	{
		try
		{
			if (false == thread->isRun())
			{
				thread->start();
			}
		}
		catch (exception&)
		{
			isRunError = true;
		}

		if ((isRunError) && (numberOfAttempts < NUMBER_OF_TASK_PROCESSORS_RUN_ATTEMPTS))
		{
			// not all processor thread has been run, try again after while
			this_thread::sleep_for(chrono::milliseconds(TASK_PROCESSORS_RUN_ATTEMPTS_PERIOD));
			++numberOfAttempts;
		}
		else
		{
			break;
		}
	}

	return !isRunError;
}

void ThreadsHolder::createAndStartThread()
{
	if (mInputFiles.empty())
	{
		return;
	}

	lock_guard<mutex> lg(mThreadPoolMutex);
	
	auto filename(move(mInputFiles.front()));
	mInputFiles.pop_front();

	unique_ptr<FileParsingThread> fpt(nullptr);
	try
	{
		fpt = make_unique<FileParsingThread>(filename, mStorage, *this);
	}
	catch (exception& e)
	{
		ostringstream os;
		os << e.what() << endl;
		cout << os.str();
		return;
	}

	if (startThread(fpt))
	{
		mThreadPool.push_back(move(fpt));
	}
	else
	{
		ostringstream os;
		os << ERROR_DURING_THREAD_RUN << endl;
		os << filename << WILL_BE_SKIPPED << endl;
		cout << os.str();
	}
}

void ThreadsHolder::preamble()
{
	for (auto i(0); i < mNumberOfThreads; ++i)
	{
		createAndStartThread();
	}
}

void ThreadsHolder::onObserve()
{
	createAndStartThread();
}

bool ThreadsHolder::processing()
{
	unique_ptr<FileParsingThread> fpt;

	{
		lock_guard<mutex> lg(mThreadPoolMutex);
		if (mThreadPool.empty())
		{
			return true;
		}
		else
		{
			fpt = move(mThreadPool.front());
			mThreadPool.pop_front();
		}
	}

	fpt->join();	
	return false;
}

