#include "format.h"

int main() {
    try {
        std::cout<<format("{1}+{1} = {2}", 2,"one");
    }
    catch (ErrorFormatBrackets& error){
        error.showError();
    }
    catch (ErrorNumOfArg& error){
        error.showError();
    }
    return 0;
}


