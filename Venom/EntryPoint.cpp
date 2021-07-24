#include "Core/Application.h"

int main()
{
  Venom::Log::Init(); // INITIALIZING LOG IMPORTANT!!!

  // Creating an application
  Venom::Application app;
  app.Run();

  return 0;
}