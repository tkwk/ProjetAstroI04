#ifndef __BARNESHUT_HPP__
#define __BARNESHUT_HPP__

#include "Universe.hpp"
#include "Octree.hpp"
#include "Scheme.hpp"

class BarnesHut : public Scheme {
    private:
        bool first;
        std::vector<Particule*> parts;
        Octree * tree;
    public:
        BarnesHut() {first=true;tree=NULL;}
        ~BarnesHut() {if(tree!=NULL)delete tree;}
        virtual void universeStep(Universe &);
};

#endif
