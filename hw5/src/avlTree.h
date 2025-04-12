
#ifndef HW5_SRC_AVLTREE_H_
#define HW5_SRC_AVLTREE_H_

#endif  // HW5_SRC_AVLTREE_H_
#include <vector>
#include <functional>
#include <memory>
#include <utility>

#include "node.h"
#include "iteratorsImp.h"
#include "allocatorImp.h"
#include "errorNotInMap.h"


template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<NodeAVL<Key, T>>>
class avl {
 public:
  Allocator allocator;
  using iterator = Iterator<NodeAVL<Key, T>>;
  using iteratorR = IteratorR<NodeAVL<Key, T>>;
  Compare compare = Compare();

 public:
  std::vector<NodeAVL<Key, T> *> toVector();
  NodeAVL<Key, T> *base_ = nullptr;
  avl();
  avl(std::initializer_list<std::pair<Key, T>> init);
  iterator begin();
  iterator end();
  iteratorR rbegin();
  iteratorR rend();

 private:
  int heightOfCurrentNode(NodeAVL<Key, T> *n);
  void newHeight(NodeAVL<Key, T> *n);
  NodeAVL<Key, T> *rotateR(NodeAVL<Key, T> *target1);
  NodeAVL<Key, T> *rotateL(NodeAVL<Key, T> *target1);
  int balance(NodeAVL<Key, T> *n);
  NodeAVL<Key, T> *balancingTree(NodeAVL<Key, T> *n);

 public:
  iterator erase(iterator iterator1);
  NodeAVL<Key, T> *getMax();
  void insert(const std::pair<Key, T> pair);
  NodeAVL<Key, T> *search(Key key);
  T &operator[](Key key);
  int getHeight(NodeAVL<Key, T> *nodeAvl);
  NodeAVL<Key, T> *minValueNode(NodeAVL<Key, T> *node);
  NodeAVL<Key, T> *deleteNode(NodeAVL<Key, T> *base, Key key);

  std::pair<Key, T> at(Key key);
  iterator find(Key key);
  bool contains(Key key);
  bool empty();
  int size();
  void clear();
  ~avl();

 private:
  NodeAVL<Key, T> *recursionForInsert(NodeAVL<Key, T> *base,
                                      std::pair<Key, T> pair);
};

