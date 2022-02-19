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
    Ogre::Ray ray;
    Application::Singleton().camera->getCameraToViewportRay(evt.x, evt.y, &ray);

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