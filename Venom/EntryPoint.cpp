#include "Core/Application.h"
#include "Gui/ImGuiLayer.h"

int main()
{
  // Getting application singleton pointer
  Venom::Application *app = Venom::Application::Get();
  app->Run();

  return 0;
}