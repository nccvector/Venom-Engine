// IMGUI INCLUDES
#include "OgreResourceManager.h"
#include "OgreResourceGroupManager.h"
#include "OgreImGuiOverlay.h"

#include<iostream>
#include<vector>
#include<string>
#include <map>
#include<tuple>

#include "imgui_internal.h"

// Toolbar callback signature
typedef void (*ToolbarCallback) ();


class Toolbar
{
    static Toolbar* instance;

    // Sorted list of tools
    std::map<int, std::tuple<std::string, ImTextureID, ToolbarCallback>> tools 
    {
        { 0, std::make_tuple("pick",     nullptr, []() -> void { }) },
        { 1, std::make_tuple("move",     nullptr, []() -> void { }) },
        { 2, std::make_tuple("rotate",   nullptr, []() -> void { }) },
        { 3, std::make_tuple("scale",    nullptr, []() -> void { }) },
        { 4, std::make_tuple("object",   nullptr, []() -> void { }) },
        { 5, std::make_tuple("cube",     nullptr, []() -> void { }) },
        { 6, std::make_tuple("cone",     nullptr, []() -> void { }) }
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
                []() -> void {  }               // callback
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

        for(auto tool : tools)
        {
            // Getting textureID and callback
            ImTextureID     texID = std::get<1>(tool.second);
            ToolbarCallback toolCallback = std::get<2>(tool.second);

            // Using the tool button
            if(ImGui::ImageButton((void*)(intptr_t) texID, ImVec2(32, 32)))
            {
                // Calling assigned callback
                toolCallback();
            }
        }

        ImGui::PopStyleVar();

        ImGui::End();
    }

    void AttachAllCallbacks(ToolbarCallback callback)
    {
        // Initializing tools
        for(auto tool : tools)
            std::get<2>(tool.second) = callback;
    }
};

// Initializing the singleton
Toolbar* Toolbar::instance = 0;