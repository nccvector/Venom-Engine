#pragma once

#include "State.h"
#include "Console.h"

class RotateState : public State
{
    RotateState() {}

public:
    static RotateState& Singleton()
    {
        static RotateState instance;
        return instance;
    }

    void Enter() override
    {
        Console::getSingleton()->AddLog("Entered Rotate State");
    }

    void Update() override
    {
        Console::getSingleton()->AddLog("Rotate::Update()");
    }

    void Exit() override
    {
        Console::getSingleton()->AddLog("Exiting Rotate State");
    }
};