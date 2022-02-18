#pragma once

#include "State.h"
#include "StateMachine.h"

class ApplicationStateMachine : public StateMachine
{
    ApplicationStateMachine() {}

public:
    static ApplicationStateMachine& Singleton()
    {
        static ApplicationStateMachine instance;
        return instance;
    }
};