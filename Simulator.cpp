
#include "Simulator.hpp"

Simulator::Simulator(const std::string &input, const std::string &params,
        const std::string &out, const std::string &outMovie, bool rt) {
    parameters = new Parameter(params);
    universe = new Universe(input);
    if(parameters->scheme == "Euler")
        scheme = new Euler;
    else if(parameters->scheme == "Leapfrog")
        scheme = new Leapfrog;
    else {
        if(parameters->scheme=="")
            cerr << "No scheme specified" << std::endl;
        else
            cerr << "Unknown scheme: " << parameters->scheme << endl;
        exit(0);
    }
    scheme->dt = parameters->dt;
    output = out;
    outputMovie = outMovie;
    realTime = rt;

    this->start();
}

Simulator::~Simulator() {
    delete parameters;
    delete universe;
    delete scheme;
}

void Simulator::start() {
    int pid = -1;
    double * shm = NULL;
    int shmid = -1;
    int nbParticules = universe->particules().size();

    if(realTime)
        pid = fork();
    if(pid == 0) {
        //afficheur temps réel vtk
        //memoire paratagee
        shmid = shmget(2016,3*sizeof(double)*nbParticules,0);
        shm = (double*)shmat(shmid,0,0);
        
        RealTimePlayer(shm,nbParticules);

        shmdt(shm);
        shmid=-1;
    }
    else {
        if(pid != -1) {
            //memoire paratagee
            shmid = shmget(2016,3*sizeof(double)*nbParticules,0666 | IPC_CREAT);
            shm = (double*)shmat(shmid,0,0);
        }
        //boucle de calcul
        double time = 0.0;
        bool movie = (outputMovie!="");
        ofstream *mfile;
        if(movie) mfile = new ofstream(outputMovie.c_str());
        int it=0;
        int nbit=parameters->T/parameters->dt;

        while(time < parameters->T) {
            //ecrire dans le fichier si necessaire
            if(movie && nbit > 11000 && (it%(nbit/10000)==0)) {
                (*mfile) << time;
                for(int i=0;i<nbParticules;i++)
                    for(int j=0;j<3;j++)
                        (*mfile) << " " << universe->particules()[i].r[j];
                (*mfile) << std::endl;
            }
            //ecrire dans la memoire partagee si necessaire
            if(pid != -1 && ((nbit%1000)==0)) {
                for(int i=0;i<nbParticules;i++)
                    for(int j=0;j<3;j++)
                        shm[3*i+j] = universe->particules()[i].r[j];
            }
            it++;
            time+=parameters->dt;
            //iteration du schema
            scheme->universeStep(*universe);
        }

        std::cout << "Computation finished" << std::endl;
        
        if(movie) {
            mfile->close();
            delete mfile;
            std::cout << "Movie file written to " << outputMovie << std::endl;
        }
        universe->write(output);
        std::cout << "Output file written to " << output << std::endl;

        if(pid != -1) {
            cout << "Waiting for graphical interface to be closed..." << endl;
            wait(NULL);
            cout << "Done" << endl;
            shmdt(shm);
            shmctl(shmid,IPC_RMID,NULL);
        }
    }

}










