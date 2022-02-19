#pragma once

#include "State.h"

namespace Venom::States
{

class RotateState : public Venom::Abstract::State
{
    RotateState() {}

public:
    static RotateState& Singleton()
    {
        static RotateState instance;
        return instance;
    }

    void Enter() override;

    void Update() override;

    void Exit() override;
};

}