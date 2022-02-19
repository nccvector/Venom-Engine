#include "PickState.h"
#include "Console.h"

using namespace Venom::UI;

namespace Venom::States
{

void PickState::Enter()
{
    Console::getSingleton().AddLog("Entered Pick State");
}

void PickState::Update()
{
    Console::getSingleton().AddLog("Pick::Update()");
}

void PickState::Exit()
{
    Console::getSingleton().AddLog("Exiting Pick State");
}

}