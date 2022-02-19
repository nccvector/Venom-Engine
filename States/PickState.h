#pragma once

#include "State.h"

namespace Venom::States
{

class PickState : public Venom::Abstract::State
{
    PickState() {}

public:
    static PickState& Singleton()
    {
        static PickState instance;
        return instance;
    }

    void Enter() override;

    void Update() override;

    void Exit() override;
};

}