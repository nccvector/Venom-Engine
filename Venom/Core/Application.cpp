#include "Core/Application.h"

namespace Venom
{
  // PUBLIC FUNCTIONS
  // Returns an app pointer
  Application* Application::Get()
  {
    if (Application::app == NULL)
    {
      // Creating an instance if null
      Application::app = new Window();
    }

    return Application::app;
  }

  void Application::Run()
  {

    Application::Init();
    Application::Loop();
  }

  void Application::Init()
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

  void Application::Loop()
  {
  }

  // PRIVATE FUNCTIONS
  // Constructor
  Application::Application()
  {
    Application::s_Width = 640;
    Application::s_Height = 480;
    Application::s_Title = "My Application";

    Application::app = NULL;
  }
}