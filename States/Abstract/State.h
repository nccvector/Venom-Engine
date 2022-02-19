#pragma once

namespace Venom::Abstract
{

class State
{
public:
    State () {}
    virtual void Enter() {}
    virtual void HandleInput() {}
    virtual void Update() {}
    virtual void LogicalUpdate() {}
    virtual void Exit() {}
};   

}