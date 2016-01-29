#ifndef __SCHEME_HPP__
#define __SCHEME_HPP__

#include "Universe.hpp"

class Scheme {
	protected:
	public:
		double dt;
        bool infinite;
        double bounds[16];
		virtual void timeStep(Particule &) const {}
        virtual void universeStep(Universe & u) {
            u.gForces();
            for(int i=0; i<u.Particules.size(); i++)
                timeStep((u.Particules)[i]);
        }
};

#endif

