#pragma once

#include "FileParsingThread.h"
#include <memory>
#include <list>
#include <mutex>

class ThreadsHolder : public Thread, public FileParsingThread::IObserver
{
private:
	const static int NUMBER_OF_TASK_PROCESSORS_RUN_ATTEMPTS = 10;
	const static int TASK_PROCESSORS_RUN_ATTEMPTS_PERIOD = 500;
	inline const static char* ERROR_DURING_THREAD_RUN = "Error during run thread. Possibly too many threads in system.";
	inline const static char* WILL_BE_SKIPPED = " will be skipped.";

	int mNumberOfThreads;
	list<unique_ptr<FileParsingThread>> mThreadPool;
	mutex mThreadPoolMutex;
	list<string> mInputFiles;
	FileParsingThread::IStorage& mStorage;

	bool startThread(unique_ptr<FileParsingThread>&) const;
	void createAndStartThread();

public:
	ThreadsHolder(const int, list<string>&&, FileParsingThread::IStorage&);

	void preamble() override;
	void onObserve() override;
	bool processing() override;
};