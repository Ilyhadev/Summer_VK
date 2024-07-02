#ifndef HW3_SRC_DYNAMICCONTAINER_H_
#define HW3_SRC_DYNAMICCONTAINER_H_

#endif
#include <memory>
class DynamicContainer {
private:

  int64_t sizeofArr = 1;
  std::shared_ptr<int[]> elem = std::shared_ptr<int[]>(new int[sizeofArr]);
  bool isDeleted;

public:

  int64_t currSize = 0;
  DynamicContainer();
  void add(int number);
  int operator[](int64_t place);
  int operator[](int64_t place) const;

  void set(int64_t place, int number);
  DynamicContainer abs();
  void removeFirst();
  std::shared_ptr<int[]> getElem();
};
