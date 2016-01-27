
#include "RealTimePlayer.hpp"


vtkStandardNewMacro(CustomInteractor);

//implementation de vtkTimerCallback

void vtkTimerCallback::Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId,
            void *vtkNotUsed(callData)) {
    if (vtkCommand::TimerEvent == eventId){
        //++this->TimerCount;
        for(int i=0;i<nb;i++)
            actors[i]->SetPosition(shm[i*3],shm[i*3+1],shm[i*3+2]);
        window->Render();
    }
}
 
//implementation de RealTimePlayer

RealTimePlayer::RealTimePlayer(double * shmem, int nb) : shm(shmem), nbParticules(nb) {
    vtkRenderWindow * window = vtkRenderWindow::New();
    vtkSphereSource ** spheres = new vtkSphereSource*[nbParticules];
    vtkRenderer * renderer = vtkRenderer::New();
    for(int i=0; i<nbParticules;i++) {
        spheres[i] = vtkSphereSource::New();
        spheres[i]->SetCenter(0.0, 0.0, 0.0 );
        spheres[i]->SetRadius(0.1);
    }
    vtkPolyDataMapper ** mappers = new vtkPolyDataMapper*[nbParticules];
    for(int i=0;i<nbParticules;i++) {
        mappers[i] = vtkPolyDataMapper::New();
        mappers[i]->SetInputConnection(spheres[i]->GetOutputPort());
    }
    vtkActor ** actors = new vtkActor*[nbParticules];
    for(int i=0;i<nbParticules;i++) {
        actors[i] = vtkActor::New();
        actors[i]->SetMapper(mappers[i]);
        renderer->AddActor(actors[i]);
    }

    CustomInteractor * camera = CustomInteractor::New();
    camera->window=window;

    vtkRenderWindowInteractor * interactor = vtkRenderWindowInteractor::New();
    interactor->SetRenderWindow(window);
    interactor->SetInteractorStyle(camera);
    interactor->Initialize();
    vtkTimerCallback * cb = vtkTimerCallback::New();
    cb->nb=nbParticules;
    cb->window=window;
    cb->actors=actors;
    cb->shm = shm;
    interactor->AddObserver(vtkCommand::TimerEvent, cb);
    interactor->CreateRepeatingTimer(30);

    window->AddRenderer(renderer);
    
    
    //on lance la lecture
    interactor->Start();
    }


RealTimePlayer::~RealTimePlayer() {
    camera->Delete();
    for(int i=0; i<nbParticules;i++) {
        actors[i]->Delete();
    }
    delete[] actors;
    for(int i=0; i<nbParticules;i++) {
        mappers[i]->Delete();
    }
    delete[] mappers;
    for(int i=0; i<nbParticules;i++) {
        spheres[i]->Delete();
    }
    delete[] spheres;
    interactor->Delete();
    renderer->Delete();
    window->Delete();
}



