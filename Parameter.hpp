
#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <string>
#include <fstream>
#include <sstream>

struct Parameter {
    Parameter(const std::string &file) {
        readFromFile(file);
    }
    void readFromFile(const std::string &filename) {
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
						else if(left=="init") {
								stringstream sss(right);
								sss >> init;
						}
						else if(left=="Np") {
								stringstream sss(right);
								sss >> Np;
						}
						else if(left=="m") {
								stringstream sss(right);
								sss >> m;
						}
        }
        
        file.close();
    }
    double dt;
    double T;
    std::string scheme;
		std::string init;
		int Np;
		double m;
};

#endif

