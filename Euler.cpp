#include "Euler.hpp"

void Euler::timeStep(Particule & p) const {
	double dt = this->dt;

	for (int d=0; d<DIM; d++) {
		p.v[d] += dt * p.f[d]/p.m;
		p.r[d] += dt * p.v[d];
        if(!infinite) {
            if(p.r[d] < bounds[2*d]) {
                p.r[d] += 2*(bounds[2*d]-p.r[d]);
                p.v[d] = -p.v[d];
            }
            else if(p.r[d] > bounds[2*d+1]) {
                p.r[d] -= 2*(p.r[d]-bounds[2*d+1]);
                p.v[d] = -p.v[d];
            }
        }
	}	
}
