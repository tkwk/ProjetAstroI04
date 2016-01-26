
#include "Parser.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>

Parser::Parser(char ** args, const std::vector<std::string> &list, 
                const std::vector<int> & size, 
                const std::vector<bool> &optional,
                const std::vector<std::string>&desc,
                bool allowFiles)
                    : list_(list), description_(list.size()),
                    size_(list.size()), allowFiles_(allowFiles),
                    optional_(list.size()), isPresent_(list.size()) {
    for(int i=0;i<size_.size();i++) size_[i] = -1;
    for(int i=0;i<optional_.size();i++) optional_[i] = true;
    int i=0;
    while(args[i]!=NULL) {
        argv_.push_back(args[i]);
        i++;
    }
    for(int i=0; i<desc.size(); i++)
        description_[i] = desc[i];
    for(int i=0;i<size.size();i++)
        size_[i] = size[i];
    for(int i=0;i<optional.size();i++)
        optional_[i] = optional[i];
    for(int i=0;i<isPresent_.size();i++)
        isPresent_[i] = false;
    update();    
}

bool Parser::isPresent(const std::string &option) {
    std::vector<std::string>::iterator it = find(list_.begin(),list_.end(),option);
    if(it == list_.end())
        return false;
    return isPresent_[it-list_.begin()];
}

std::vector<std::string> & Parser::operator[] (const std::string &opt) {
    return args_[opt];
}

std::string Parser::help() {
    std::stringstream ss("");
    ss << "Options" << std::endl;
    for(int i=0; i<list_.size(); i++) {
        ss << "-" << list_[i] << " " << description_[i] << std::endl;
    }
    return ss.str();
}

bool Parser::update() {
    //on ne lit pas le premier element qui n'est que le nom de l'executable
    int i=1;
    while(i<argv_.size()) {
        //on regarde si on a bien une option
        std::string option = argv_[i];
        if(option[0] != '-') {
            //si ce n'est pas le cas, c'est un fichier d'entrée
            if(!allowFiles_) {
                std::cerr << "Error reading command line options" << std::endl;
                std::cerr << help() << std::endl;
                return false;
            }
            fileList_.push_back(argv_[i]);
            i++;
            continue;
        }
        //sinon on lit les parametres concernant cette option
        std::string opt = option.substr(1);
        //on verifie que l'option existe
        std::vector<std::string>::iterator index = find(list_.begin(),list_.end(),opt);
        if(index == list_.end()) {
            std::cerr << "unknown option: " << option << std::endl;
            std::cerr << help() << std::endl;
            return false;
        }
        int size = size_[index-list_.begin()];
        isPresent_[index-list_.begin()] = true;

        i++;
        std::vector<std::string> arguments;
        int count = 0;
        while(i<argv_.size() && argv_[i][0] != '-' && count != size) {
            arguments.push_back(argv_[i]);
            i++;count++;
        }
        //args_.insert( std::pair<std::string,std::vector<std::string> > (opt,arguments));
        args_[opt] = arguments;
    }
    //on verifie les nombres d'arguments
    for(int i=0;i<list_.size();i++) {
        if(!optional_[i] && !isPresent_[i]) {
            std::cerr << "Missing option -" << list_[i] << std::endl;
            std::cerr << help() << std::endl;
            return false;
        }
        if(size_[i] != -1 && isPresent_[i]) {
            int size = args_[list_[i]].size();
            if(size_[i] != size) {
                std::cerr << "Wrong number of arguments for option -" << list_[i] << std::endl;
                std::cerr << help() << std::endl;
            }
        }
    }
    return true;
}


