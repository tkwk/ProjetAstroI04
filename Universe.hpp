#ifndef __UNIVERSE_HPP__
#define __UNIVERSE_HPP__

#include <vector>
#include "Particule.hpp"

using namespace std;

class Particule;

class Universe {
	private :
		vector<Particule> Particules;
	public :
		Universe();
        Universe(const vector<Particule> &);
		void gForce(Particule &);
        void gForces();
		real potentialEnergy(const Particule &) const;
		real systemEnergy() const;
        const vector<Particule> & particules() const;

        friend class Scheme;
};

#endif

