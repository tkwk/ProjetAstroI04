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
        Universe(const string &);

        void readFromFile(const string &);

		void gForce(Particule &, int options = 0);
        void gForces(int options = 0);
		real potentialEnergy(const Particule &) const;
		real systemEnergy() const;

        const vector<Particule> & particules() const;

        friend class Scheme;
};

#endif

