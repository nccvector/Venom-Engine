#pragma once

#include "State.h"
#include "Console.h"

class PickState : public State
{
    PickState() {}

public:
    static PickState& Singleton()
    {
        static PickState instance;
        return instance;
    }

    void Enter() override
    {
        Console::getSingleton()->AddLog("Entered Pick State");
    }

    void Update() override
    {
        Console::getSingleton()->AddLog("Pick::Update()");
    }

    void Exit() override
    {
        Console::getSingleton()->AddLog("Exiting Pick State");
    }
};