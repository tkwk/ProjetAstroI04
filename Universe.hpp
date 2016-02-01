#ifndef __UNIVERSE_HPP__
#define __UNIVERSE_HPP__

/*
    Classe decrivant les caracteristiques de l'unviers dans lequel se deroule la
    simulation
*/

#define SCHEME_EULER 		0
#define SCHEME_LEAPFROG 	1

#include <vector>
#include "Particule.hpp"

using namespace std;

class Particule;

class Universe {
	private :
		vector<Particule> Particules;                   //liste des particules
	public :
        double epsilon;                                 //smoothingLength

        Universe(const vector<Particule> &);
        Universe(const string &);

        void readFromFile(const string &);
        void write(const string &);                     //backup de la positions des particules dans un fichier

		void gForce(Particule &, int options = 0);      //calcul de la force appliquee a une particule
        void gForces(int options = 0);                  //calcul de toutes les forces
		real potentialEnergy(const Particule &) const;  //calcul de l'enrgie potentielle d'une particule
		real systemEnergy() const;                      //Energie totale

        const vector<Particule> & particules() const;  

        friend class Scheme;
	friend class Leapfrog;
	friend class BarnesHut;
};

#endif

