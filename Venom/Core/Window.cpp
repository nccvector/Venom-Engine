#include "Window.h"
#include "Log.h"

namespace Venom
{
  Window::~Window()
  {
    Window::Shutdown();
  }

  void Window::OnUpdate()
  {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
  }

  void Window::SetVSync(bool enabled) 
  { 
    if (enabled)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);

    m_Data.VSync = enabled;  
  }

  // Init Create Destroy Shutdown
  void Window::Init(const WindowProps& props)
  {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    VENOM_INFO("Initializing glfw...");

    if (!glfwInit())
    {
      // Handle initialization failure
      VENOM_ERROR("glfw initialization failed!");
    }

    // Configure glfw
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    VENOM_INFO("Successfully initialized glfw");

    // Creating a m_Window instance
    m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), NULL, NULL);
    if (!m_Window)
    {
      // Window or OpenGL context creation failed
      VENOM_INFO("Failed to create a m_Window");
    }

    VENOM_INFO("Window Creation Successful");

    // Setting the current context
    glfwMakeContextCurrent(m_Window);

    // Doing GLAD stuff
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    VENOM_INFO("GLAD initialization status: {0}", status);

    glfwSetWindowUserPointer(m_Window, &m_Data);
    Window::SetVSync(true);

    // Loading openGL
    gladLoadGL();

    // Setting Callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
      // Getting window user pointer
      WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
      data->Width = width;
      data->Height = height;

      WindowResizeEvent event(width, height);
      data->EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
      // Getting window user pointer
      WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
      
      WindowCloseEvent event;
      data->EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
      // Getting window user pointer
      WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

      switch(action)
      {
        case GLFW_PRESS:
        {
          KeyPressedEvent event(key, 0);
          data->EventCallback(event);
          break;
        }
        case GLFW_RELEASE:
        {
          KeyReleasedEvent event(key);
          data->EventCallback(event);
          break;
        }
        case GLFW_REPEAT:
        {
          KeyPressedEvent event(key, 1);
          data->EventCallback(event);
          break;
        }
      }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
    {
      // Getting window user pointer
      WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

      switch(action)
      {
        case GLFW_PRESS:
        {
          MouseButtonPressedEvent event(button);
          data->EventCallback(event);
          break;
        }
        case GLFW_RELEASE:
        {
          MouseButtonReleasedEvent event(button);
          data->EventCallback(event);
          break;
        }
        // REPEAT TO BE IMPLEMENTED YET
      }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
      // Getting window user pointer
      WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

      MouseScrolledEvent event((float)xOffset, (float)yOffset);
      data->EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
    {
      // Getting window user pointer
      WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

      MouseMovedEvent event((float)xPos, (float)yPos);
      data->EventCallback(event);
    });

    glfwSetErrorCallback([](int code, const char *description)
    {
      VENOM_ERROR(description);
      throw std::invalid_argument(description);
    });
  }

  void Window::Shutdown()
  {
    VENOM_INFO("Destroying the m_Window");
    // Terminating the glfw
    glfwDestroyWindow(m_Window);
    glfwTerminate();
  }
}