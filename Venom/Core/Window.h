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

    ~Window();

    void OnUpdate();

    inline unsigned int GetWidth() { return m_Data.Width; }
    inline unsigned int GetHeight() { return m_Data.Height; }

    inline GLFWwindow *Get() { return m_Window; }

    // Window attributes
    inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

    void SetVSync(bool enabled);

    inline bool IsVSync() const { return m_Data.VSync; }

    // Init Create Destroy Shutdown
    void Init(const WindowProps& props = WindowProps());
    void Shutdown();

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