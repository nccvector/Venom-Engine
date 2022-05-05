#pragma once

class Widget
{
protected:
    const char* mTitle;

public:
    Widget(const char* title) { mTitle = title; }

    bool Open = false;
    bool Focused = false;

    virtual void setup() = 0;
    virtual void shutdown() = 0;
    virtual void show() = 0;
    virtual void update() = 0;

    virtual void _update()
    {
        // Update any necessary data
        update();

        // Show the widget
        show();
    }
};