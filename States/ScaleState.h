#pragma once

#include "State.h"

namespace Venom::States
{

class ScaleState : public Venom::Abstract::State
{
    ScaleState() {}

public:
    static ScaleState& Singleton()
    {
        static ScaleState instance;
        return instance;
    }

    void Enter() override;

    void Update() override;

    void Exit() override;
};

}