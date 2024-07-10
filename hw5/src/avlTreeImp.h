#ifndef HW5_SRC_AVLTREEIMP_H_
#define HW5_SRC_AVLTREEIMP_H_

#endif  // HW5_SRC_AVLTREEIMP_H_
#include "avlTree.h"


#include <vector>
#include <algorithm>
#include <utility>

template <class Key, class T>
using iterator = Iterator<NodeAVL<Key, T>>;
template <class Key, class T>
using iteratorR = IteratorR<NodeAVL<Key, T>>;

template <class Key, class T, class Compare, class Allocator>
std::vector<NodeAVL<Key, T> *> avl<Key, T, Compare, Allocator>::toVector() {
  iterator iterator(base_);
  std::vector<NodeAVL<Key, T> *> temp1;
  temp1.push_back(iterator.current);
  while (((iterator)).current != NULL) {
    auto temp = (++(iterator)).current;
    if (temp != NULL) {
      temp1.push_back(temp);
    }
  }
  return temp1;
}
template <class Key, class T, class Compare, class Allocator>
avl<Key, T, Compare, Allocator>::avl() {
  base_ = nullptr;
}
template <class Key, class T, class Compare, class Allocator>
avl<Key, T, Compare, Allocator>::avl(
    std::initializer_list<std::pair<Key, T>> init) {
  auto end = init.end();
  auto it = init.begin();

  for (size_t i = 0; it != end; it++, ++i) {
    insert({it->first, it->second});
  }
}
template <class Key, class T, class Compare, class Allocator>
iterator<Key, T> avl<Key, T, Compare, Allocator>::begin() {
  return iterator(base_);
}
template <class Key, class T, class Compare, class Allocator>
iterator<Key, T> avl<Key, T, Compare, Allocator>::end() {
  iterator itera(base_);
  iterator ans(base_);
  while (((itera).current)!= nullptr) {
    auto temp = ((itera++).current);
    if (temp != NULL) {
      ans = itera;
    }
  }
  return (ans++);
}
template <class Key, class T, class Compare, class Allocator>
iteratorR<Key, T> avl<Key, T, Compare, Allocator>::rbegin() {
  return iteratorR(base_);
}
template <class Key, class T, class Compare, class Allocator>
iteratorR<Key, T> avl<Key, T, Compare, Allocator>::rend() {
  return iteratorR(getMax())++;
}

template <class Key, class T, class Compare, class Allocator>
int avl<Key, T, Compare, Allocator>::heightOfCurrentNode(
    NodeAVL<Key, T> *n) {  // helping func to update height of current node
  if (n == nullptr) {
    return -1;
  } else {
    return n->height;
  }
}
template <class Key, class T, class Compare, class Allocator>
void avl<Key, T, Compare, Allocator>::newHeight(
    NodeAVL<Key, T> *n) {  // for AVL implementation updating the
  // height for node
  n->height =
      1 + std::max(heightOfCurrentNode(n->left), heightOfCurrentNode(n->right));
}
template <class Key, class T, class Compare, class Allocator>
NodeAVL<Key, T> *avl<Key, T, Compare, Allocator>::rotateR(
    NodeAVL<Key, T> *target1) {  // rotating right func
  NodeAVL<Key, T> *target2 = target1->left;
  NodeAVL<Key, T> *temp = target2->right;
  target2->right = target1;
  target1->left = temp;
  newHeight(target1);
  newHeight(target2);
  return target2;
}
template <class Key, class T, class Compare, class Allocator>
NodeAVL<Key, T> *avl<Key, T, Compare, Allocator>::rotateL(
    NodeAVL<Key, T> *target1) {  // rotating left func
  NodeAVL<Key, T> *target2 = target1->right;
  NodeAVL<Key, T> *temp = target2->left;
  target2->left = target1;
  target1->right = temp;
  newHeight(target1);
  newHeight(target2);
  return target2;
}
template <class Key, class T, class Compare, class Allocator>
int avl<Key, T, Compare, Allocator>::balance(
    NodeAVL<Key, T> *n) {  // func that returns difference of heights
  // for children of current node
  if (n == nullptr) {
    return 0;
  } else {
    return heightOfCurrentNode(n->right) - heightOfCurrentNode(n->left);
  }
}
template <class Key, class T, class Compare, class Allocator>
NodeAVL<Key, T> *avl<Key, T, Compare, Allocator>::balancingTree(
    NodeAVL<Key, T> *n) {
  if (balance(n) > 1) {  // check where balance is wrong (on right or on left)
    // to make rotations
    if (heightOfCurrentNode(n->right->right) >
        heightOfCurrentNode(n->right->left)) {
      n = rotateL(n);
    } else {
      n->right = rotateR(n->right);
      n = rotateL(n);
    }
  } else if (balance(n) < -1) {
    if (heightOfCurrentNode(n->left->left) >
        heightOfCurrentNode(n->left->right)) {
      n = rotateR(n);
    } else {
      n->left = rotateL(n->left);
      n = rotateR(n);
    }
  }
  return n;
}

