#ifndef __PARTICULE_HPP__
#define __PARTICULE_HPP__

#include "Vector.hpp"

const int DIM=2;

class Particule {
    private:
        int id_;
        static int nid_;;

        void genId();
	public:
		Particule();
		Particule(const real &);
        Particule(const real &, const Vector<DIM> &);
        Particule(const real &, const Vector<DIM> &, const Vector<DIM> &);
		~Particule();
		
		real kineticEnergy();

		real m;		// Mass of the paticule
		Vector<DIM> r;	// Position of the particule
		Vector<DIM> v;	// Velocity of the particule
		Vector<DIM> f;	// Force felt by the particle
		Vector<DIM> fnext; // Force felt by the particle at time (n+1) -> useful for Leapfrog scheme
        int id() const;
};

#endif
