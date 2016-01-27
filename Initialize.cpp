#include "Particule.hpp"
#include <vector>
#include <stdlib.h>

std::vector<Particule> initRandom (int nbParticules, double mass, double* bounds) {
    srand(NULL);
    std::vector<Particule> res(nbParticules);

    for (int i=0; i<nbParticules; i++) {
        double x, y, z;
        x = bounds[0] + (bounds[1] - bounds[0])*(rand()%(100*nbParticules))/(100*nbParticules);
        y = bounds[2] + (bounds[3] - bounds[2])*(rand()%(100*nbParticules))/(100*nbParticules);
        z = bounds[4] + (bounds[5] - bounds[4])*(rand()%(100*nbParticules))/(100*nbParticules);
        Vector<DIM> pos;
        pos[0] = x; pos[1] = y;pos[2] = z;
        Vector<DIM> spd;
        spd[0] = 0.0; pos[1] = 0.0;pos[2] = 0.0;
        res[i] = Particule(mass,pos,spd);
    }
    return res;
}