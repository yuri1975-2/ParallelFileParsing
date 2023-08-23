#pragma once

#include "FileParsingThread.h"
#include <fstream>
#include <mutex>

class StorageImplementation : public FileParsingThread::IStorage
{
private:
	ofstream mStorage;
	mutex mStorageMutex;

public:
	StorageImplementation(const string& filename);

	virtual void flush(list<string>&) override;
};