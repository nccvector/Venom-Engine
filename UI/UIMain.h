#pragma once

// OGRE INCLUDES
#include "OgreResourceManager.h"
#include "OgreResourceGroupManager.h"
#include "OgreFontManager.h"
#include "OgreImGuiOverlay.h"

// CUSTOM INCLUDES
#include "Dockspace.h"
#include "Toolbar.h"
#include "Console.h"

/*
Created all the necessary widgets, also sets up initial resources like fonts
*/

class UIMain
{
public:
    UIMain()
    {
        //////////////////////////////////////////////////////////
        // ADDING IMGUI OVERLAY
        auto imguiOverlay = new Ogre::ImGuiOverlay();

        // PREPARING FONT
        Ogre::ResourcePtr font = Ogre::FontManager::getSingleton().create("OpenSans-Regular", "General");
        font->setParameter("type","truetype");
        font->setParameter("source","OpenSans-Regular.ttf");
        font->setParameter("size","18");
        font->setParameter("resolution","96");
        font->setParameter("code_points","30-126"); // Include spaces
        font->load();

        // SETTING DEFAULT FONT
        imguiOverlay->addFont("OpenSans-Regular", "General");

        // handle DPI scaling
        float vpScale = Ogre::OverlayManager::getSingleton().getPixelRatio();
        ImGui::GetIO().FontGlobalScale = std::round(vpScale); // default font does not work with fractional scaling
        ImGui::GetStyle().ScaleAllSizes(vpScale);

        // SETTING UP DARK THEME
        SetDarkThemeColors();

        /////////////////////////////////

        // Enabling docking
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        imguiOverlay->setZOrder(300);
        imguiOverlay->show();

        Ogre::OverlayManager::getSingleton().addOverlay(imguiOverlay); // now owned by overlaymgr
        //////////////////////////////////////////////////////////

        // CREATING DOCKS
        Dockspace::getSingleton();  // Initializing dockspace
        Toolbar::getSingleton();    // Initializing toolbar
        Console::getSingleton();    // Initializing console

        // Assigning callbacks to toolbar
        Toolbar* tb = Toolbar::getSingleton();
        tb->SetPickCallback     (&UIMain::PickCallback);
        tb->SetMoveCallback     (&UIMain::MoveCallback);
        tb->SetRotateCallback   (&UIMain::RotateCallback);
        tb->SetScaleCallback    (&UIMain::RotateCallback);
        tb->SetObjectCallback   (&UIMain::RotateCallback);
        tb->SetCubeCallback     (&UIMain::RotateCallback);
        tb->SetConeCallback     (&UIMain::RotateCallback);
    }

    void Draw()
    {
        // NEEDED!!!
        Ogre::ImGuiOverlay::NewFrame();

        // [dockspace]
        Dockspace::getSingleton()->Begin();

        Toolbar::getSingleton()->Draw();
        Console::getSingleton()->Draw("Console", nullptr);

        ImGui::ShowDemoWindow();

        // [dockspace]
        Dockspace::getSingleton()->End();
    }

    void SetDarkThemeColors() {

        ImGui::StyleColorsDark();


        // When viewports are enabled we tweak WindowRounding/WindowBg so platform
        // windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }


        auto &colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};

        // Headers
        colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Buttons
        colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Frame BG
        colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
        colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
        colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    }

    static void PickCallback()
    {
        Console::getSingleton()->AddLog("PICK");
    }

    static void MoveCallback()
    {
        Console::getSingleton()->AddLog("MOVE");
    }

    static void RotateCallback()
    {
        Console::getSingleton()->AddLog("ROTATE");
    }
};