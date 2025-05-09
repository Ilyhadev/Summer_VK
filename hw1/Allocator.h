#include <iostream>
#include <vector>

class Allocator {
 private:
  char *space = nullptr;
  int ptrToBegin = 0;
  long long int _maxSize = 0;

 public:
  void makeAllocator(size_t maxSize) {
    delete[] space;  // cleaning of memory if makeAllocator called next time
    space = new char[maxSize];
    _maxSize = maxSize;
    ptrToBegin = 0;
  }

  char *alloc(size_t size) {
    if (size + ptrToBegin <= _maxSize) {
      char *buffer = space + ptrToBegin;
      ptrToBegin += size;
      return buffer;
    } else {
      return nullptr;
    }
  }

  void reset() { ptrToBegin = 0; }

  int getOffSet() { return ptrToBegin; }

  int getMaxSize() { return _maxSize; }

  ~Allocator() { delete[] space; }  // destructor which deletes allocated memory
};