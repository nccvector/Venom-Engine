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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap front and back buffers
    glfwSwapBuffers(window->Get());
    
    // Poll for and process events
    glfwPollEvents();
  }

  delete(window);

  return 0;
}