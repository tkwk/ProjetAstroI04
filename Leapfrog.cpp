#include "Leapfrog.hpp"
#include "Universe.hpp"
#include "Particule.hpp"

void Leapfrog::universeStep(Universe & u) {
	double dt = this->dt;
	int Np = u.Particules.size();

	for (int p=0; p<Np; p++) {
		u.Particules[p].r = u.Particules[p].r + dt * u.Particules[p].v + 0.5 * dt*dt * u.Particules[p].f/u.Particules[p].m;
		u.gForce(u.Particules[p] ,SCHEME_LEAPFROG);
		u.Particules[p].v = u.Particules[p].v + 0.5 * dt * (u.Particules[p].f + u.Particules[p].fnext)/u.Particules[p].m;
		u.Particules[p].f = u.Particules[p].fnext;
	}
}

