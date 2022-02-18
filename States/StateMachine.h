#pragma once

#include "State.h"

class StateMachine
{
    State* m_currentState = nullptr;
    State* m_prevState = nullptr;

public:

    StateMachine() {}

    StateMachine (State* startState)
    {
        m_currentState = startState;
    }

    State* GetCurrentState()
    {
        return m_currentState;
    }

    void ChangeState(State* nextState)
    {
        // Exiting current state
        if (m_currentState)
            m_currentState->Exit();

        // Storing previous state (possibly for undo?)
        m_prevState = m_currentState;

        // Updating current state
        m_currentState = nextState;

        // Entering the state
        m_currentState->Enter();
    }

    void RevertState()
    {
        if (m_prevState)
        {
            m_currentState->Exit();
            m_currentState = m_prevState;
            m_currentState->Enter();   
        }
    }
};