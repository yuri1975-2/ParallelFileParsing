#include "StorageImplementation.h"

StorageImplementation::StorageImplementation(const string& filename) : mStorage(filename)
{
}

void StorageImplementation::flush(list<string>& data)
{
	lock_guard lg(mStorageMutex);
	
	for (auto& item : data)
	{
		mStorage << item << endl;
	}
}
