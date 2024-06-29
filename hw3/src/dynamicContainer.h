class DynamicContainer {
 private:
  long long int sizeofArr = 1;
  std::shared_ptr<int[]> elem = std::shared_ptr<int[]>(new int[sizeofArr]);
  bool isDeleted;

 public:
  long long int currSize = 0;
  DynamicContainer() {
    sizeofArr = 1;
    currSize = 0;
    isDeleted = false;
    elem = std::shared_ptr<int[]>(new int[sizeofArr]);
  }
  void add(int number) {
    if (sizeofArr > currSize) {
      elem[currSize] = number;
      currSize += 1;
    } else {
      int* tempArr = new int[sizeofArr * 2];
      for (int i = 0; i < sizeofArr; i++) {
        tempArr[i] = elem[i];
      }

      elem = std::shared_ptr<int[]>(new int[sizeofArr * 2]);
      for (int i = 0; i < sizeofArr; i++) {
        elem[i] = tempArr[i];
      }
      delete[] tempArr;
      sizeofArr *= 2;
      add(number);
    }
  }
  int operator[](long long int place) {
    if (place < currSize) {
      return elem[place];
    } else {
      return 100500;
    }
  }
  int operator[](long long int place) const {
    if (place < currSize) {
      return elem[place];
    } else {
      return 100500;
    }
  }

  void set(long long int place, int number) {
    if (place < sizeofArr) {
      elem[place] = number;
    }
  }
  DynamicContainer abs() {
    if (elem[currSize - 1] < 0) {
      elem[currSize - 1] *= (-1);
    }
    return *this;
  }
  void removeFirst() {
    // std::copy(elem,elem+currSize-1,elem);
    elem[currSize - 1] = 0;
    currSize -= 1;
  }
  std::shared_ptr<int[]> getElem() { return elem; }
  ~DynamicContainer() {}
};