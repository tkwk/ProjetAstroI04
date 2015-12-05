#include "Euler.hpp"
#include "Universe.hpp"
#include "Particule.hpp"
#include "astro.hpp"

void Euler::timeStep(Particule * p) {
	double dt = this->dt;

	universe.gForce(p);
	for (int d=0; d<DIM; d++) {
		p->v[d] += dt * p->f[d]/p->m;
		p->r[d] += dt * p->v[d];
	}	
}
