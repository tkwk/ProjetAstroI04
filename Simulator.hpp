#ifndef __SIMULATOR_HPP__
#define __SIMULATOR_HPP__

#include <string>
#include "Euler.hpp"
#include "Leapfrog.hpp"
#include "BarnesHut.hpp"
#include "Universe.hpp"
#include "Parameter.hpp"
#include "RealTimePlayer.hpp"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>

class Simulator {
    public:
        Simulator(const std::string &input, const std::string &params, const std::string &out, const std::string &outMovie, bool realTime);
        ~Simulator();
        void start();
        
        static void handleInterruptions();          // Fonction pour gerer l'interruption du calcul par Ctrl-C
    private:
        static bool interrupted;                    // Items relatifs à la 
        static void intHandler(int);                // gestion d'interruption

        Parameter * parameters;
        Universe * universe;
        Scheme * scheme;

        std::string output;                     // Nom du fichier de sortie (contenant l'etats des particules a le fin du calcul)
        std::string outputMovie;                // Nom d'un eventuel fichier temporel
        bool realTime;                          // Visualisation en temps reel du calcul ou non
        std::string input;                      // Nom d'un eventuel fichier d'entree

        int refreshFreq;                        // Nombre d'iteration avant d'afficher la progression du calcul
        int movieNbPoints;                      // Nombre de points dans l'eventuel fichier film
};

#endif


