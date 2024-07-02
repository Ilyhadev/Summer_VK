#ifndef HW2_SRC_TOKENPARSER_H_
#define HW2_SRC_TOKENPARSER_H_

#endif  // HW2_SRC_TOKENPARSER_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
class TokenParser {
 private:
    void generalUnconditionalStart();
    void generalUnconditionalEnd();
    std::string infor;
    using typeFuncForDigitToken = int64_t  (*)(int64_t );
    using typeFuncForStringToken = std::string (*)(std::string);
    using typeFuncForUnconditionalToken = void (*)();
    typeFuncForUnconditionalToken funcForUnconditionalTokenEnd;
    typeFuncForUnconditionalToken funcForUnconditionalTokenStart;
    typeFuncForDigitToken funcForDigitToken;
    typeFuncForStringToken funcForStringToken;
    bool isDigitFuncAssigned = false;
    bool isStringFuncAssigned = false;
    bool isUnconditionalStartFuncAssigned = false;
    bool isUnconditionalEndFuncAssigned = false;

 public:
    TokenParser() = default;

    void SetStartCallback(typeFuncForUnconditionalToken func);

    void SetEndCallback(typeFuncForUnconditionalToken func);

    void SetDigitTokenCallback(typeFuncForDigitToken func);

    void SetStringTokenCallback(typeFuncForStringToken func);

    std::vector<std::string> Parse(const std::string &info);

    std::string getInfo();
};
