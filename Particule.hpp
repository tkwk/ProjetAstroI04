#ifndef __PARTICULE_HPP__
#define __PARTICULE_HPP__

#include "Vector.hpp"

const int DIM=3;

class Particule {
    private:
        int id_;
        static int nid_;;

        void genId();
	public:
        Particule(const real &mass = 0.0, const Vector<DIM> &pos = Vector<DIM>(), const Vector<DIM> &spd = Vector<DIM>());
		
		real kineticEnergy() const;

		real m;		// Mass of the paticule
		Vector<DIM> r;	// Position of the particule
		Vector<DIM> v;	// Velocity of the particule
		Vector<DIM> f;	// Force felt by the particle
		Vector<DIM> fnext; // Force felt by the particle at time (n+1) -> useful for Leapfrog scheme
        int id() const;
};

#endif
