
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

RealTimePlayer::RealTimePlayer(double * shmem, int nb, double * bounds, const std::vector<double>&sis) : shm(shmem), nbParticules(nb) {
    domainBox = NULL;
    actorBox = NULL;
    mapperBox = NULL;
    for(int i=0;i<nb;i++)
        sizes.push_back(0.1);
    for(int i=0;i<sis.size();i++)
        sizes[i]=sis[i];
    window = vtkRenderWindow::New();
    spheres = new vtkSphereSource*[nbParticules];
    renderer = vtkRenderer::New();
    for(int i=0; i<nbParticules;i++) {
        spheres[i] = vtkSphereSource::New();
        spheres[i]->SetCenter(0.0, 0.0, 0.0 );
        spheres[i]->SetRadius(sizes[i]);
				// Spheres appear smoother
				spheres[i]->SetPhiResolution(18);
				spheres[i]->SetThetaResolution(36);
    }
    mappers = new vtkPolyDataMapper*[nbParticules];
    for(int i=0;i<nbParticules;i++) {
        mappers[i] = vtkPolyDataMapper::New();
        mappers[i]->SetInputConnection(spheres[i]->GetOutputPort());
    }
    actors = new vtkActor*[nbParticules];
    for(int i=0;i<nbParticules;i++) {
        actors[i] = vtkActor::New();
        actors[i]->SetMapper(mappers[i]);
        renderer->AddActor(actors[i]);
    }

		// Add actor to display domain box
    if(bounds!=NULL) {
		domainBox = vtkCubeSource::New();
		mapperBox = vtkPolyDataMapper::New();
		actorBox = vtkActor::New();
		
		domainBox->SetBounds(bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5]);
		mapperBox->SetInputConnection(domainBox->GetOutputPort());
		actorBox->SetMapper(mapperBox);
		actorBox->GetProperty()->SetRepresentationToWireframe();
		actorBox->GetProperty()->SetColor(0.5, 0.0, 0.0);
		renderer->AddActor(actorBox);
	}
    CustomInteractor * camera = CustomInteractor::New();
    camera->window=window;

		window->SetSize(720, 720); // Set window size in  pixels   

    interactor = vtkRenderWindowInteractor::New();	
		interactor->SetRenderWindow(window);
    interactor->SetInteractorStyle(camera);
    interactor->Initialize();
    cb = vtkTimerCallback::New();
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
    if(domainBox!=NULL) domainBox->Delete();
    if(mapperBox!=NULL) mapperBox->Delete();
    if(actorBox!=NULL) actorBox->Delete();
    delete[] spheres;
    interactor->Delete();
    renderer->Delete();
    window->Delete();
}



