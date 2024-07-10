
#ifndef HW5_SRC_ITERATORS_H_
#define HW5_SRC_ITERATORS_H_

#endif  // HW5_SRC_ITERATORS_H_

#include "iteratorDefault.h"
#include <vector>
template <class NodeAVL>
class IteratorR : Iterator<NodeAVL> {
 public:
  NodeAVL *current;
  std::vector<NodeAVL *> inorder;
  std::vector<NodeAVL *> trace;

  void findNext();
  bool operator==(const IteratorR &other) const;
  bool operator!=(const IteratorR &other) const;
  NodeAVL operator*() const;
  explicit IteratorR(NodeAVL *x) : Iterator<NodeAVL>(nullptr) {
    current = x;
    while (current != nullptr) {
      inorder.push_back(current);
      if (current->right == nullptr) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (!inorder.empty()) {
      current = inorder[inorder.size() - 1];
      trace.push_back(current);
      inorder.pop_back();
    }
  }
  IteratorR &operator++();
  IteratorR &operator++(int);

  IteratorR &operator--(int);
  IteratorR &operator--();
};
