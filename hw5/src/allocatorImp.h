#ifndef HW5_SRC_ALLOCATORIMP_H_
#define HW5_SRC_ALLOCATORIMP_H_

#endif  // HW5_SRC_ALLOCATORIMP_H_
#include <vector>
#include "allocator.h"

template <class T>
T* AllocatorMine<T>::allocate(size_type num) {
  temp = (pointer)(::operator new(num * sizeof(T)));
  toDelete.push_back(temp);
  return temp;
}
template <class T>
void AllocatorMine<T>::construct(pointer current, const T& value) {
  new (current) T(value);
}
template <class T>
void AllocatorMine<T>::deallocate() {
  for (int i = 0; i < toDelete.size(); i++) {
    delete toDelete[i];
  }
  std::vector<pointer> temp;
  toDelete = temp;
}

