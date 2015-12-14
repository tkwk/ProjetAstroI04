#ifndef __SCHEME_HPP__
#define __SCHEME_HPP__

#include "Universe.hpp"

class Scheme {
	protected:
		double dt;
	public:
		virtual void timeStep(Particule *) = 0;
};

#endif

