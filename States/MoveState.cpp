#include "MoveState.h"
#include "Console.h"

using namespace Venom::UI;

namespace Venom::States
{

void MoveState::Enter()
{
    Console::getSingleton().AddLog("Entered Move State");
}

void MoveState::Update()
{
    Console::getSingleton().AddLog("Move::Update()");
}

void MoveState::Exit()
{
    Console::getSingleton().AddLog("Exiting Move State");
}

}