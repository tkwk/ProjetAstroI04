#ifndef __SCHEME_HPP__
#define __SCHEME_HPP__

class Particule;

class Scheme {
	private:
		double dt;
	public:
		virtual void timeStep(Particule *) = 0;
		
		friend class Euler;
		friend class Leapfrog;
};

#endif

