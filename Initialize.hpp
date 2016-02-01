
#ifndef __INITIALIZE_HPP__
#define __INITIALIZE_HPP__

/* 
    Classe concernant les differents initialisations de particules possibles

    Galaxy
    Random
    InputFile
*/

#include "Particule.hpp"
#include <stdlib.h>
#include <time.h>
#include <fstream>

#define CONST_PI		3.14159265359

struct Init {
  virtual std::vector<Particule> getInit() = 0;
};

struct IFile : public Init {
  std::string fileName;

  virtual std::vector<Particule> getInit() {
    std::vector<Particule> Particules;
    ifstream file(fileName.c_str());
    std::string line;
    Particules.resize(0);
    while(getline(file,line)) {
        stringstream ss(line);
        real m, x, y, z, vx, vy, vz, radius;
        radius = -1.0;
        ss >> m >> x >> y >> z >> vx >> vy >> vz;
        std::string findeligne;
        getline(ss,findeligne);
        if(findeligne!="") {
            std::stringstream sss(findeligne);
            sss >> radius;
        }
        Vector<DIM> pos, spd;
        pos[0] = x;
        pos[1] = y;
        pos[2] = z;
        spd[0] = vx;
        spd[1] = vy;
        spd[2] = vz;
        Particules.push_back(Particule(m,pos,spd,radius));
    }
    file.close();
    return Particules;
  }
};

struct IRandom : public Init {
  int nbParticules;
  double bounds[6];
  double mass;
  
  virtual std::vector<Particule> getInit () {
    srand(time(NULL));
    std::vector<Particule> res(nbParticules);
    for (int i=0; i<nbParticules; i++) {
      double x, y, z;
      x = bounds[0] + (bounds[1] - bounds[0])*((double)(rand()%(100*nbParticules)))/(100.*nbParticules);
      y = bounds[2] + (bounds[3] - bounds[2])*((double)(rand()%(100*nbParticules)))/(100.*nbParticules);
      z = bounds[4] + (bounds[5] - bounds[4])*((double)(rand()%(100*nbParticules)))/(100.*nbParticules);
      Vector<DIM> pos;
      pos[0] = x; pos[1] = y; pos[2] = z;
      Vector<DIM> spd;
      spd[0] = 0.0; spd[1] = 0.0; spd[2] = 0.0;
      res[i] = Particule(mass,pos,spd);
    }
    return res;
  }

};

struct IGalaxy : public Init {
	int nbParticules;
	double mass;
	virtual std::vector<Particule> getInit () {
		srand(time(NULL));
		std::vector<Particule> res(nbParticules);
		int np1 = floor(0.5*nbParticules);
		int np2 = nbParticules - np1;

		double xc1, xc2, vxc1, vxc2;
		double Rgal1, Rgal2;
		double Mcenter1, Mcenter2;
		xc1  = -1.5; xc2  = 1.5;
		vxc1 = 0.5;  vxc2 = -0.4;
		
		Rgal1 = 1.0; Rgal2 = 1.0;
		Mcenter1 = 2.e6; Mcenter2 = 1.5e6;

		// Premiere galaxie
		Vector<DIM> pos1, pos2;
		pos1[0] = xc1; pos1[1] = 0.0; pos1[2] = 0.0;
		pos2[0] = xc2; pos2[1] = 0.0; pos2[2] = 0.0;
		Vector<DIM> spd1, spd2;
		spd1[0] = vxc1; spd1[1] = 0.0; spd1[2] = 0.0;
		spd2[0] = vxc2; spd2[1] = 0.0; spd2[2] = 0.0;

		res[0] 	= Particule(Mcenter1, pos1, spd1);
		res[np1] = Particule(Mcenter2, pos2, spd2);
		
		for (int i=1; i<nbParticules; i++) {
			if (i<np1) {
			double r, phi;
			r 	= 0.1*Rgal1 + 0.9*Rgal1*((double)(rand()%(100*nbParticules)))/(100.*nbParticules);
			phi = 2*CONST_PI*((double)(rand()%(100*nbParticules)))/(100.*nbParticules); 
			Vector<DIM> pos;
			pos[0] = xc1 + r*cos(phi); pos[1] = r*sin(phi); pos[2] = 0.0;
			Vector<DIM> spd;
			double vr = sqrt(Mcenter1/r);
			spd[0] = vxc1 - vr*sin(phi); spd[1] = vr*cos(phi); spd[2] = 0.0;
			res[i] = Particule(mass,pos,spd);
			}
			else if (i>np1) {
			double r, phi;
			r   = 0.1*Rgal2 + 0.9*Rgal2*((double)(rand()%(100*nbParticules)))/(100.*nbParticules);
			phi = 2*CONST_PI*((double)(rand()%(100*nbParticules)))/(100.*nbParticules);
			Vector<DIM> pos;
			pos[0] = xc2 + r*cos(phi); pos[1] = r*sin(phi); pos[2] = 0.0;
			Vector<DIM> spd;
			double vr = sqrt(Mcenter2/r);
			spd[0] = vxc2 - vr*sin(phi); spd[1] = vr*cos(phi); spd[2] = 0.0;
			res[i] = Particule(mass,pos,spd);
			}
			}
		return res;
	}

};

#endif


