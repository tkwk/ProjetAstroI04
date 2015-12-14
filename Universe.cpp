#include "Universe.hpp"
#include <cmath>
#include <fstream>
#include <sstream>


Universe::Universe(const vector<Particule> &parts) : Particules(parts) {gForces();}

Universe::Universe(const string & filename) : Particules() {
    this->readFromFile(filename);
    gForces();
}

void Universe::readFromFile(const string & filename) {
    ifstream file(filename.c_str());
    string line;
    Particules.resize(0);
    while(getline(file,line)) {
        stringstream ss(line);
        real m, x, y, vx, vy;
        ss >> m >> x >> y >> vx >> vy;
        Vector<DIM> pos, spd;
        pos[0] = x;
        pos[1] = y;
        spd[0] = vx;
        spd[1] = vy;
        Particules.push_back(Particule(m,pos,spd));
    }
    file.close();
}

void Universe::gForce(Particule & p, int options) {
	int Np = Particules.size();

	if (options == SCHEME_EULER) {
		p.f = Vector<DIM>(); 	
		for (int id=0; id<Np; id++) {
			if (p.id() != Particules[id].id()) 
                	p.f = (p.m * Particules[id].m * (Particules[id].r-p.r).normalized())/(Particules[id].r - p.r).squaredNorm();	
		}
	}
	else if (options == SCHEME_LEAPFROG) {
		p.fnext = Vector<DIM>();
		for (int id=0; id<Np; id++) {
			if (p.id() != Particules[id].id())
				p.fnext = (p.m * Particules[id].m * (Particules[id].r-p.r).normalized())/(Particules[id].r - p.r).squaredNorm();
		}
	}

}

void Universe::gForces(int options) {
    for(int i=0; i<Particules.size(); i++)
        gForce(Particules[i], options);
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

