#include "Application.h"

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

}

void Application::update()
{
    DoMainMenu();
}