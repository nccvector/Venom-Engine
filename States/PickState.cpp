#include "PickState.h"
#include "Application.h"
#include "Console.h"

using namespace Venom::UI;
using namespace Venom::App;
using namespace OgreBites;

namespace Venom::States
{

void PickState::Enter()
{
    Console::getSingleton().AddLog("Entered Pick State");
}

bool PickState::mousePressed(const MouseButtonEvent& evt)
{
    // Getting the application handle
    Application& app = Application::Singleton();

    

    // Creating ray scene query object
    Ogre::RaySceneQuery* rsq = app.sceneManager->createRayQuery(
        Ogre::Ray(), Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK
    );
    
    // Cast a ray into the scene every time left click is pressed
    Ogre::Ray ray(
        Ogre::Vector3(0, 0, 0),
        Ogre::Vector3(0, 0 ,0)
    );

    // Getting the camera to world ray
    // coords must be uv's [0 to 1]
    app.camera->getCameraToViewportRay(
        evt.x / float(app.getRenderWindow()->getWidth()), 
        evt.y / float(app.getRenderWindow()->getHeight()), 
        &ray);

    // Assinging the query ray
    rsq->setRay(ray);
    rsq->setSortByDistance(true);

    // Check the intersections
    if(rsq->execute().size() > 0)
    {
        Console::getSingleton().AddLog("HIT!");

        // Getting the results 
        Ogre::RaySceneQueryResult result = rsq->getLastResults();

        std::string sz = std::to_string(result.size());
        Console::getSingleton().AddLog(&sz[0]);

        // Deselect previous object
        if(app.selectedObj)
            app.selectedObj->showBoundingBox(false);

        // Update selected object
        app.selectedObj = result[0].movable->getParentSceneNode();

        // Selecting the current object
        app.selectedObj->showBoundingBox(true);
    }

    std::string msg = "PickState::" + std::to_string(evt.x);
    Console::getSingleton().AddLog(&msg[0]);

    return true;
}

void PickState::frameRendered(const Ogre::FrameEvent& evt)
{
    Console::getSingleton().AddLog("Pick::FrameUpdate");
}

void PickState::Update()
{
    // Console::getSingleton().AddLog("Pick::Update()");
}
 
void PickState::Exit()
{
    // Console::getSingleton().AddLog("Exiting Pick State");
}

}