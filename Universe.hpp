#ifndef __UNIVERSE_HPP__
#define __UNIVERSE_HPP__

#include <vector>
using namespace std;


const int DIM = 2;
const int N_PARTICULES = 10;

class Particule;


class Universe {
	private :
		int N_particules;
		vector<Particule *> Particules;
	public :
		Universe();
		void gForce(Particule *);
		double potentialEnergy(const Particule *);
		double totalEnergy(const Particule *);
};

#endif

