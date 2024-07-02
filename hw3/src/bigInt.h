#include "dynamicContainer.h"
#include <cstdint>
#include <iostream>
#include <string>

class BigInt {
private:
  long int base = 10;

public:
  DynamicContainer array;

  explicit BigInt(int32_t number) : BigInt(std::to_string(number)){};
  BigInt(const BigInt &other);

  BigInt(BigInt &&other);

  BigInt(std::string str);
  BigInt abs();
  void clean();
  friend std::ostream &operator<<(std::ostream &os, BigInt &number);

  std::string stringGenerator(long long int len, char sym);

  BigInt operator+(int32_t number);
  BigInt operator+(BigInt another);

  BigInt operator-(int32_t number);
  BigInt operator-(BigInt another);
  BigInt operator-();

  BigInt operator*(int32_t number);
  BigInt operator*(BigInt const &another);

  int operator[](long long int place);
  int operator[](long long int place) const;
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