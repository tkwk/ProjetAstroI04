#include "Universe.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include "Initialize.hpp"


Universe::Universe(const vector<Particule> &parts) : Particules(parts) {gForces();}

Universe::Universe(const string & filename) : Particules() {
    this->readFromFile(filename);
    gForces();
}

void Universe::write(const string & filename) {
    ofstream file(filename.c_str());
    for(int i=0; i<Particules.size(); i++) {
        file << Particules[i].m << " " << Particules[i].r[0] << " " << Particules[i].r[1] << " " << Particules[i].r[2] << " "
                                << " " << Particules[i].v[0] << " " << Particules[i].v[1] << " " << Particules[i].v[2]
                                << " " << Particules[i].radius << std::endl;
    }
    file.close();
}

void Universe::readFromFile(const string & filename) {
    IFile ifile;
    ifile.fileName = filename;
    Particules = ifile.getInit();
}

void Universe::gForce(Particule & p, int options) {
	int Np = Particules.size();

	if (options == SCHEME_EULER) {
		p.f = Vector<DIM>(); 	
		for (int id=0; id<Np; id++) {
			if (p.id() != Particules[id].id()) {
                //real smoothingLength = 0.5*0.69*(p.radius + Particules[id].radius);
                Vector<DIM> force = Particules[id].r;
                force -= p.r;
                double length = force.norm();
                force/=length;
                force*=(p.m*Particules[id].m);
                force/=((length*length)+(epsilon*epsilon));
                p.f += force;
            }
		}
	}
	else if (options == SCHEME_LEAPFROG) {
		p.fnext = Vector<DIM>();
		for (int id=0; id<Np; id++) {
			if (p.id() != Particules[id].id()) {
                //real smoothingLength = 0.5*0.69*(p.radius + Particules[id].radius);
                Vector<DIM> force = Particules[id].r;
                force -= p.r;
                double length = force.norm();
                force/=length;
                force*=(p.m*Particules[id].m);
                force/=((length*length)+(epsilon*epsilon));
                p.fnext += force;
                //p.fnext += (p.m * Particules[id].m * (Particules[id].r-p.r).normalized())/((Particules[id].r - p.r).squaredNorm() + (smoothingLength)*(smoothingLength));
            }
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

