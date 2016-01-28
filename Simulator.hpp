#ifndef __SIMULATOR_HPP__
#define __SIMULATOR_HPP__

#include <string>
#include "Euler.hpp"
#include "Leapfrog.hpp"
#include "Universe.hpp"
#include "Parameter.hpp"
#include "RealTimePlayer.hpp"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>

class Simulator {
    public:
        Simulator(const std::string &input, const std::string &params, const std::string &out, const std::string &outMovie, bool realTime);
        ~Simulator();
        void start();
    private:
        Parameter * parameters;
        Universe * universe;
        Scheme * scheme;
        std::string output;
        std::string outputMovie;
        bool realTime;
};

#endif


