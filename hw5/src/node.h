



#ifndef HW5_SRC_NODE_H_
#define HW5_SRC_NODE_H_

#endif  // HW5_SRC_NODE_H_
#include <utility>
template <class Key, class T>
class NodeAVL {
 public:
  std::pair<Key, T> pair;
  int height;
  NodeAVL *right;
  NodeAVL *left;

  explicit NodeAVL(std::pair<Key, T> pair) {
  height = 0;
  this->pair = pair;
  right = nullptr;
  left = nullptr;
  }
};
