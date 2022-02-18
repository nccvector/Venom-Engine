#pragma once

#include "State.h"
#include "Console.h"

class MoveState : public State
{
    MoveState() {}

public:
    static MoveState& Singleton()
    {
        static MoveState instance;
        return instance;
    }

    void Enter() override
    {
        Console::getSingleton()->AddLog("Entered Move State");
    }

    void Update() override
    {
        Console::getSingleton()->AddLog("Move::Update()");
    }

    void Exit() override
    {
        Console::getSingleton()->AddLog("Exiting Move State");
    }
};