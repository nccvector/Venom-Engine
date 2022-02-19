#pragma once

#include "State.h"

namespace Venom::States
{

class MoveState : public Venom::Abstract::State
{
    MoveState() {}

public:
    static MoveState& Singleton()
    {
        static MoveState instance;
        return instance;
    }

    void Enter() override;

    void Update() override;

    void Exit() override;
};

}