NEEDS TO BE IMPLEMENTED:

Program retrieving in command line parameters:
1) directory with files to be parsed. The white characters are assumed as items delimiter;
2) file to place results of parsing;
3) number of threads of file parsing. This number shouldn't noticably exceeds number of logical processor cores.


IMPLEMENTATION:

Thread-Java-like class incapsulating work with C++ thread;

FileParsingThread-thread for file parsing. Parse file by means of ifstream >> operator ('cause white characters are delimiters). Define interfaces:
      -IStorage-for synchronous saving of parsing result;
      -IObserver-for notification of current thread completion. Upon completion the new thred
