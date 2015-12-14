#include "Universe.hpp"
#include <cmath>


Universe::Universe() {}


void Universe::gForce(Particule & p) {
	int Np = Particules.size();
	int idp = p.id();

	for (int d=0; d<DIM; d++) {
		p.f[d] = 0.0; 
	
		for (int id=0; id<Np; id++) {
			if (idp != id) {
				p.f[d] += - p.m * Particules[id].m * (p.r[d] - Particules[id].r[d]) / pow((p.r - Particules[id].r).norm(), 3); 
			}
		}
	}	
}


double Universe::potentialEnergy(const Particule &) const {
	return 0.0;
}


double Universe::totalEnergy(const Particule &) const {
	return 0.0;
}
