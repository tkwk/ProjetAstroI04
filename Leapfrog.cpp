#include "Leapfrog.hpp"
#include "Universe.hpp"
#include "Particule.hpp"
#include "astro.hpp"


void Leapfrog::timeStep(Particule * p) {
	double dt = this->dt;
	
	for (int d=0; d<DIM; d++) p->r[d] += dt * p->v[d] + 0.5 * dt*dt * p->f[d]/p->m;
	
	universe.gForce(p);
	for (int d=0; d<DIM; d++) p->v[d] += 0.5 * dt * (p->f[d] + p->fnext[d])/p->m;
}

