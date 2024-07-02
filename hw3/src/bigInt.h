#ifndef HW3_SRC_BIGINT_H_
#define HW3_SRC_BIGINT_H_

#endif 

#include "dynamicContainer.h"
#include <cstdint>
#include <iostream>
#include <string>

class BigInt {
private:

  int32_t base = 10;

public:

  DynamicContainer array;

  explicit BigInt(int32_t number) : BigInt(std::to_string(number)){}
  BigInt(const BigInt &other);

  BigInt(BigInt &&other);

  explicit BigInt(std::string str) {
	for (int i = 0; i < str.size(); i++) {
		if (str[str.size() - i - 1] == '-') {
			array.set(i - 1, array[i - 1] * (-1));
			break;
		}
		if (str[str.size() - i - 1] == '+') {
			array.set(i - 1, array[i - 1]);
			break;
		}
		array.add(str[str.size() - i - 1] - '0');
	}
  }
  BigInt abs();
  void clean();
  friend std::ostream &operator<<(std::ostream &os, BigInt &number);

  std::string stringGenerator(int64_t len, char sym);

  BigInt operator+(int32_t number);
  BigInt operator+(BigInt another);

  BigInt operator-(int32_t number);
  BigInt operator-(BigInt another);
  BigInt operator-();

  BigInt operator*(int32_t number);
  BigInt operator*(BigInt const &another);

  int operator[](int64_t place);
  int operator[](int64_t place) const;
  bool operator==(BigInt const &another);
  bool operator>(BigInt const &another);
  bool operator<(BigInt const &another);

  bool operator<=(BigInt const &another);
  bool operator>=(BigInt const &another);
  bool operator!=(BigInt const &another);
  BigInt &operator=(BigInt &&other) noexcept;
  BigInt &operator=(const BigInt &other);
  std::string getNum();
};
