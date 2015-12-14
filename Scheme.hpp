#ifndef __SCHEME_HPP__
#define __SCHEME_HPP__

#include "Universe.hpp"

class Scheme {
	protected:
		double dt;
	public:
		virtual void timeStep(Particule &) const = 0;
        void universeStep(Universe & u) {
            u.gForces();
            for(int i=0; i<u.Particules.size(); i++)
                timeStep((u.Particules)[i]);
        }
};

#endif

