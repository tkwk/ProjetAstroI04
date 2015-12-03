#include "Particule.hpp"

// Constructors are declared here :
Particule::Particule() : m(0.0) {}

Particule::Particule(const real & mass) : m(mass) {}

// Kinetic and Potential energy are calculated here :
real Particule::kineticEnergy() {
	return 0.5*(this->m)*(this->v.squaredNorm());
}
