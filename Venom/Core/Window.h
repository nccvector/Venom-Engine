#pragma once

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Venom
{
  struct WindowProps
  {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "Venom Engine",
                unsigned int width = 800,
                unsigned int height = 600)
                : Title(title), Width(width), Height(height)
    {  
    }
  };

  class Window
  {
  public:
    using EventCallbackFn = std::function<void(Event&)>;

    ~Window() 
    {
      Shutdown();
    }

    void OnUpdate()
    {
      glfwPollEvents();
      glfwSwapBuffers(m_Window);
    }

    inline unsigned int GetWidth() { return m_Data.Width; }
    inline unsigned int GetHeight() { return m_Data.Height; }

    inline GLFWwindow *Get() { return m_Window; }

    // Window attributes
    inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

    void SetVSync(bool enabled) 
    { 
      if (enabled)
        glfwSwapInterval(1);
      else
        glfwSwapInterval(0);

      m_Data.VSync = enabled;  
    }

    inline bool IsVSync() const { return m_Data.VSync; }

    // Init Create Destroy Shutdown
    void Init(const WindowProps& props = WindowProps())
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
      SetVSync(true);

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

    void Shutdown()
    {
      VENOM_INFO("Destroying the m_Window");
      // Terminating the glfw
      glfwDestroyWindow(m_Window);
      glfwTerminate();
    }

  private:

    // Window pointer
    GLFWwindow *m_Window;

    struct WindowData
    {
      std::string Title;
      unsigned int Width, Height;
      bool VSync;

      EventCallbackFn EventCallback;
    };

    WindowData m_Data;
  };
}