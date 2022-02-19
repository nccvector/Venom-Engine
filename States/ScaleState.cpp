#include "ScaleState.h"
#include "Console.h"

using namespace Venom::UI;

namespace Venom::States
{

void ScaleState::Enter()
{
    Console::getSingleton().AddLog("Entered Scale State");
}

void ScaleState::Update()
{
    Console::getSingleton().AddLog("Scale::Update()");
}

void ScaleState::Exit()
{
    Console::getSingleton().AddLog("Exiting Scale State");
}

}