#include "Application.h"
#include "ImageViewWindow.h"
#include "SceneViewWindow.h"

ImageViewerWindow ivw;
SceneViewWindow svw;

void Application::DoMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                quit();

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
    ivw.Setup();
    ivw.Open = true;

    svw.Setup();
    svw.Open = true;
}

void Application::preUpdate()
{
    // Append some logic before base class
    ivw.Update();
    svw.Update();

    // Pre-update setup of base class
    BaseApplication::preUpdate();
}

void Application::update()
{
    DoMainMenu();

    if(ivw.Open)
        ivw.Show();
    
    if(svw.Open)
        svw.Show();
}

void Application::exit()
{
    BaseApplication::exit();

    ivw.Shutdown();
    svw.Shutdown();
}