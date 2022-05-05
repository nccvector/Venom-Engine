#pragma once

#include "Widget.h"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

class Viewport : public Widget
{
public:
    Viewport(const char* title) : Widget {title} { }
    
    RenderTexture ViewTexture = { 0 };
    ImVec2 Size;
    Rectangle ViewRect = { 0 };

    virtual void show()
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

        rlImGuiImageRect(&ViewTexture.texture, (int)Size.x, (int)Size.y, ViewRect);
        ImGui::End();
        ImGui::PopStyleVar();
    }
};