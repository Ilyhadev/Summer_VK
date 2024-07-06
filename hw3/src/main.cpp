#include <iostream>
#include <string>

#include "bigInt.h"

int main() {
  BigInt num1("724");
  BigInt num2("55");

  num1 = num1 + num2;
  std::cout << num1 << std::endl;
  std::cout << num1.getNum();

  return 0;
}
