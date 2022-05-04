#pragma once

#include <iostream>

#include "BaseApplication.h"

class Application : public BaseApplication
{
public:
    Application(const char* title="MyApp", const Vector2& defaultWindowSize=Vector2{1280, 720});

    void preUpdate() override;
    void update() override; 
    void exit() override;

    void DoMainMenu();
};