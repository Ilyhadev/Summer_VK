#ifndef HW4_SRC_FORMAT_H_
#define HW4_SRC_FORMAT_H_

#endif  // HW4_SRC_FORMAT_H_
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "errors.h"

void checkIfstringValid(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '{') {
      int temp = i + 1;
      do {
        if (!std::isdigit(str[temp])) { // Фигурные скобки - зарезервированный
                                        // символ, если встречаются вне
                                        // контекста {n} выбрасывать исключение;
          throw ErrorFormatBrackets(temp);
        }
        temp += 1;
      } while (str[temp] != '}');
    }
  }
}
std::string func(const std::string &res, int32_t pos) {
  for (int32_t i = 0; i < res.size() - 1; i++) {
    if (res[i] == '{' || res[i] == '}') {
      throw ErrorNumOfArg();
    }
  }
  return res;
}
template <typename T, typename... Args>
std::string func(const std::string &string, int32_t position, const T &arg,
                 const Args &...args) {
  std::basic_ostringstream<char> result;
  bool isBracketsAppear = false;
  for (int32_t i = 0; i < string.size(); i++) {
    if (string[i] == '{') {
      int32_t temp = i;
      isBracketsAppear = true;
      temp += 1;
      std::string digit;
      do {
        if (std::isdigit(string[temp])) {
          digit += string[temp];
        }

        temp += 1;
      } while (string[temp] != '}');

      if (stoi(digit) == (position)) {
        result << arg;
        i = temp;
      } else {
        result << string[i];
      }

    } else {
      result << string[i];
    }
  }
  if (!isBracketsAppear) {
    throw ErrorNumOfArg();
  }

  position += 1;
  std::string res = (result.str());
  return func(res, position, args...);
}
template <typename... Args>
std::string format(const std::string &s, const Args &...args) {
  return func(s, 0, args...);
}
