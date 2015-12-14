#include "Particule.hpp"

int Particule::nid_ = 0;
// Constructors are declared here :
Particule::Particule() : m(0.0) {}

Particule::Particule(const real & mass) : m(mass) {}

Particule::Particule(const real & mass, const Vector<DIM> &pos) : m(mass), r(pos) {}

Particule::Particule(const real & mass, const Vector<DIM> &pos, const Vector<DIM> &spd) : m(mass), r(pos), v(spd) {}

// Kinetic and Potential energy are calculated here :
real Particule::kineticEnergy() {
	return 0.5*(this->m)*(this->v.squaredNorm());
}

int Particule::id() const {return id_;}

void Particule::genId() {
    this->id_ = Particule::nid_;
    nid_++;
}
