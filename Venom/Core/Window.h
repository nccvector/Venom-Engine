#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "Log.h"

namespace Venom
{
  // Namespace functions
  void error_callback(int code, const char *description)
  {
    // TODO Implement logging here
    throw std::invalid_argument(description);
  }

  class Window
  {
  public:
    static Window *Get()
    {
      if (window == NULL)
      {
        // Creating an instance if null
        window = new Window();
      }

      return window;
    }

    static void Run()
    {

      Window::Init();
      Window::Loop();
    }

    static void Init()
    {
      // Attaching error callback for logging
      glfwSetErrorCallback(error_callback);

      // Initialize glfw
      if (!glfwInit())
      {
        // Implement logging here
        throw std::invalid_argument("Cannot initialize glfw");
      }

      // Configure glfw
      glfwDefaultWindowHints();
      glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

    static void Loop()
    {
    }

  private:
    unsigned int Width;
    unsigned int Height;
    std::string Title;

    // Window pointer
    static Window *window;

    // Constructor
    Window()
    {
      Window::Width = 640;
      Window::Height = 480;
      Window::Title = "My Application";

      // Must start with NULL
      Window::window = NULL;
    }
  };

}