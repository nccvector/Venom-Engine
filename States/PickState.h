#pragma once

#include "State.h"
#include "OgreInput.h"

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

    bool mousePressed(const OgreBites::MouseButtonEvent& evt) override;

    void Update() override;

    void Exit() override;
};

}