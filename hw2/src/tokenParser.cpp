#include <utility>

#include "tokenParser.h"

void TokenParser::generalUnconditionalStart(
    const std::string &infor) {  // Функции по умолчанию
  const_cast<std::string &>(infor) = "B" + infor;  // Знак B = begin
}
void TokenParser::generalUnconditionalEnd(const std::string &infor) {
  const_cast<std::string &>(infor) = infor + "E";
}  // E = end

void TokenParser::SetStartCallback(std::function<void(std::string &)> func) {
  funcForUnconditionalTokenStart = std::move(func);
  isUnconditionalStartFuncAssigned = true;
}

void TokenParser::SetEndCallback(std::function<void(std::string &)> func) {
  funcForUnconditionalTokenEnd = std::move(func);
  isUnconditionalEndFuncAssigned = true;
}

void TokenParser::SetDigitTokenCallback(
    std::function<void(std::string &, int begin, int end)> func) {
  isDigitFuncAssigned = true;
  funcForDigitToken = std::move(func);
}

void TokenParser::SetStringTokenCallback(
    std::function<void(std::string &, int begin, int end)> func) {
  isStringFuncAssigned = true;
  funcForStringToken = std::move(func);
}

void TokenParser::Parse(
    const std::string &info) {  // Добавил возможность возвращать вектор чтобы
  // на тетстах понять сработали ли нужные функции
  unsigned int begin = 0;
  unsigned int end = 0;
  // std::string token;
  uint64_t digInToken = 0;

  if (isUnconditionalStartFuncAssigned) {  // функция каллбэк в начале
    funcForUnconditionalTokenStart(const_cast<std::string &>(info));
  } else {
    generalUnconditionalStart(const_cast<std::string &>(info));
  }
  for (int i = 0; i < info.size(); i++) {
    if (info[i] == ' ' || info[i] == '\n' || info[i] == '\t') {
      begin = i + 1;
      // if (i + 1 == info.size()) token = "";  // Решение бага последнего
      // символа

      for (int j = i + 1; j < info.size(); j++) {
        if (abs(info[j] - '0') <= 9) {  // Считаем количество цифр
          digInToken += 1;
        }
        if (info[j] == ' ' || info[j] == '\n' || info[j] == '\t') {
          end = j;
          // token = info.substr(begin, end - begin);
          i = j - 1;
          break;
        }
      }
    }
    if (begin > end) {
      break;
    }
    if (begin !=
        end) {  // Блок, чтобы вызвать функции по умолчанию/модифицированные
      if (end - begin == digInToken) {
        if (isDigitFuncAssigned) {
          ((funcForDigitToken(
              const_cast<std::string &>(info), begin,
              end)));  // Если обработчика нет - то и обработки нет
          begin = end;
        }
      } else {
        if (isStringFuncAssigned)
          (funcForStringToken(const_cast<std::string &>(info), begin, end));
        begin = end;
      }
    }
    digInToken = 0;
  }
  if (isUnconditionalEndFuncAssigned) {  // функция каллбэк в конце
    funcForUnconditionalTokenEnd(const_cast<std::string &>(info));
  } else {
    generalUnconditionalEnd(const_cast<std::string &>(info));
  }
}
