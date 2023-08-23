NEEDS TO BE IMPLEMENTED:

Program retrieving in command line parameters:
1) directory with files to be parsed. The white characters are assumed as items delimiter;
2) file to place results of parsing;
3) number of threads of file parsing. This number shouldn't noticably exceeds number of logical processor cores.


IMPLEMENTATION:

Thread-Java-like class incapsulating work with C++ thread;

FileParsingThread class-thread for file parsing. Parse file by means of ifstream >> operator ('cause white characters are delimiters). Declares interfaces:
      -IStorage-for synchronous saving of parsing result;
      -IObserver-for notification of current thread completion.
Upon completion thread by means of IObserver implementation creates new thread processing a new file.

StorageImplementation class-implementation of FileParsingThread::IStorage interface.

ThreadsHolder class-maintains pool of currently active file parsing threads and synchronizes execution of main thread with them. Also implements FileParsingThread::IObserver.

ParallelFileParsing-module contained entry point.
