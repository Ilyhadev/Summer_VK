
#ifndef HW2_SRC_TOKENPARSER_H_
#define HW2_SRC_TOKENPARSER_H_

#endif  // HW2_SRC_TOKENPARSER_H_

#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
class TokenParser {
 private:
  void generalUnconditionalStart(const std::string& infor);
  void generalUnconditionalEnd(const std::string& infor);
  std::function<void(std::string&, int begin, int end)> funcForDigitToken;
  std::function<void(std::string&, int begin, int end)> funcForStringToken;
  std::function<void(std::string&)> funcForUnconditionalTokenStart;
  std::function<void(std::string&)> funcForUnconditionalTokenEnd;
  bool isDigitFuncAssigned = false;
  bool isStringFuncAssigned = false;
  bool isUnconditionalStartFuncAssigned = false;
  bool isUnconditionalEndFuncAssigned = false;

 public:
  TokenParser() = default;

  void SetStartCallback(std::function<void(std::string&)> func);

  void SetEndCallback(std::function<void(std::string&)> func);

  void SetDigitTokenCallback(
      std::function<void(std::string&, int begin, int end)> func);

  void SetStringTokenCallback(
      std::function<void(std::string&, int begin, int end)> func);

  void Parse(const std::string& info);
};
