#pragma once

#include "State.h"
#include "Console.h"

using namespace Venom::UI;

namespace Venom::States
{

class ScaleState : public State
{
    ScaleState() {}

public:
    static ScaleState& Singleton()
    {
        static ScaleState instance;
        return instance;
    }

    void Enter() override
    {
        Console::getSingleton().AddLog("Entered Scale State");
    }

    void Update() override
    {
        Console::getSingleton().AddLog("Scale::Update()");
    }

    void Exit() override
    {
        Console::getSingleton().AddLog("Exiting Scale State");
    }
};

}