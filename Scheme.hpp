#ifndef __SCHEME_HPP__
#define __SCHEME_HPP__

/* 
    classe virtuelle décrivant un schéma numérique
*/

#include "Universe.hpp"

class Scheme {
	protected:
	public:
		double dt;                                      // pas de temps
        bool infinite;                                  // univers fini ou infini (les particules rebondissent sur les parois si l'univers est fini)
        double bounds[6];                               // boite contenant l'univers dans le cas d'un monde fini
		virtual void timeStep(Particule &) const {}     // pas de temps d'une particule
        virtual void universeStep(Universe & u) {       // pas de temps sur tout l'univers
            u.gForces();
            for(int i=0; i<u.Particules.size(); i++)
                timeStep((u.Particules)[i]);
        }
};

#endif

