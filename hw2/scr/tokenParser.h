#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class TokenParser {
private:
    void generalUnconditionalStart() {  // Функции по умолчанию
        infor = "B" + infor;  // Знак B = begin
    }
    void generalUnconditionalEnd() { infor = infor + "E"; } // E = end
    std::string infor;
    using typeFuncForDigitToken = long long int (*)(long long int);
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

    void SetStartCallback(typeFuncForUnconditionalToken func) {
        funcForUnconditionalTokenStart = func;
        isUnconditionalStartFuncAssigned = true;
    }

    void SetEndCallback(typeFuncForUnconditionalToken func) {
        funcForUnconditionalTokenEnd = func;
        isUnconditionalEndFuncAssigned = true;
    }

    void SetDigitTokenCallback(typeFuncForDigitToken func) {
        isDigitFuncAssigned = true;
        funcForDigitToken = func;
    }

    void SetStringTokenCallback(typeFuncForStringToken func) {
        isStringFuncAssigned = true;
        funcForStringToken = func;
    }

    std::vector<std::string> Parse(const std::string &info) { // Добавил возможность возвращать вектор чтобы на тетстах понять сработали ли нужные функции
        unsigned int begin = 0;
        unsigned int end = 0;
        this->infor = info;
        std::string token;
        uint64_t digInToken = 0;
        std::vector<std::string> output;

        if (isUnconditionalStartFuncAssigned) {  // функция каллбэк в начале
            funcForUnconditionalTokenStart();
        } else {
            generalUnconditionalStart();
        }
        for (int i = 0; i < info.size(); i++) {
            if (info[i] == ' ' || info[i] == '\n' || info[i] == '\t') {
                begin = i + 1;
                if (i + 1 == info.size())
                    token = "";  // Решение бага последнего символа
                for (int j = i + 1; j < info.size(); j++) {
                    if (abs(info[j] - '0') <= 9) {  // Считаем количество цифр
                        digInToken += 1;
                    }
                    if (info[j] == ' ' || info[j] == '\n' || info[j] == '\t') {
                        end = j;
                        token = info.substr(begin, end - begin);
                        i = j - 1;
                        break;
                    }
                }
            }
            if (!std::equal(token.begin(), token.end(),
                            "")) {  // Блок, чтобы вызвать функции по умолчанию/модифицированные
                if (token.size() == digInToken) {
                    if (isDigitFuncAssigned)
                        output.push_back(std::to_string(funcForDigitToken(stoi(token))));  // Если обработчика нет - то и обработки нет
                } else {
                    if (isStringFuncAssigned) output.push_back(funcForStringToken(token));
                }
            }
            digInToken = 0;
        }
        if (isUnconditionalEndFuncAssigned) {  // функция каллбэк в конце
            funcForUnconditionalTokenEnd();
        } else {
            generalUnconditionalEnd();
        }
        return output;
    }

    std::string getInfo(){
        return infor;
    }

};