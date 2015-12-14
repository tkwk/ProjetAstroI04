#include "Universe.hpp"
#include <cmath>


Universe::Universe() {}

Universe::Universe(const vector<Particule> &parts) : Particules(parts) {}

void Universe::gForce(Particule & p) {
	int Np = Particules.size();
	int idp = p.id();

		p.f = Vector<DIM>(); 
	
		for (int id=0; id<Np; id++) {
			if (idp != id) {
                p.f = (p.m * Particules[id].m * (Particules[id].r-p.r).normalized())/(Particules[id].r - p.r).squaredNorm();
			}
		}
}

void Universe::gForces() {
    for(int i=0; i<Particules.size(); i++)
        gForce(Particules[i]);
}


double Universe::potentialEnergy(const Particule &) const {
	return 0.0;
}


double Universe::totalEnergy(const Particule &) const {
	return 0.0;
}

const vector<Particule> & Universe::particules() const {return Particules;}

