
#ifndef HW5_SRC_ITERATORDEFAULT_H_
#define HW5_SRC_ITERATORDEFAULT_H_

#endif  // HW5_SRC_ITERATORDEFAULT_H_
#include <algorithm>
#include <cstdlib>
#include <vector>

template <typename NodeAVL>
class Iterator : public std::iterator<std::forward_iterator_tag, NodeAVL> {
 public:
  NodeAVL *current;
  std::vector<NodeAVL *> inorder;
  std::vector<NodeAVL *> trace;

  void findNext();
  bool operator==(const Iterator &other) const;
  bool operator!=(const Iterator &other) const;
  NodeAVL operator*() const;
  explicit Iterator(NodeAVL *x);
  Iterator &operator++();
  Iterator &operator++(int);

  Iterator &operator--(int);
  Iterator &operator--();
};
