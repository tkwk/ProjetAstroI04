#ifndef __UNIVERSE_HPP__
#define __UNIVERSE_HPP__

#define SCHEME_EULER 		0
#define SCHEME_LEAPFROG 	1

#include <vector>
#include "Particule.hpp"

using namespace std;

class Particule;

class Universe {
	private :
		vector<Particule> Particules;
	public :
        Universe(const vector<Particule> &);
        Universe(const string &);

        void readFromFile(const string &);
        void write(const string &);

		void gForce(Particule &, int options = 0);
        void gForces(int options = 0);
		real potentialEnergy(const Particule &) const;
		real systemEnergy() const;

        const vector<Particule> & particules() const;

        friend class Scheme;
	friend class Leapfrog;
	friend class BarnesHut;
};

#endif

