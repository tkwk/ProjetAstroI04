
#ifndef __REALTIMEPLAYER_H__
#define __REALTIMEPLAYER_H__

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

class RealTimePlayer {
    private:
        double * shm;
        int nbParticules;
        std::vector<double> sizes;

        vtkRenderWindow * window;
        vtkSphereSource ** spheres;
        vtkRenderer * renderer;
        vtkPolyDataMapper ** mappers;
        vtkActor ** actors;
        CustomInteractor * camera;
        vtkRenderWindowInteractor * interactor;
        vtkTimerCallback * cb;
    public:
        RealTimePlayer(double *shmem, int nb, double * bounds = NULL, const std::vector<double> &sizes = std::vector<double>(0));
        ~RealTimePlayer();
};


#endif


