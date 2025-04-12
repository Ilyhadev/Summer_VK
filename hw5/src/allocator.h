//
// Created by ilia1 on 08.07.2024.
//

#ifndef HW5_SRC_ALLOCATOR_H_
#define HW5_SRC_ALLOCATOR_H_

#endif  // HW5_SRC_ALLOCATOR_H_

#include <vector>
template <typename T>
class AllocatorMine {
 public:
  using size_type = std::size_t;
  typedef T *pointer;
  pointer temp;
  std::vector<pointer> toDelete;
  T *allocate(size_type num);

  void construct(pointer current, const T &value);

  void deallocate();
};
