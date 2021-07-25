#include "Core/Application.h"
#include "Gui/ImGuiLayer.h"

int main()
{
  Venom::Log::Init(); // INITIALIZING LOG IMPORTANT!!!

  // Getting application singleton
  Venom::Application *app = Venom::Application::Get();
  app->Run();

  return 0;
}