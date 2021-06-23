#include <Window.h>

namespace Venom
{
  // Namespace functions
  void error_callback(int code, const char *description)
  {
    // TODO Implement logging here
    throw std::invalid_argument(description);
  }

  // PUBLIC FUNCTIONS
  // Returns a window pointer
  Window *Window::Get()
  {
    if (Window::window == NULL)
    {
      // Creating an instance if null
      Window::window = new Window();
    }

    return Window::window;
  }

  void Window::Run()
  {
    Window::Init();
    Window::Loop();
  }

  void Window::Init()
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

  void Window::Loop()
  {
  }

  // PRIVATE FUNCTIONS
  // Constructor
  Window::Window()
  {
    Window::s_Width = 640;
    Window::s_Height = 480;
    Window::s_Title = "My Application";

    Window::window = NULL;
  }
}