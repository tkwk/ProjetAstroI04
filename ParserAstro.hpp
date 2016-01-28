#ifndef __PARSERASTRO_HPP__
#define __PARSERASTRO_HPP__

#include "Parser.hpp"

std::vector<std::string> list() {
    std::vector<std::string> list_;
    list_.push_back("o");
    list_.push_back("i");
    list_.push_back("p");
    return list_;
}
std::vector<int> size() {
    std::vector<int> size_;
    size_.push_back(1);
    size_.push_back(1);
    size_.push_back(1);
    return size_;
}

std::vector<bool> optional() {
    std::vector<bool> optional_;
    optional_.push_back(true);
    optional_.push_back(true);
    optional_.push_back(false);
    return optional_;
}

std::vector <std::string> description() {
    std::vector<std::string> description_;
    description_.push_back("<output file>: specifie le fichier de sortie");
    description_.push_back("<input file>: specifie le fichier de conditions initiales");
    description_.push_back("<input file>: specifie le fichier de parametres");
    return description_;
}



class ParserAstro : public Parser {
    public:
    ParserAstro(char ** argv) : Parser(argv,list(),size(),optional(),description()) {
    }
};

#endif

