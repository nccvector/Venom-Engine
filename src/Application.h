#include <iostream>

#include "BaseApplication.h"

class Application : public BaseApplication
{
public:
    Application(const char* title="MyApp", const Vector2& defaultWindowSize=Vector2{1280, 720});

    void update() override; 

    void DoMainMenu();
};