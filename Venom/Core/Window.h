#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Venom
{
  // Namespace functions
  void error_callback(int code, const char *description)
  {
    Venom::LogError(description);
    throw std::invalid_argument(description);
  }

  static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  class Window
  {
  public:
    // Constructor
    Window()
    {
      Width = 640;
      Height = 480;
      Title = "Venom Engine";

      // Must start with NULL
      window = NULL;
    }

    ~Window()
    {
      Destroy();
    }

    GLFWwindow *Get()
    {
      return window;
    }

    void Init()
    {
      Venom::LogInfo("Initializing glfw...");

      if (!glfwInit())
      {
        // Handle initialization failure
        Venom::LogError("glfw initialization failed!");
      }

      // Configure glfw
      glfwDefaultWindowHints();
      glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

      Venom::LogInfo("Successfully initialized glfw");

      // Creating a window instance
      window = glfwCreateWindow(Width, Height, Title, NULL, NULL);
      if (!window)
      {
        // Window or OpenGL context creation failed
        Venom::LogError("Failed to create a window");
      }

      Venom::LogInfo("Window Creation Successful");

      // Setting the current context
      glfwMakeContextCurrent(window);

      // Loading openGL
      gladLoadGL();

      // Setting the input callbacks
      glfwSetKeyCallback(window, key_callback);

      // Attaching error callback for logging
      glfwSetErrorCallback(error_callback);
    }

    void Destroy()
    {
      Venom::LogInfo("Destroying the window");
      // Terminating the glfw
      glfwDestroyWindow(window);
      glfwTerminate();
    }

  private:
    unsigned int Width;
    unsigned int Height;
    const char *Title;

    // Window pointer
    GLFWwindow *window;
  };

}