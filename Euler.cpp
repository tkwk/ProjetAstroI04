#include "Euler.hpp"

void Euler::timeStep(Particule & p) const {
	double dt = this->dt;

	for (int d=0; d<DIM; d++) {
		p.v[d] += dt * p.f[d]/p.m;
		p.r[d] += dt * p.v[d];
	}	
}
