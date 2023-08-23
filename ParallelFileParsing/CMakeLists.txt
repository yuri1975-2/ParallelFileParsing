# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (ParallelFileParsing "ParallelFileParsing.cpp" "ParallelFileParsing.h" "Thread.h" "Thread.cpp" "FileParsingThread.cpp" "FileParsingThread.h" "StorageImplementation.h" "StorageImplementation.cpp" "ThreadsHolder.cpp" "ThreadsHolder.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
