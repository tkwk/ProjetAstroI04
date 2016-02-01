#ifndef __BARNESHUT_HPP__
#define __BARNESHUT_HPP__

#include "Universe.hpp"
#include "Octree.hpp"
#include "Scheme.hpp"

class BarnesHut : public Scheme {
    public:
        virtual void universeStep(Universe &);
};

#endif
