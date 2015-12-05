#ifndef __LEAPFROG_HPP__
#define __LEAPFROG_HPP__

#include "Scheme.hpp"
class Particule;

class Leapfrog : public Scheme {
	public:
		void timeStep(Particule *);
};

#endif
