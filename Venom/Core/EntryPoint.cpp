#include "Core/Log.h"
#include "Core/Window.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
  Venom::Log::Init(); // INITIALIZING LOG IMPORTANT!!!

  Venom::LogInfo("Initializing glfw");

  if (!glfwInit())
  {
      // Handle initialization failure
      Venom::LogError("glfwInit() Failed");
  }

  // std::cout << "GOT INIT :)";

  GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
  if (!window)
  {
      // Window or OpenGL context creation failed
      Venom::LogError("Window Creation Failed");
  }

  // Setting the current context
  glfwMakeContextCurrent(window);

  // Setting the input callbacks
  glfwSetKeyCallback(window, key_callback);

  // Simulation loop
  while (!glfwWindowShouldClose(window))
  {
      // Keep running

      glfwSwapBuffers(window);
      glfwPollEvents();
  }

  // Terminating the glfw
  glfwDestroyWindow(window);
  glfwTerminate();

  // auto app = Venom::CreateApplication();
  // app->Run();
  // delete app;

  return 0;
}