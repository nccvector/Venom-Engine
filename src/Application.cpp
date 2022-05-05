#include "Application.h"
#include "ImageViewport.h"
#include "SceneViewport.h"
#include "Console.h"

ImageViewport ivp;
SceneViewport svp;
Console& console = LOG_GET();

void Application::DoMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                Quit = true;

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            ImGui::Text("ImGui Demo");
            ImGui::Text("Image Viewer");
            ImGui::Text("3D View");

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

Application::Application(const char* title, const Vector2& defaultWindowSize) :
    BaseApplication(title, defaultWindowSize)
{
    ivp.setup();
    ivp.Open = true;

    svp.setup();
    svp.Open = true;

    console.Open = true;
}

void Application::preUpdate()
{
    // Append some logic before base class
    ivp.update();
    svp.update();
    console.update();

    // Pre-update setup of base class
    BaseApplication::preUpdate();
}

void Application::update()
{
    DoMainMenu();

    if(ivp.Open)
        ivp.show();
    
    if(svp.Open)
        svp.show();
    
    if(console.Open)
        console.show();

    // LOG("I am Update");
    // Console::get().AddLog("YO");
}

void Application::exit()
{
    BaseApplication::exit();

    ivp.shutdown();
    svp.shutdown();
    console.shutdown();
}