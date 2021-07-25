#pragma once

#include "Core/Log.h"
#include "Core/Window.h"
#include "LayerStack.h"

namespace Venom
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

  class Application
  {
  public:

    // Get singleton pointer
    static Application* Get();

    ~Application();

    void OnEvent(Event& e);
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    bool OnWindowClose(WindowCloseEvent& e);
    void Run();

  private:
    Application();

    static Application *s_Application;

    // Unique pointer to the Window Object
    std::unique_ptr<Window> m_Window;
    LayerStack m_LayerStack;

    // TO BE DEFINED IN CLIENT
    Application* CreateApplication()
    {

    }
  };
}