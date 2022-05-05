#include "ImageViewport.h"
#include "imgui.h"
#include "rlImGui.h"
#include "raymath.h"
#include "Console.h"

void ImageViewport::setup()
{
    Camera.zoom = 1;
    Camera.target.x = 0;
    Camera.target.y = 0;
    Camera.rotation = 0;
    Camera.offset.x = GetScreenWidth() / 2.0f;
    Camera.offset.y = GetScreenHeight() / 2.0f;

    ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    ImageTexture = LoadTexture("res//heightmap.png");

    updateRenderTexture();
}

void ImageViewport::show()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

    ImGui::Begin(mTitle, &Open, ImGuiWindowFlags_NoScrollbar);
    Focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);

    Size = ImGui::GetContentRegionAvail();
    
    ViewRect = { 0 };
    ViewRect.x = ViewTexture.texture.width / 2 - Size.x / 2;
    ViewRect.y = ViewTexture.texture.height / 2 - Size.y / 2;
    ViewRect.width = Size.x;
    ViewRect.height = -Size.y;

    //================================================================================ 
    // Add optional content inside the content region
    if (ImGui::BeginChild("Toolbar", ImVec2(ImGui::GetContentRegionAvail().x, 25)))
    {
        ImGui::SetCursorPosX(2);
        ImGui::SetCursorPosY(3);

        if (ImGui::Button("None"))
        {
            CurrentToolMode = ToolMode::None;
        }
        ImGui::SameLine();

        if (ImGui::Button("Move"))
        {
            CurrentToolMode = ToolMode::Move;
        }

        ImGui::SameLine();
        switch (CurrentToolMode)
        {
        case ToolMode::None:
            ImGui::TextUnformatted("No Tool");
            break;
        case ToolMode::Move:
            ImGui::TextUnformatted("Move Tool");
            break;
        default:
            break;
        }

        ImGui::SameLine();
        ImGui::TextUnformatted(TextFormat("Camera target X%f Y%f", Camera.target.x, Camera.target.y));
        ImGui::EndChild();
    }
    //================================================================================ 

    rlImGuiImageRect(&ViewTexture.texture, (int)Size.x, (int)Size.y, ViewRect);
    ImGui::End();
    ImGui::PopStyleVar();
}

void ImageViewport::update()
{
    if (!Open)
        return;

    if (IsWindowResized())
    {
        LOG("RESIZED");
        UnloadRenderTexture(ViewTexture);
        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

        Camera.offset.x = GetScreenWidth() / 2.0f;
        Camera.offset.y = GetScreenHeight() / 2.0f;

        DirtyScene = true;
    }

    if (Focused)
    {
        if (CurrentToolMode == ToolMode::Move)
        {
            if (IsMouseButtonDown(0))
            {
                if (!Dragging)
                {
                    LastMousePos = GetMousePosition();
                    LastTarget = Camera.target;
                }
                Dragging = true;
                Vector2 mousePos = GetMousePosition();
                Vector2 mouseDelta = Vector2Subtract(LastMousePos, mousePos);

                mouseDelta.x /= Camera.zoom;
                mouseDelta.y /= Camera.zoom;
                Camera.target = Vector2Add(LastTarget, mouseDelta);

                DirtyScene = true;
                
            }
            else
            {
                Dragging = false;
            }
        }
    }
    else
    {
        Dragging = false;
    }

    // Update render texture only if dirty
    if (DirtyScene)
    {
        DirtyScene = false;
        updateRenderTexture();
    }
}

void ImageViewport::updateRenderTexture()
{
    BeginTextureMode(ViewTexture);
    ClearBackground(BLUE);
    BeginMode2D(Camera);
    DrawTexture(ImageTexture, ImageTexture.width / -2, ImageTexture.height / -2, WHITE);
    EndMode2D();
    EndTextureMode();
}

void ImageViewport::shutdown()
{
    UnloadRenderTexture(ViewTexture);
    UnloadTexture(ImageTexture);
}