#ifndef __UNIVERSE_HPP__
#define __UNIVERSE_HPP__

const int DIM = 2;
const int N_PARTICULES = 10;

class Particule;


class Universe {
	public :
		Universe();
		void gForce(Particule *);
		double potentialEnergy(const Particule *);
		double totalEnergy(const Particule *);
};

#endif

