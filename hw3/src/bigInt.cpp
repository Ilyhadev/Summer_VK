#include <iostream>
#include <string>

#include "bigInt.h"

BigInt::BigInt(const BigInt &other) { array = other.array; }

BigInt::BigInt(BigInt &&other) {
  array = other.array;
  other.array.getElem() = nullptr;
  other.array.currSize = 0;
}

BigInt::BigInt(std::string str) 
}
BigInt BigInt::abs() {
  if (array[array.currSize - 1] < 0) {
    array.set(array.currSize - 1, array[array.currSize - 1] * (-1));
  }
  return *this;
}
void BigInt::clean() {
  for (int i = 0; i < array.currSize; i++) {
    array.set(i, 0);
  }
}
std::ostream &operator<<(std::ostream &os, BigInt &number) {
  for (int i = 0; i < number.array.currSize; i++) {
    os << number.array[number.array.currSize - i - 1];
  }
  return os;
}

std::string BigInt::stringGenerator(int64_t len, char sym) {
  std::string res;
  for (int64_t i = 0; i < len; i++) {
    res += sym;
  }
  return res;
}

BigInt BigInt::operator+(int32_t number) {
  BigInt temp(number);
  return (*this) + temp;
}
BigInt BigInt::operator+(BigInt another) {
  BigInt zero("0");
  // Если слева минус а справа плюс то вычитаем просто
  if ((*this) < zero && another > zero) {
    return another - (*this).abs();
  }
  // Если слева плюс, а справа минус то снова вычитаем
  if ((*this) > zero && another < zero) {
    return (*this) - another.abs();
  }
  // Если оба минуса то складываем, а затем минус
  if ((*this) < zero && another < zero) {
    return -((*this).abs() + another.abs());
  }

  int residual = 0;
  BigInt res(
      stringGenerator(std::max(array.currSize, another.array.currSize), '0'));
  int minSize = std::min(array.currSize, another.array.currSize);
  int maxSize = std::max(array.currSize, another.array.currSize);
  for (int i = 0; i < minSize; i++) {
    res.array.set(i, (array[i] + another.array[i] + residual) % 10);
    residual = (array[i] + another.array[i] + residual) / 10;
  }
  DynamicContainer maxDynamicArray;
  if (array.currSize > another.array.currSize) {
    for (int i = 0; i < array.currSize; i++) {
      maxDynamicArray.add(array[i]);
    }
  } else {
    for (int i = 0; i < another.array.currSize; i++) {
      maxDynamicArray.add(another.array[i]);
    }
  }
  for (int i = minSize; i < maxSize; i++) {
    res.array.set(i, (maxDynamicArray[i] + residual) % 10);
    residual = (maxDynamicArray[i] + residual) / 10;
  }
  if (residual > 0) {
    res.array.add(residual);
  }
  // delete[] zero.array.getElem();
  // delete[] maxDynamicArray.getElem();Удаляя maxDynArr он удалил еще инфу под
  // anotherArr zero.array.add(0); delete[] zero.array.getElem();
  return res;
}

BigInt BigInt::operator-(int32_t number) {
  BigInt temp(number);
  return (*this) - temp;
}
BigInt BigInt::operator-(BigInt another) {
  auto anotherArr = another.array;
  BigInt res(
      stringGenerator(std::max(array.currSize, anotherArr.currSize), '0'));
  int minSize = std::min(array.currSize, anotherArr.currSize);
  int maxSize = std::max(array.currSize, anotherArr.currSize);
  BigInt zero("0");
  if (*this < zero && another > zero) {
    return -((*this).abs() + another);
  }
  // если справа полож а слева отриц работаем как + только с минусом
  if (another < zero && zero < *this) {
    return (*this + another.abs());
  }
  // если справа отриц а слева полож работаем как +
  // если оба минуса то меняем местами в вызове -
  if (zero > another && *this < zero) {
    return (another.abs() - (*this).abs());
  }
  if ((*this).abs() >= another.abs()) {
    for (int i = anotherArr.currSize; i < array.currSize; i++) {
      anotherArr.add(0);
    }
    for (int i = 0; i < maxSize; i++) {
      if (array[i] < anotherArr[i]) {
        array.set(i, base + array[i]);
        array.set(i + 1, array[i + 1] - 1);
      }
      res.array.set(i, array[i] - anotherArr[i]);
    }
    while (res.array[res.array.currSize - 1] == 0) {
      if (res.array.currSize == 1) {
        break;
      }
      res.array.removeFirst();
    }
  } else {
    res = another - *this;
    res.array.set(res.array.currSize - 1,
                  res.array[res.array.currSize - 1] * -1);
  }
  return res;
}
BigInt BigInt::operator-() {
  array.set(array.currSize - 1, array[array.currSize - 1] * -1);
  return *this;
}

