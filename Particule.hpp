#ifndef __PARTICULE_HPP__
#define __PARTICULE_HPP__

/*
    Definition d'une particule
*/

#include "Vector.hpp"

const int DIM=3;            //dimension de l'espace

class Particule {
    private:
        int id_;            //identifiant unique de la particule
        static int nid_;;   //nombre d'identifiants

        void genId();
	public:
        Particule(const real &mass = 0.0, const Vector<DIM> &pos =
        Vector<DIM>(), const Vector<DIM> &spd = Vector<DIM>(), const real & rad = -1.0);
		
		real kineticEnergy() const;

		real m;		// Mass of the paticule
		Vector<DIM> r;	// Position of the particule
		Vector<DIM> v;	// Velocity of the particule
		Vector<DIM> f;	// Force felt by the particle
		Vector<DIM> fnext; // Force felt by the particle at time (n+1) -> useful for Leapfrog scheme
        real radius;    // Radius of the particule (usefull for smoothingLength)
        int id() const;

        static real defaultRadius;
};

#endif
