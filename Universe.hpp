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
		double potentialEnergy(const Particule &) const;
		double totalEnergy(const Particule &) const;
};

#endif

