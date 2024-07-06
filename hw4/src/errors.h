#ifndef HW4_SRC_ERRORS_H_
#define HW4_SRC_ERRORS_H_

#endif  // HW4_SRC_ERRORS_H_
#include <cstdint>
#include <string>
#include <utility>
class ErrorFormatBrackets {
 private:
  std::string message = "Wrong placement of brackets. Index in string: ";
  int32_t line_;

 public:
  explicit ErrorFormatBrackets(int32_t line_) { this->line_ = line_; }
  void showError() { std::cout << message << line_ << std::endl; }
};

class ErrorNumOfArg {
 private:
  std::string message = "Wrong number of arguments in function.";

 public:
  ErrorNumOfArg() = default;
  void showError() { std::cout << message << std::endl; }
};
