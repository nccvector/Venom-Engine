#pragma once

#include "Viewport.h"

class SceneViewport : public Viewport
{
public:
    SceneViewport(const char* title="Scene") : Viewport {title} { }

    Camera3D Camera = { 0 };
    Ray PickRay = { 0 };                    // Picking line ray
    RayCollision Collision = { 0 };

    void setup() override
    {
        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

        Camera.fovy = 45;
        Camera.up.y = 1;
        Camera.position.y = 3;
        Camera.position.z = -25;

        Image img = GenImageChecked(256, 256, 32, 32, DARKGRAY, WHITE);
        GridTexture = LoadTextureFromImage(img);
        UnloadImage(img);
        GenTextureMipmaps(&GridTexture);
        SetTextureFilter(GridTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
        SetTextureWrap(GridTexture, TEXTURE_WRAP_CLAMP);
    }

    void shutdown() override
    {
        UnloadRenderTexture(ViewTexture);
        UnloadTexture(GridTexture);
    }

    void update() override
    {
        if (!Open)
            return;

        if (IsWindowResized())
        {
            UnloadRenderTexture(ViewTexture);
            ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        }

        float period = 10;
        float magnitude = 25;

        // Input-related functions: mouse
        if (Focused && IsMouseButtonDown(0))
            Camera.position.x = (float)(sinf(GetTime() / period) * magnitude);

        BeginTextureMode(ViewTexture);
        ClearBackground(SKYBLUE);

        BeginMode3D(Camera);

        // grid of cube trees on a plane to make a "world"
        if (!Focused)
            DrawPlane(Vector3 { 0, 0, 0 }, Vector2{ 50, 50 }, BEIGE); // simple world plane
        else
            DrawPlane(Vector3 { 0, 0, 0 }, Vector2{ 50, 50 }, BLUE); // simple world plane

        float spacing = 4;
        int count = 5;

        for (float x = -count * spacing; x <= count * spacing; x += spacing)
        {
            for (float z = -count * spacing; z <= count * spacing; z += spacing)
            {
                Vector3 pos = { x, 0.5f, z };

                Vector3 min = { x - 0.5f,0,z - 0.5f };
                Vector3 max = { x + 0.5f,1,z + 0.5f };

                DrawCubeTexture(GridTexture, Vector3{ x, 1.5f, z }, 1, 1, 1, GREEN);
                DrawCubeTexture(GridTexture, Vector3{ x, 0.5f, z }, 0.25f, 1, 0.25f, BROWN);
            }
        }

        EndMode3D();
        EndTextureMode();
    }

    Texture2D GridTexture = { 0 };
};