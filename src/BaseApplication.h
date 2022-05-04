#pragma once

#include "raylib.h"
#include "raymath.h"

#include "imgui.h"
#include "rlImGui.h"
#include "rlImGuiColors.h"

class BaseApplication
{
    bool Quit;

public:

    BaseApplication(const char* title, const Vector2& defaultWindowSize=Vector2{800, 600})
    {
        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
        InitWindow(defaultWindowSize.x, defaultWindowSize.y, title);
        SetTargetFPS(60);
        rlImGuiSetup(true);

        ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
    }

    virtual ~BaseApplication() {}

    virtual void preUpdate()
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        rlImGuiBegin();
    }

    virtual void update() 
    {

    }

    virtual void postUpdate()
    {
        rlImGuiEnd();
        EndDrawing();
    }

    virtual void exit()
    {
        rlImGuiShutdown();
    }

    virtual void run()
    {
        // Main game loop
        while (!WindowShouldClose() && !Quit)    // Detect window close button or ESC key
        {
            preUpdate();
            update();
            postUpdate();
        }

        exit();
        CloseWindow();
    }

    virtual void quit()
    {
        Quit = true;
    }
};