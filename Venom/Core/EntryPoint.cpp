#include "Core/Log.h"
#include "Core/Window.h"

int main()
{
  Venom::Log::Init(); // INITIALIZING LOG IMPORTANT!!!

  // Creating a new Window
  Venom::Window *window = new Venom::Window();
  window->Init();

  // Simulation loop
  Venom::LogInfo("Starting the loop");
  while (!glfwWindowShouldClose(window->Get()))
  {
    // Render here...
    

    // Swap front and back buffers
    glfwSwapBuffers(window->Get());
    
    // Poll for and process events
    glfwPollEvents();
  }

  delete(window);

  return 0;
}