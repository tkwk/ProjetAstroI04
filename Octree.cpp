
#include "Octree.hpp"
#include <sstream>

double Octree::theta = 0.0;
std::map<Particule*,Octree*> Octree::partMap;
Octree * Octree::head = NULL;

double min(double x,double y) {return (x<y)?x:y;}

Octree::Octree(double * bounds) : previous_(NULL), particule(NULL), np(0) {
    for(int i=0;i<6;i++) box_[i] = bounds[i];
    for(int d=0;d<8;d++) children_[d] = NULL;
    double dx = bounds[1] - bounds[0];
    double dy = bounds[3] - bounds[2];
    double dz = bounds[5] - bounds[4];
    D_ = min(dx,min(dy,dz));
}

Octree::Octree(const std::vector<Particule*> &particules, double * bounds) :
previous_(NULL), particule(NULL), np(0) {
    Octree::head = this;
    for(int i=0;i<6;i++) box_[i] = bounds[i];
    for(int d=0;d<8;d++)
        children_[d] = NULL;
    double dx = bounds[1] - bounds[0];
    double dy = bounds[3] - bounds[2];
    double dz = bounds[5] - bounds[4];
    D_ = min(dx,min(dy,dz));
    for(int i=0;i<particules.size();i++) {
        insert(particules[i]);
    }
}

Octree::~Octree() {
    for(int i=0;i<8;i++)
        if(children_[i] != NULL) {
            delete children_[i];
            children_[i] = NULL;
        }
}

void Octree::force(Particule *p, Vector<DIM> &forc) const {
    if(isLeaf()) {
        if(particule!=NULL) {
                Vector<DIM> vect = pos_;
                vect -= p->r;
                double length = vect.norm();
                if(particule->id() == p->id()) return;
                vect *= p->m * mass_;
                vect /= (length*length*length);
                forc += vect;
        }
    }
    else {
        Vector<DIM> vect = pos_;
        vect -= p->r;
        double length = vect.norm();
        if(D_/length < theta) {
            vect *= p->m * mass_;
            vect /= (length*length*length);
            forc += vect;
        }
        else
            for(int i=0;i<8;i++) {
                children_[i]->force(p,forc);
            }
    }
}

void Octree::insert(Particule *p) {
    if(isLeaf()) {
        if(np==0/*particule==NULL*/) {
            particule=p;
            Octree::partMap[p]=this;
        }
        else {
            for(int i=0;i<8;i++) {
                double bounds[6];
                for(int d=0;d<6;d++)
                    bounds[d] = box_[d];
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
                if(p->r.isInside(bounds)) children_[i]->insert(p);
                if(pos_.isInside(bounds)) children_[i]->insert(particule);
            }
        }
    }
    else {
        for(int i=0;i<8;i++) {
            if(p->r.isInside(children_[i]->box_)) {
                children_[i]->insert(p);
                break;
            }
        }
    }
    pos_ = (p->m * p->r + mass_ * pos_)/(mass_ + p->m);
    mass_ = (mass_ + p->m);
    np++;
}

void Octree::decrement() {
    np--;
    if(np==0) particule = NULL;
    if(previous_ != NULL)
        previous_->decrement();
}

void Octree::deletePart(Particule *p) {
    if(np!=1 || particule!=p) {
        Octree::partMap[p]->deletePart(p);
        return;
    }
    particule = NULL;
    Octree::partMap[p] = NULL;
    decrement();
    if(previous_!=NULL)
        previous_->remove(mass_,pos_);
    
}

void Octree::remove(double mass, const Vector<DIM> &pos) {
    Vector<DIM> oldPos = pos_;
    double oldMass = mass_;

    pos_ -= mass*pos/mass_;
    mass_ -= mass;
    
    if(previous_ != NULL) {
        if(np==0)
            previous_->remove(oldMass,oldPos);
        else
            previous_->update(oldMass,mass_,oldPos,pos_);
    }
}

void Octree::update(double oldmass, double newmass, const Vector<DIM> &oldr, const Vector<DIM> &newr) {
    Vector<DIM> oldPos = pos_;
    double oldMass = mass_;

    pos_ -= oldmass*oldr/mass_;
    mass_ -= oldmass;
    pos_ = (mass_ * pos_ + newmass * newr)/(mass_ + newmass);
    mass_ += newmass;
    if(previous_!=NULL)
        previous_->update(oldMass,mass_,oldPos,pos_);
}

void Octree::checkChildren() {
    if(isLeaf()) return;
    bool leaf=true;
    for(int i=0;i<8;i++) {
        if(children_[i]->np != 0)
            leaf=false;
    }
    if(leaf) {
        for(int i=0;i<8;i++) {
            delete children_[i];
            children_[i] = NULL;
        }
    }
    else {
        for(int i=0;i<8;i++)
            children_[i]->checkChildren();
    }
}

void Octree::update(Particule *p) {
    if(np!=1 || particule!=p) {
        Octree::partMap[p]->update(p);
        return;
    }
    if(p->r.isInside(box_)) {
        if(previous_!=NULL)
            previous_->update(p->m,p->m,pos_,p->r);
        pos_=p->r;
    }
    else {
        Octree::partMap[p] = NULL;
        particule = NULL;
        deletePart(p);
        Octree::head->insert(p);
    }

}

bool Octree::isLeaf() const {
    for(int i=0;i<8;i++) if(children_[i]!=NULL) return false;
    return true;
}

std::string Octree::toString(std::string indent) const {
    std::stringstream ss("");
    ss << indent;
    for(int i=0;i<6;i++)
        ss << " " << box_[i];
    ss << std::endl;
    ss << indent;
    ss << mass_ << " " << pos_ << std::endl;
    indent += "          ";
    for(int i=0;i<8;i++) {
        if(children_[i] != NULL)
            ss << children_[i]->toString(indent);
    }
    return ss.str();
}




