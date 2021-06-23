#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
  if (!glfwInit())
  {
      // Handle initialization failure
      std::cout << "GOT FAILED :(";
  }

  std::cout << "GOT INIT :)";

  GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
  if (!window)
  {
      // Window or OpenGL context creation failed
      std::cout << "WINDOW CREATION FAILED";
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

  return 0;
}