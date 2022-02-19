#pragma once

/*
Created all the necessary widgets, also sets up initial resources like fonts
UIMain needs access to ogre root to create and read info of many objects
*/

namespace Venom::UI
{

class UIMain
{

public:

    static UIMain& Singleton()
    {
        static UIMain instance;
        return instance;
    }

    UIMain();

    void Draw();

    void SetDarkThemeColors();

    // Toolbar callbacks
    static void PickCallback();
    static void MoveCallback();
    static void RotateCallback();
    static void ScaleCallback();
    static void ObjectCallback();
    static void CubeCallback();
    static void ConeCallback();

};

}