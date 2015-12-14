#include "Particule.hpp"

int Particule::nid_ = 0;
// Constructors are declared here :

Particule::Particule(const real & mass, const Vector<DIM> &pos, const Vector<DIM> &spd) : m(mass), r(pos), v(spd) {genId();}

// Kinetic and Potential energy are calculated here :
real Particule::kineticEnergy() {
	return 0.5*(this->m)*(this->v.squaredNorm());
}

int Particule::id() const {return id_;}

void Particule::genId() {
    this->id_ = Particule::nid_;
    nid_++;
}

