#include "Particule.hpp"

int Particule::nid_ = 0;
real Particule::defaultRadius = 0.0;
// Constructors are declared here :

Particule::Particule(const real & mass, const Vector<DIM> &pos, const
Vector<DIM> &spd, const real & rad) : m(mass), r(pos), v(spd), radius(rad) {
    genId();
    if(rad<0.0) radius = Particule::defaultRadius;
}

// Kinetic and Potential energy are calculated here :
real Particule::kineticEnergy() const {
	return 0.5*(this->m)*(this->v.squaredNorm());
}

int Particule::id() const {return id_;}

void Particule::genId() {
    this->id_ = Particule::nid_;
    nid_++;
}

