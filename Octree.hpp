
#ifndef __OCTREE_HPP__
#define __OCTREE_HPP__

#include "Particule.hpp"
#include <vector>


class Octree {
    private:
        double mass_;
        Vector<DIM> pos_;
        double theta_;
        Octree * previous_;
        Octree * children_[8];
        double box_[6];
        double D_;
        bool empty_;
    public:
        double mass() const {return mass_;}
        Vector<DIM> pos() const {return pos_;}

        Octree(double *);
        Octree(const std::vector<Particule> &, double *);
        ~Octree();
        
        bool isLeaf() const;
        void insert(const Particule &);
        void force(const Particule &, Vector<DIM> &) const;

        static double theta;
};


#endif

