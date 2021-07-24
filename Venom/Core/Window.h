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

      // Creating a m_Window instance
      m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), NULL, NULL);
      if (!m_Window)
      {
        // Window or OpenGL context creation failed
        Venom::LogError("Failed to create a m_Window");
      }

      Venom::LogInfo("Window Creation Successful");

      // Setting the current context
      glfwMakeContextCurrent(m_Window);
      glfwSetWindowUserPointer(m_Window, &m_Data);
      SetVSync(true);

      // Loading openGL
      gladLoadGL();

      // Setting Callbacks
      glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
      {
        // Getting window user pointer
        WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

        WindowResizeEvent event(width, height);
        data->EventCallback(event);
        data->Width = width;
        data->Height = height;
      });

      glfwSetKeyCallback(m_Window, [](GLFWwindow *m_Window, int key, int scancode, int action, int mods)
      {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
      });

      glfwSetErrorCallback([](int code, const char *description)
      {
        Venom::LogError(description);
        throw std::invalid_argument(description);
      });
    }

    void Shutdown()
    {
      Venom::LogInfo("Destroying the m_Window");
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