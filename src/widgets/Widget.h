#pragma once

class Widget
{
public:
    bool Open = false;
    bool Focused = false;

    virtual void setup() = 0;
    virtual void shutdown() = 0;
    virtual void show() = 0;
    virtual void update() = 0;
};