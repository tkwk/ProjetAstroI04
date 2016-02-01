#ifndef __VISUALISATION_HPP__
#define __VISUALISATION_HPP__

#include <string>
#include "RealTimePlayer.hpp"

class StaticVisualisation {
    public:
    double * shm;
    ~StaticVisualisation() {delete shm;}
    StaticVisualisation(const std::string & fileName) {
        Universe universe(fileName);
        shm = new double[3*universe.particules().size()];
        for(int i=0;i<universe.particules().size();i++) {
            shm[3*i] = universe.particules()[i].r[0];
            shm[3*i+1] = universe.particules()[i].r[1];
            shm[3*i+2] = universe.particules()[i].r[2];
        }
        std::vector<double> size(universe.particules().size());
        for(int i=0;i<universe.particules().size();i++)
            size[i] = 0.1;//universe.particules()[i].radius;
        std::cout << "coucou" << std::endl;
        RealTimePlayer(shm,universe.particules().size(),NULL,size);
        std::cout << "coucou" << std::endl;
    }
};

class MovieVisualisation {

};

#endif
