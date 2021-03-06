#ifndef __PARSERASTRO_HPP__
#define __PARSERASTRO_HPP__

/*
    Parser pour notre programme
*/

#include "Parser.hpp"

std::vector<std::string> list() {
    std::vector<std::string> list_;
    list_.push_back("o");
    list_.push_back("i");
    list_.push_back("p");
    list_.push_back("m");
    list_.push_back("vm");
    list_.push_back("vs");
    return list_;
}
std::vector<int> size() {
    std::vector<int> size_;
    size_.push_back(1);
    size_.push_back(1);
    size_.push_back(1);
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
    optional_.push_back(true);
    optional_.push_back(true);
    optional_.push_back(true);
    return optional_;
}

std::vector <std::string> description() {
    std::vector<std::string> description_;
    description_.push_back("<output file>: specifie le fichier de sortie");
    description_.push_back("<input file>: specifie le fichier de conditions initiales");
    description_.push_back("<input file>: specifie le fichier de parametres");
    description_.push_back("<input file>: specifie le fichier ou enregistrer les positions des particules");
    description_.push_back("<input file>: specifie un fichier temporel a visualiser");
    description_.push_back("<input file>: specifie un fichier de conditions initiales a visualiser");
    return description_;
}



class ParserAstro : public Parser {
    public:
    ParserAstro(char ** argv) : Parser(argv,list(),size(),optional(),description()) {
    }
};

#endif

