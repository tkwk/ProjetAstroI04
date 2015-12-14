#include "Universe.hpp"
#include <cmath>


Universe::Universe() {}

Universe::Universe(const vector<Particule> &parts) : Particules(parts) {}

void Universe::gForce(Particule & p) {
	int Np = Particules.size();
	int idp = p.id();

		p.f = Vector<DIM>(); 
	
		for (int id=0; id<Np; id++) {
			if (idp != id) 
                	p.f = (p.m * Particules[id].m * (Particules[id].r-p.r).normalized())/(Particules[id].r - p.r).squaredNorm();	
		}
}

void Universe::gForces() {
    for(int i=0; i<Particules.size(); i++)
        gForce(Particules[i]);
}


real Universe::potentialEnergy(const Particule & p) const {
	real res;
	int Np = Particules.size();
	int idp = p.id();

	res = 0.0;
	for (int id=0; id<Np; id++) {
		if (idp != id)
			res += -(p.m * Particules[id].m)/(Particules[id].r - p.r).squaredNorm();
	}
	
	return res;
}


real Universe::systemEnergy() const {
	real res;
	int Np = Particules.size();

	res = 0.0;
	for (int id=0; id<Np; id++) {
		res += this->Particules[id].kineticEnergy() + this->potentialEnergy(Particules[id]);
	}

	return res;
}

const vector<Particule> & Universe::particules() const {return Particules;}

