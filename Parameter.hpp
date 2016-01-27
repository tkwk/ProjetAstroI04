#ifndef __PARAMETER_HPP__
#define __PARAMETER_HPP__

#include <string>
#include <fstream>
#include <sstream>

struct Parameter {
    Parameter(const std::string &);
    void readFromFile(const std::string &);

    double dt;
    double T;
    std::string scheme;
};

Parameter::Parameter(const std::string &filename) {
    readFromFile(filename);
}

void Parameter::readFromFile(const std::string & filename) {
   ifstream file(filename.c_str());
   std::string line;
   while(getline(file,line)) {
        std::stringstream ss(line);
        std::string left, right;
        getline(ss,left,'=');
        getline(ss,right,'=');
        if(left=="dt") {
            stringstream sss(right);
            sss >> dt;
        }
        else if(left=="T") {
            stringstream sss(right);
            sss >> T;
        }
        else if(left=="scheme") {
            stringstream sss(right);
            sss >> scheme;
        }
   }

   file.close();
}

#endif

