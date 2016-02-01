
#ifndef __OCTREE_HPP__
#define __OCTREE_HPP__

#include "Particule.hpp"
#include <vector>
#include <string>
#include <map>

class Octree {
    private:
        double mass_;
        Vector<DIM> pos_;
        double theta_;
        Octree * previous_;
        Octree * children_[8];
        double box_[6];
        double D_;
        Particule *particule;
        int np;

        static std::map<Particule*,Octree*> partMap;
        static Octree * head;
    public:
        double mass() const {return mass_;}
        Vector<DIM> pos() const {return pos_;}

        Octree(double *);
        Octree(const std::vector<Particule*> &, double *);
        ~Octree();
        
        bool isLeaf() const;
        void insert(Particule *);
        void force(Particule *, Vector<DIM> &) const;
        std::string toString(std::string indent="") const;
        void update(Particule *);
        void update(double, double, const Vector<DIM> &,const Vector<DIM> &);
        void checkChildren();
        void decrement();
        void deletePart(Particule*);
        void remove(double,const Vector<DIM> &);

        static double theta;
};


#endif

