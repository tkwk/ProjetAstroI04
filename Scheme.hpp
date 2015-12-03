#ifndef __SCHEME_HPP__
#define __SCHEME_HPP__

#include "Particule.hpp"

class Scheme {
	private:
		timeStep dt;
	public:
		virtual void timeStep(const Particule &) = 0;
};

#endif

