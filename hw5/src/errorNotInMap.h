
#ifndef HW5_SRC_ERRORNOTINMAP_H_
#define HW5_SRC_ERRORNOTINMAP_H_

#endif  // HW5_SRC_ERRORNOTINMAP_H_
#include <iostream>
#include <string>
class errorNotInMap {
  std::string message = "Key wasn't found in map";

 public:
  errorNotInMap() = default;
  void showMessage() { std::cout << message << std::endl; }
};
