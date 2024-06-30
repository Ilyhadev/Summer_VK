class ErrorFormatBrackets {
private:
    std::string message = "Wrong placement of brackets. Line of source code: ";
    int line_;
    std::string file;
public:
    ErrorFormatBrackets(int line_,std::string file){
        this->line_=line_;
        this->file=std::move(file);
    }
    void showError(){
        std::cout<<message<<line_<<". In file: "<<file<<std::endl;
    }
};

class ErrorNumOfArg {
private:
    std::string message = "Wrong number of arguments in function. Line of source code: ";
    int line_;
    std::string file;
public:
    ErrorNumOfArg(int line_,std::string file){
        this->line_=line_;
        this->file=std::move(file);
    }
    void showError(){
        std::cout<<message<<line_<<". In file: "<<file<<std::endl;
    }
};