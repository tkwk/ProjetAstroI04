
#include "BarnesHut.hpp"


void BarnesHut::universeStep(Universe & u) {
    Octree tree(u.Particules,bounds);
    for(int i=0; i<u.Particules.size(); i++) {
        for(int d=0;d<DIM;d++) u.Particules[i].f[d] = 0.0;
        tree.force(u.Particules[i],u.Particules[i].f);
        u.Particules[i].f *= dt;
        u.Particules[i].f /= u.Particules[i].m;
        u.Particules[i].v += u.Particules[i].f;
        u.Particules[i].r += dt*u.Particules[i].v;
        for(int d=0;d<DIM;d++)
        if(!infinite) {
            if(u.Particules[i].r[d] < bounds[2*d]) {
                u.Particules[i].r[d] += 2*(bounds[2*d]-u.Particules[i].r[d]);
                u.Particules[i].v[d] = -u.Particules[i].v[d];
            }
            else if(u.Particules[i].r[d] > bounds[2*d+1]) {
                u.Particules[i].r[d] -= 2*(u.Particules[i].r[d]-bounds[2*d+1]);
                u.Particules[i].v[d] = -u.Particules[i].v[d];
            }
        }
    }
}