BigInt BigInt::operator*(int32_t number) {
  BigInt temp(number);
  return (*this) * temp;
}
BigInt BigInt::operator*(BigInt const &another) {
  auto anotherArr = another.array;
  auto minArr = *this >= another ? anotherArr : array;
  auto maxArr = *this < another ? anotherArr : array;

  BigInt res(stringGenerator(array.currSize * anotherArr.currSize + 1, '0'));
  BigInt buff1(stringGenerator(array.currSize * anotherArr.currSize + 1, '0'));
  BigInt buff2(stringGenerator(array.currSize * anotherArr.currSize + 1, '0'));
  bool flag = true;
  for (int i = 0; i < minArr.currSize; i++) {
    int residual = 0;
    for (int j = 0; j < maxArr.currSize; j++) {
      if (flag) {
        if (j == maxArr.currSize - 1) {
          buff1.array.set(j + i,
                          (::abs(minArr[i]) * ::abs(maxArr[j]) + residual));
          break;
        }
        buff1.array.set(
            j + i, (::abs(minArr[i]) * ::abs(maxArr[j]) + residual) % base);
        residual = (::abs(minArr[i]) * ::abs(maxArr[j]) + residual) / base;
      } else if (!flag) {
        if (j == maxArr.currSize - 1) {
          buff2.array.set(j + i,
                          (::abs(minArr[i]) * ::abs(maxArr[j]) + residual));
          break;
        }
        buff2.array.set(
            j + i, (::abs(minArr[i]) * ::abs(maxArr[j]) + residual) % base);
        residual = (::abs(minArr[i]) * ::abs(maxArr[j]) + residual) / base;
      }
    }

    flag = !flag;
    // std::cout<<buff1<<std::endl;
    res = buff1 + res;
    // std::cout<<buff1<<std::endl;
    buff1.clean();
    res = buff2 + res;
    // std::cout<<buff2<<std::endl;
    buff2.clean();
    // std::cout<<res;
  }
  while (res.array[res.array.currSize - 1] == 0) {
    if (res.array.currSize == 1) {
      break;
    }
    res.array.removeFirst();
  }
  if (array[array.currSize - 1] < 0 ^ anotherArr[anotherArr.currSize - 1] < 0) {
    res.array.set(res.array.currSize - 1,
                  res.array[res.array.currSize - 1] * -1);
  }
  return res;
}

int BigInt::operator[](int64_t place) { return array[place]; }
int BigInt::operator[](int64_t place) const { return array[place]; }
bool BigInt::operator==(BigInt const &another) {
  if (array[array.currSize - 1] < 0 &&
      another[another.array.currSize - 1] > 0) {
    return false;
  } else if (array[array.currSize - 1] > 0 &&
             another[another.array.currSize - 1] < 0) {
    return false;
  } else {
    if (array.currSize > another.array.currSize) {
      return false;
    } else if (array.currSize < another.array.currSize) {
      return false;
    }
    for (int i = array.currSize - 1; i >= 0; i--) {
      if (array[i] != another[i]) {
        return false;
      }
    }
    return true;
  }
}
bool BigInt::operator>(BigInt const &another) {
  if (*this == another) {
    return false;
  }
  if (array[array.currSize - 1] < 0 &&
      another[another.array.currSize - 1] > 0) {
    return false;
  } else if (array[array.currSize - 1] > 0 &&
             another[another.array.currSize - 1] < 0) {
    return true;
  } else if (array[array.currSize - 1] >= 0 &&
             another[another.array.currSize - 1] >= 0) {
    if (array.currSize > another.array.currSize) {
      return true;
    } else if (array.currSize < another.array.currSize) {
      return false;
    }
    for (int i = array.currSize - 1; i >= 0; i--) {
      if (array[i] > another[i]) {
        return true;
      } else if (array[i] < another[i]) {
        return false;
      }
    }
  } else {
    if (array.currSize > another.array.currSize) {
      return false;
    } else if (array.currSize < another.array.currSize) {
      return true;
    }
    for (int i = array.currSize - 1; i >= 0; i--) {
      if (::abs(array[i]) > ::abs(another[i])) {
        return false;
      } else if (::abs(array[i]) < ::abs(another[i])) {
        return true;
      }
    }
  }
}
bool BigInt::operator<(BigInt const &another) {
  if (!(*this == another)) {
    if (!(*this > another)) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool BigInt::operator<=(BigInt const &another) {
  if ((*this == another) || !(*this > another)) {
    return true;
  } else {
    return false;
  }
}
bool BigInt::operator>=(BigInt const &another) {
  if ((*this == another) || !(*this < another)) {
    return true;
  } else {
    return false;
  }
}
bool BigInt::operator!=(BigInt const &another) {
  if (!(*this == another)) {
    return true;
  } else {
    return false;
  }
}
BigInt &BigInt::operator=(BigInt &&other) noexcept {
  if (*this == other)
    return *this;

  array = other.array;
  other.array.getElem() = nullptr;
  other.array.currSize = 0;
  return *this;
};
BigInt &BigInt::operator=(const BigInt &other) {
  if (array.currSize != other.array.currSize) {
    array = other.array;
    array.currSize = other.array.currSize;
  }

  for (int i = 0; i < array.currSize; ++i)
    array.set(i, other.array[i]);

  return *this;
}
std::string BigInt::getNum() {
  std::string out;
  for (int i = array.currSize - 1; i >= 0; i--) {
    out += (std::to_string(array[i]));
  }
  return out;
}