template <class Key, class T, class Compare, class Allocator>
iterator<Key, T> avl<Key, T, Compare, Allocator>::erase(iterator iterator1) {
  base_ = deleteNode(base_, iterator1.current->pair.first);
  return iterator(base_);
}
template <class Key, class T, class Compare, class Allocator>
NodeAVL<Key, T> *avl<Key, T, Compare, Allocator>::getMax() {
  NodeAVL<Key, T> *root = base_;
  while (root != nullptr) {
    if (root->right->right == nullptr) {
      root = root->right;
      break;
    }
    root = root->right;
  }
  return root;
}
template <class Key, class T, class Compare, class Allocator>
void avl<Key, T, Compare, Allocator>::insert(
    const std::pair<Key, T> pair) {  // There is function for insertion, that
  // calling recursive go through tree
  base_ = recursionForInsert(base_, pair);
}
template <class Key, class T, class Compare, class Allocator>
NodeAVL<Key, T> *avl<Key, T, Compare, Allocator>::search(
    Key key) {  // func that searches by unique key object in AVLtree (node)
  NodeAVL<Key, T> *root = base_;
  while (root != nullptr) {
    if (root->pair.first == key) {
      break;
    }
    if (root->pair.first < key) {
      root = root->right;
    } else {
      root = root->left;
    }
  }
  return root;
}
template <class Key, class T, class Compare, class Allocator>
T &avl<Key, T, Compare, Allocator>::operator[](Key key) {
  auto node = search(key);
  if (node != nullptr) {
    return search(key)->pair.second;
  } else {
    insert({key, T()});
    return search(key)->pair.second;
  }
}
template <class Key, class T, class Compare, class Allocator>
int avl<Key, T, Compare, Allocator>::getHeight(NodeAVL<Key, T> *nodeAvl) {
  if (nodeAvl == NULL) {
    return 0;
  } else {
    return nodeAvl->height;
  }
}
template <class Key, class T, class Compare, class Allocator>
NodeAVL<Key, T> *avl<Key, T, Compare, Allocator>::minValueNode(
    NodeAVL<Key, T> *node) {
  NodeAVL<Key, T> *current = node;

  while (current->left != nullptr) current = current->left;

  return current;
}
template <class Key, class T, class Compare, class Allocator>
NodeAVL<Key, T> *avl<Key, T, Compare, Allocator>::deleteNode(
    NodeAVL<Key, T> *base, Key key) {
  if (base == nullptr) return base;

  if (compare(key, base->pair.first)) {
    base->left = deleteNode(base->left, key);

  } else if (!compare(key, base->pair.first) && key != base->pair.first) {
    base->right = deleteNode(base->right, key);

  } else {
    if ((base->left == nullptr) || (base->right == nullptr)) {
      NodeAVL<Key, T> *temp = nullptr;
      if (temp == base->left)
        temp = base->right;
      else
        temp = base->left;
      if (temp == nullptr) {
        temp = base;
        base = nullptr;
      } else {
        base = temp;
      }

    } else {
      NodeAVL<Key, T> *temp = minValueNode(base->right);

      base->pair.first = temp->pair.first;

      base->right = deleteNode(base->right, temp->pair.first);
    }
  }

  if (base == nullptr) return base;

  base->height = std::max(getHeight(base->left), getHeight(base->right)) + 1;
  base = balancingTree(base);

  return base;
}
template <class Key, class T, class Compare, class Allocator>
std::pair<Key, T> avl<Key, T, Compare, Allocator>::at(Key key) {
  try {
    if (search(key) != nullptr) {
      return search(key)->pair;
    } else {
      throw errorNotInMap();
    }
  } catch (errorNotInMap error) {
    error.showMessage();
    return {Key(), T()};
  }
}
template <class Key, class T, class Compare, class Allocator>
iterator<Key, T> avl<Key, T, Compare, Allocator>::find(Key key) {
  if (search(key) != nullptr) {
    return iterator(search(key));
  } else {
    return end();
  }
}
template <class Key, class T, class Compare, class Allocator>
bool avl<Key, T, Compare, Allocator>::contains(Key key) {
  if (search(key) == nullptr) {
    return false;
  } else {
    return true;
  }
}
template <class Key, class T, class Compare, class Allocator>
bool avl<Key, T, Compare, Allocator>::empty() {
  if (base_ == NULL) {
    return true;
  } else {
    return false;
  }
}
template <class Key, class T, class Compare, class Allocator>
int avl<Key, T, Compare, Allocator>::size() {
  auto temp = toVector();
  int size = 0;
  for (int i = 0; i < temp.size(); i++) {
    if (temp[i] != NULL) {
      size += 1;
    }
  }
  return size;
}
template <class Key, class T, class Compare, class Allocator>
void avl<Key, T, Compare, Allocator>::clear() {
  allocator.deallocate();
  base_ = nullptr;
}
template <class Key, class T, class Compare, class Allocator>
avl<Key, T, Compare, Allocator>::~avl() {
  allocator.deallocate();
}

template <class Key, class T, class Compare, class Allocator>
NodeAVL<Key, T> *avl<Key, T, Compare, Allocator>::recursionForInsert(
    NodeAVL<Key, T> *base, std::pair<Key, T> pair) {
  if (base == nullptr) {
    auto ptr = allocator.allocate(1);
    allocator.construct(ptr, NodeAVL<Key, T>(pair));
    return ptr;
  }

  if (!compare(base->pair.first,
               (pair.first))) {  // comparing generic values of keys
    base->left = recursionForInsert(base->left, pair);
  }
  if (compare(base->pair.first, (pair.first))) {
    base->right = recursionForInsert(base->right, pair);
  }
  newHeight(base);
  base = balancingTree(base);
  return base;
}

