#pragma once

#include "State.h"
#include "StateMachine.h"

using namespace Venom::Abstract;

namespace Venom::States
{

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

}