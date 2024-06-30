#include <iostream>
#include <string>
#include <utility>
#include <sstream>

#include "errors.h"
std::string func(std::string& res, int pos){
    for (int i=0;i<res.size()-1;i++){
        if (res[i]=='{' || res[i] == '}'){
            throw ErrorNumOfArg(__LINE__,__FILE__);
        }
    }
    return res;
}
template <typename T,typename... Args>
std::string func(const std::string& string, int position,const T& arg, const Args&... args) {
    std::basic_ostringstream<char> result;
    bool isBracketsAppear = false;
    for (int i=0;i<string.size();i++){
        if (string[i]=='{'){
            int temp = i;
            isBracketsAppear= true;
            temp+=1;
                std::string digit;
            do {
                if (!std::isdigit(string[temp])) {//Фигурные скобки - зарезервированный символ, если встречаются вне контекста {n} выбрасывать исключение;
                    throw ErrorFormatBrackets(__LINE__, __FILE__);
                }
                digit+=string[temp];
                temp+=1;
            } while (string[temp]!='}');

            try{//Оставил на всякий случай - do-while должен это 100 процентов учитывать (что в скобках число), но пускай будет.
                if (stoi(digit)==(position)) {
                    result << arg;
                    i=temp;
                } else {
                    result<<string[i];
                }
            } catch (std::invalid_argument& e) {
                throw ErrorFormatBrackets(__LINE__, __FILE__);
            }
        } else {
            result<<string[i];
        }
    }
    if (!isBracketsAppear){
        throw ErrorNumOfArg(__LINE__,__FILE__);
    }



    position+=1;
    std::string res = (result.str());
    return func(res,position,args...);
}
template <typename... Args>
std::string format(const std::string& s, const Args&... args)
{
    return func(s,0,args...);
}




