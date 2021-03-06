
#ifndef __REALTIMEPLAYER_H__
#define __REALTIMEPLAYER_H__

/*
    Classe d'affichage:
    La classe RealTimePlayer affiche toutes les 30 ms les particules dont la
    positon est stockée dans le buffer shm
*/

#include <string>

#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>
#include <vtkCubeSource.h>
#include <vtkProperty.h>

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>

// Interacteur vtk
class CustomInteractor : public vtkInteractorStyleTrackballCamera {
private:
public:
    vtkRenderWindow * window;
    static CustomInteractor *New();
    void OnKeyPress(){
        std::string key = Interactor->GetKeySym();
        if(key.compare("q")==0) {
            window->Finalize();
        }
    }
};

// Timer
class vtkTimerCallback : public vtkCommand
{
    public:
        static vtkTimerCallback *New() {
            vtkTimerCallback *cb = new vtkTimerCallback;
            return cb;
        }
        virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId,
            void *vtkNotUsed(callData));
        int nb;
        double * shm;
        vtkRenderWindow * window;
        vtkActor ** actors;
};

// Classe affichant les shperes
class RealTimePlayer {
    private:
        double * shm;                   //buffer contenant les positions des particules: il est lu toutes les 30ms
        int nbParticules;               
        std::vector<double> sizes;      //tailles d'affichage des particules

        vtkRenderWindow * window;
        vtkSphereSource ** spheres;
        vtkRenderer * renderer;
        vtkPolyDataMapper ** mappers;
        vtkActor ** actors;
        CustomInteractor * camera;
        vtkRenderWindowInteractor * interactor;
        vtkTimerCallback * cb;
        vtkCubeSource * domainBox;
        vtkPolyDataMapper * mapperBox;
        vtkActor * actorBox;
    public:
        RealTimePlayer(double *shmem, int nb, double * bounds = NULL, const std::vector<double> &sizes = std::vector<double>(0));
        ~RealTimePlayer();
};


#endif


