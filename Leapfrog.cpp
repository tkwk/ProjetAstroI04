#include "Leapfrog.hpp"
#include "Universe.hpp"
#include "Particule.hpp"

void Leapfrog::universeStep(Universe & u) {
	double dt = this->dt;
	int Np = u.Particules.size();

	for (int p=0; p<Np; p++) {
        Vector<DIM> inter=u.Particules[p].v;
        inter*=dt;
        Vector<DIM> inter2=u.Particules[p].f;
        inter2*=0.5*dt*dt;
        inter2/=u.Particules[p].m;
        inter += inter2;
        u.Particules[p].r += inter;//dt * u.Particules[p].v + 0.5 * dt*dt * u.Particules[p].f/u.Particules[p].m;
        if(!infinite) {
            for(int d=0;d<DIM;d++)
            if(u.Particules[p].r[d] < bounds[2*d]) {
                u.Particules[p].r[d] += 2*(bounds[2*d]-u.Particules[p].r[d]);
                u.Particules[p].v[d] = -u.Particules[p].v[d];
            }
            else if(u.Particules[p].r[d] > bounds[2*d+1]) {
                u.Particules[p].r[d] -= 2*(u.Particules[p].r[d]-bounds[2*d+1]);
                u.Particules[p].v[d] = -u.Particules[p].v[d];
            }
        }
		u.gForce(u.Particules[p] ,SCHEME_LEAPFROG);
        Vector<DIM> moy = u.Particules[p].f;
        moy += u.Particules[p].fnext;
        moy *= 0.5 * dt;
        moy /= u.Particules[p].m;
		u.Particules[p].v += moy;//0.5 * dt * (u.Particules[p].f + u.Particules[p].fnext)/u.Particules[p].m;
		u.Particules[p].f = u.Particules[p].fnext;
	}
}

