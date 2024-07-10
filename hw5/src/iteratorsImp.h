#ifndef HW5_SRC_ITERATORSIMP_H_
#define HW5_SRC_ITERATORSIMP_H_

#endif  // HW5_SRC_ITERATORSIMP_H_

#include "iterators.h"
template <class NodeAVL>
void IteratorR<NodeAVL>::findNext() {
  ++*(this);
}
template <class NodeAVL>
bool IteratorR<NodeAVL>::operator==(const IteratorR &other) const {
  return current == other.current;
}
template <class NodeAVL>
bool IteratorR<NodeAVL>::operator!=(const IteratorR &other) const {
  return !(*this == other);
}
template <class NodeAVL>
NodeAVL IteratorR<NodeAVL>::operator*() const {
  return *current;
}

template <class NodeAVL>
IteratorR<NodeAVL> &IteratorR<NodeAVL>::operator++() {
  if (inorder.empty()) {
    IteratorR tmp = IteratorR(nullptr);
    *this = tmp;
    return *this;
  }
  current = inorder[inorder.size() - 1];
  trace.push_back(current);
  inorder.pop_back();
  if (current->left != nullptr) {
    NodeAVL *tmp = current->left;
    while (tmp != nullptr) {
      inorder.push_back(tmp);
      tmp = tmp->right;
    }
  }
  return *this;
}
template <class NodeAVL>
IteratorR<NodeAVL> &IteratorR<NodeAVL>::operator++(int) {
  NodeAVL *x = current;
  ++*(this);
  return *this;
}

template <class NodeAVL>
IteratorR<NodeAVL> &IteratorR<NodeAVL>::operator--(int) {
  NodeAVL *x = current;
  --*(this);
  return *this;
}
template <class NodeAVL>
IteratorR<NodeAVL> &IteratorR<NodeAVL>::operator--() {
  current = trace[trace.size() - 2];
  inorder.erase(inorder.begin());
  if (std::find(inorder.begin(), inorder.end(), trace[trace.size() - 1]) ==
      inorder.end()) {
    inorder.push_back(trace[trace.size() - 1]);
  }
  trace.pop_back();
  return *this;
}
template <class NodeAVL>
void Iterator<NodeAVL>::findNext() {
  ++*(this);
}
template <class NodeAVL>
bool Iterator<NodeAVL>::operator==(const Iterator &other) const {
  return current == other.current;
}
template <class NodeAVL>
bool Iterator<NodeAVL>::operator!=(const Iterator &other) const {
  return !(*this == other);
}
template <class NodeAVL>
NodeAVL Iterator<NodeAVL>::operator*() const {
  return *current;
}
template <class NodeAVL>
Iterator<NodeAVL>::Iterator(NodeAVL *x) {
  current = x;
  while (current != nullptr) {
    inorder.push_back(current);
    if (current->left == nullptr) {
      current = current->right;
    } else {
      current = current->left;
    }
  }
  if (!inorder.empty()) {
    current = inorder[inorder.size() - 1];
    trace.push_back(current);
    inorder.pop_back();
  }
}
template <class NodeAVL>
Iterator<NodeAVL> &Iterator<NodeAVL>::operator++() {
  if (inorder.empty()) {
    Iterator tmp = Iterator(nullptr);
    tmp.trace = (*this).trace;
    *this = tmp;
    return *this;
  }
  current = inorder[inorder.size() - 1];
  trace.push_back(current);
  inorder.pop_back();
  if (current->right != nullptr) {
    NodeAVL *tmp = current->right;
    while (tmp != nullptr) {
      inorder.push_back(tmp);
      tmp = tmp->left;
    }
  }
  return *this;
}
template <class NodeAVL>
Iterator<NodeAVL> &Iterator<NodeAVL>::operator++(int) {
  NodeAVL *x = current;
  ++*(this);
  return *this;
}

template <class NodeAVL>
Iterator<NodeAVL> &Iterator<NodeAVL>::operator--(int) {
  NodeAVL *x = current;
  --*(this);
  return *this;
}
template <class NodeAVL>
Iterator<NodeAVL> &Iterator<NodeAVL>::operator--() {
  current = trace[trace.size() - 2];
  if (!inorder.empty()) {
    inorder.erase(inorder.begin());
  }
  if (std::find(inorder.begin(), inorder.end(), trace[trace.size() - 1]) ==
      inorder.end()) {
    inorder.push_back(trace[trace.size() - 1]);
  }
  trace.pop_back();
  return *this;
}
