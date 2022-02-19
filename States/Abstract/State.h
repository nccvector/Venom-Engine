#pragma once

#include "OgreInput.h"

namespace Venom::Abstract
{

/*
States are input listeners as well
*/

class State : public OgreBites::InputListener
{
public:
    State () {}
    virtual void Enter() {}
    virtual void Update() {}
    virtual void LogicalUpdate() {}
    virtual void Exit() {}
};   

}