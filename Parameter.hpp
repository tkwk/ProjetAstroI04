
#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <string>
#include <fstream>
#include <sstream>
#include "Initialize.hpp"

struct Parameter {
  Parameter(const std::string &file) {
    init = NULL;
    readFromFile(file);
  }
  ~Parameter() {
    if(init!=NULL)
      delete init;
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
        std::string type;
        sss >> type;
        if (type=="random") {
          IRandom * initR = new IRandom;
          int nbLine = 3;
          std::string line;
          for(int l=0;l<nbLine;l++) {
            getline(file,line);
            std::stringstream ssssi(line);
            ssssi >> line;
            std::stringstream ssss(line);
            std::string leftt;
            std::string rightt;
            getline(ssss,leftt,'=');
            getline(ssss,rightt,'=');
            std::stringstream sssss(rightt);
            if(leftt=="m")
              sssss >> initR->mass;
            else if(leftt=="Np")
              sssss >> initR->nbParticules;
            else if(leftt=="box") {
              for(int j=0;j<3;j++) {
                std::string dimstring;
                getline(sssss,dimstring,'x');
                double dim;
                std::stringstream sts(dimstring);
                sts >> dim;
                initR->bounds[2*j] = -dim/2;
                initR->bounds[2*j+1] = dim/2;
              }
            }
          }
          init = initR;
        }
        else if (type.data()=="galaxy") {
          //init = new IGalaxy;
        }
      }
    }
    file.close();
  }
  double dt;
  double T;
  std::string scheme;
  Init * init;
};

#endif

