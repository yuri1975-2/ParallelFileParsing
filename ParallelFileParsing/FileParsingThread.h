#pragma once

#include "Thread.h"
#include <list>
#include <string>
#include <fstream>

class FileParsingThread : public Thread
{
public:
	class IStorage
	{
	public:
		virtual void flush(list<string>&) = 0;

		virtual ~IStorage() {};
	};

	class IObserver
	{
	public:
		virtual void onObserve() = 0;

		virtual ~IObserver() {};
	};

private:
	inline const static char* SUCCESFULLY_PROCESSED = " has succesfully been processed.";
	const static int WORK_QUANTUM = 1000;
	const static int OVERLOAD_REST_QUANTUM = 100;

	ifstream mIFStream;
	string mFilename;
	list<string> mParsedData;
	IStorage& mStorage;
	IObserver& mObserver;

public:
	FileParsingThread(const string& filename, IStorage& storage, IObserver& observer) noexcept(false);

protected:
	bool processing() override;
	void postscriptum() override;
};