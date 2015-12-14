#ifndef __EULER_HPP__
#define __EULER_HPP__

#include "Scheme.hpp"
class Particule;

class Euler : public Scheme {
	public:
		void timeStep(Particule &) const;
};

#endif

