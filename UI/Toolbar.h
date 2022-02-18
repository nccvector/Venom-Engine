#pragma once

// IMGUI INCLUDES
#include "OgreResourceManager.h"
#include "OgreResourceGroupManager.h"
#include "OgreImGuiOverlay.h"

#include<iostream>
#include<vector>
#include<string>
#include <map>
#include <unordered_map>
#include<tuple>

#include "imgui_internal.h"

#include "Console.h"

/*
I am trying to make toolbar in such a way so as to re-use in other projects. That's
why I am trying to give it callbacks from outside, so that the specific functionalities
on button presses remain outside this class
*/

// Toolbar callback signature
typedef void (*ToolbarCallback) ();


class Toolbar
{
    // Singleton instance
    static Toolbar* instance;

    // Sorted list of tools
    std::map<int, std::tuple<std::string, ImTextureID, ToolbarCallback>> tools 
    {
        { 0, std::make_tuple("pick",     nullptr, nullptr) },
        { 1, std::make_tuple("move",     nullptr, nullptr) },
        { 2, std::make_tuple("rotate",   nullptr, nullptr) },
        { 3, std::make_tuple("scale",    nullptr, nullptr) },
        { 4, std::make_tuple("object",   nullptr, nullptr) },
        { 5, std::make_tuple("cube",     nullptr, nullptr) },
        { 6, std::make_tuple("cone",     nullptr, nullptr) }
    };

    Toolbar()
    {
        // Initializing tools
        for(auto tool : tools)
        {
            // LOADING RESOURCE
            Ogre::TextureManager::getSingleton().load(std::get<0>(tool.second) + ".png", "General");

            // GETTING TEXTURE HANDLE
            ImTextureID imtexid = (ImTextureID)Ogre::TextureManager::getSingleton().getByName(std::get<0>(tool.second) + ".png", "General")->getHandle();

            // Adding handle and empty callback to hashmap
            tools[tool.first] = std::make_tuple(
                std::get<0>(tool.second),       // tool name
                imtexid,                        // texture handle
                nullptr
            );
        }
    }

public:
    static Toolbar* getSingleton()
    {
        if (!instance)
            instance = new Toolbar;
        
        return instance;
    }

    void Draw()
    {
        

        ImGui::Begin("Toolbar", nullptr);

        // ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(250, 250));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        for(int i=0; i<tools.size(); i++)
        {
            // Getting textureID and callback
            ImTextureID     texID = std::get<1>(tools[i]);

            // Using the button and using callback
            if(ImGui::ImageButton((void*)(intptr_t) texID, ImVec2(32, 32)))
                std::get<2>(tools[i])();
        }

        ImGui::PopStyleVar();

        ImGui::End();
    }

    // CALLBACK ATTACHMENT FUNCTIONS
    void SetPickCallback(ToolbarCallback callback)
    {
        std::get<2>(tools[0]) = callback;
    }

    void SetMoveCallback(ToolbarCallback callback)
    {
        std::get<2>(tools[1]) = callback;
    }

    void SetRotateCallback(ToolbarCallback callback)
    {
        std::get<2>(tools[2]) = callback;
    }

    void SetScaleCallback(ToolbarCallback callback)
    {
        std::get<2>(tools[3]) = callback;
    }

    void SetObjectCallback(ToolbarCallback callback)
    {
        std::get<2>(tools[4]) = callback;
    }

    void SetCubeCallback(ToolbarCallback callback)
    {
        std::get<2>(tools[5]) = callback;
    }

    void SetConeCallback(ToolbarCallback callback)
    {
        std::get<2>(tools[6]) = callback;
    }
};

// Initializing the singleton
Toolbar* Toolbar::instance = 0;