#ifndef __PARTICULE_HPP__
#define __PARTICULE_HPP__

#include "Vector.hpp"
#include "Universe.hpp"
#include "Scheme.hpp"

class Particule {
	private:
		real m;		// Mass of the paticule
		Vector<DIM> r;	// Position of the particule
		Vector<DIM> v;	// Velocity of the particule
		Vector<DIM> f;	// Force felt by the particle
	public:
		Particule();
		Particule(const real & mass);
		~Particule();
		
		real kineticEnergy();

		friend class Euler;
};

#endif
