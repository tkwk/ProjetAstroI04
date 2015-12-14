#ifndef __PARTICULE_HPP__
#define __PARTICULE_HPP__

#include "Vector.hpp"
#include "Universe.hpp"

class Particule {
	public:
		Particule();
		Particule(const real & mass);
		~Particule();
		
		real kineticEnergy();

		real m;		// Mass of the paticule
		Vector<DIM> r;	// Position of the particule
		Vector<DIM> v;	// Velocity of the particule
		Vector<DIM> f;	// Force felt by the particle
		Vector<DIM> fnext; // Force felt by the particle at time (n+1) -> useful for Leapfrog scheme
};

#endif
