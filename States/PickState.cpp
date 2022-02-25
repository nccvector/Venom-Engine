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
    // Cast a ray into the scene every time left click is pressed
    Ogre::Ray ray(
        Ogre::Vector3(0, 0, 0),
        Ogre::Vector3(0, 0 ,0)
    );

    // Getting the application handle
    Application& app = Application::Singleton();

    // Getting the camera to world ray
    // coords must be uv's [0 to 1]
    app.camera->getCameraToViewportRay(
        evt.x / float(app.getRenderWindow()->getWidth()), 
        evt.y / float(app.getRenderWindow()->getHeight()), 
        &ray);

    // Assinging the query ray
    app.raySceneQuery->setRay(ray);

    // Check the intersections
    if(app.raySceneQuery->execute().size() > 0)
    {
        Console::getSingleton().AddLog("HIT!");
        // Finding the closest object from query result
        app.raySceneQueryResult = &app.raySceneQuery->getLastResults();

        // Do something with the results
        // Enable the bounding volume of the object
        (*app.raySceneQueryResult)[0].movable->getParentSceneNode()->showBoundingBox(true);
    }

    std::string msg = "PickState::" + std::to_string(evt.x);
    Console::getSingleton().AddLog(&msg[0]);

    return true;
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