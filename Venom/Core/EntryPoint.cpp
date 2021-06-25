#include "Core/Log.h"
#include "Core/Window.h"

int main()
{
  Venom::Log::Init(); // INITIALIZING LOG IMPORTANT!!!

  // Creating a new Window
  Venom::Window *window = new Venom::Window();

  // Running the window
  window->Run();

  return 0;
}