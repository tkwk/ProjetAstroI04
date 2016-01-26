#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <vector>
#include <string>
#include <map>

class Parser {
    public:
        Parser(char ** args,const std::vector<std::string> &list, 
            const std::vector<int> &size = std::vector<int>(0),
            const std::vector<bool> &optional = std::vector<bool>(0),
            const std::vector<std::string> &desc = std::vector<std::string>(0),
            bool allowFiles = true);
        std::string help();
        std::vector<std::string> & operator[] (const std::string &);
        bool isPresent(const std::string &);
        bool check() {return check_;}
    protected:
        bool check_;
        bool update();
        
        bool allowFiles_;
        std::vector<std::string> argv_;
        
        std::vector<int> size_;
        std::vector<std::string> list_;
        std::vector<bool> optional_;
        std::vector<std::string> description_;

        std::vector<bool> isPresent_;
        std::map<std::string,std::vector<std::string> > args_;
        std::vector<std::string> fileList_;
};

#endif

