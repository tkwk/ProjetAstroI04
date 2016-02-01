
#include "Octree.hpp"

double Octree::theta = 0.0;

double min(double x,double y) {return (x<y)?x:y;}

Octree::Octree(double * bounds) : previous_(NULL), empty_(true) {
    for(int i=0;i<6;i++) box_[i] = bounds[i];
    for(int d=0;d<8;d++) children_[d] = NULL;
    double dx = bounds[1] - bounds[0];
    double dy = bounds[3] - bounds[2];
    double dz = bounds[5] - bounds[4];
    D_ = min(dx,min(dy,dz));
}

Octree::Octree(const std::vector<Particule> &particules, double * bounds) : previous_(NULL), empty_(true) {
    for(int i=0;i<6;i++) box_[i] = bounds[i];
    for(int d=0;d<8;d++)
        children_[d] = NULL;
    double dx = bounds[1] - bounds[0];
    double dy = bounds[3] - bounds[2];
    double dz = bounds[5] - bounds[4];
    D_ = min(dx,min(dy,dz));
    for(int i=1;i<particules.size();i++)
        insert(particules[i]);
}

Octree::~Octree() {
    for(int i=0;i<8;i++)
        if(children_[i] != NULL)
            delete children_[i];
}

void Octree::force(const Particule &p, Vector<DIM> &forc) const {
    if(isLeaf()) {
        if(!empty_) {
                Vector<DIM> vect = pos_;
                vect -= p.r;
                double length = vect.norm();
                if(length==0.0) return;
                vect *= p.m * mass_;
                vect /= (length*length*length);
                forc += vect;
        }
    }
    else {
        Vector<DIM> vect = pos_;
        vect -= p.r;
        double length = vect.norm();
        if(false && D_/length < theta_) {
            vect *= p.m * mass_;
            vect /= (length*length*length);
            forc += vect;
        }
        else
            for(int i=0;i<8;i++) {
                children_[i]->force(p,forc);
            }
    }
}

void Octree::insert(const Particule &p) {
    if(isLeaf()) {
        if(empty_) {
            pos_ = p.r;
            mass_ = p.m;
            empty_ = false;
        }
        else {
            for(int i=0;i<8;i++) {
                double bounds[6];
                for(int d=0;d<6;d++)
                    bounds[d] = box_[d];
                //creer le bon bounds(i)
                double xm = (box_[0]+box_[1])/2.0;
                double ym = (box_[2]+box_[3])/2.0;
                double zm = (box_[4]+box_[5])/2.0;
                if((i%2)==0) 
                    bounds[1]=xm;
                else 
                    bounds[0]=xm;

                if(i<4)
                    bounds[3]=ym;
                else
                    bounds[2]=ym;
                if(((i/2)%2)==0)
                    bounds[5]=zm;
                else
                    bounds[4]=zm;
                
                children_[i] = new Octree(bounds);
                children_[i]->previous_ = this;
                if(p.r.isInside(bounds)) children_[i]->insert(p);
                if(pos_.isInside(bounds)) children_[i]->insert(Particule(mass_,pos_));
            }
        }
    }
    else {
        for(int i=0;i<8;i++) {
            //pos_ = (p.r + pos_)/2.0;
            //mass_ = (mass_ + p.m)/2.0;
            if(p.r.isInside(children_[i]->box_)) {
                children_[i]->insert(p);
                break;
            }
        }
    }
    pos_ = (p.m * p.r + mass_ * pos_)/(mass_ + p.m);
    mass_ = (mass_ + p.m);
}

bool Octree::isLeaf() const {
    for(int i=0;i<8;i++) if(children_[i]!=NULL) return false;
    return true;
}
