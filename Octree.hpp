
#ifndef __OCTREE_HPP__
#define __OCTREE_HPP__

/*
    Classe decrivant les octrees utiles pour Barnes-Hut
*/

#include "Particule.hpp"
#include <vector>
#include <string>
#include <map>

//Un objet Octree represente un noeud de l'arbre
class Octree {
    private:

        double mass_;       //masse de la cellule
        Vector<DIM> pos_;   //position du centre de masse

        Octree * previous_;     //noeud parent
        Octree * children_[8];  //les 8 enfants

        double box_[6];         //dimensions de la cellule
        double D_;              //taille de la cellule

        int np;                 //nombre de particules dans la cellule
        Particule *particule;   //pointeur sur la particule contenu dans le cas ou np==1

        static std::map<Particule*,Octree*> partMap;        //table d'association particule->noeud contenant la particule
        static Octree * head;                               //tete de l'arbre
    public:
        double mass() const {return mass_;}
        Vector<DIM> pos() const {return pos_;}

        Octree(double *);                                       //construction d'un noeud (parametre: dimensions de la cellule)
        Octree(const std::vector<Particule*> &, double *);      //construction de l'arbre (parametere: liste de particules, dimension de l'univers)
        ~Octree();
        
        bool isLeaf() const;                                    //suis-je une feuille ?
        void insert(Particule *);                               //insertion d'un particule
        void force(Particule *, Vector<DIM> &) const;           //calcul de la force appliquee a une particule (on accumule le resultat dans le dernier parametre)

        std::string toString(std::string indent="") const;

        // ======================= fonction pour updater l'arbre ==================
        //                    (plutot que le reconstruire a chaque pas)
        //                      Ne fonctionne pas !
        void update(Particule *);
        void update(double, double, const Vector<DIM> &,const Vector<DIM> &);
        void checkChildren();
        void decrement();
        void deletePart(Particule*);
        void remove(double,const Vector<DIM> &);
        // ========================================================================

        static double theta;                                // parametre theta de la simulation
};


#endif

