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

    static Application* Get()
    {
      if(!s_Application)
        s_Application = new Application();
      
      return s_Application;
    }

    ~Application() 
    {
    }

    void OnEvent(Event& e)
    {
      // Will run only if the event is WindowCloseEvent
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
      VENOM_INFO("{0}", e);

      // Traversing layerstack backwards
      for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
      {
        (*--it)->OnEvent(e);
        if (e.Handled)
          break;
      }
    }

    void PushLayer(Layer* layer)
    {
      m_LayerStack.PushLayer(layer);
    }

    void PushOverlay(Layer* overlay)
    {
      m_LayerStack.PushOverlay(overlay);
    }

    bool OnWindowClose(WindowCloseEvent& e)
    {
      VENOM_INFO("Application::Window is closed");
      return true;
    }

    void Run()
    {
      // Simulation loop
      VENOM_INFO("Starting the loop");
      while (!glfwWindowShouldClose(m_Window->Get()))
      {
        // Render here...
        glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Layer* layer : m_LayerStack)
          layer->OnUpdate();

        m_Window->OnUpdate();
      }
    }

  private:
    Application()
    {
      // Creating a new Window
      m_Window = std::unique_ptr<Window>(new Venom::Window());

      // Binding application event to the window instance
      m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

      // Initializing window
      m_Window->Init();
    }
    
    static Application *s_Application;

    // Unique pointer to the Window Object
    std::unique_ptr<Window> m_Window;
    LayerStack m_LayerStack;

    // TO BE DEFINED IN CLIENT
    Application* CreateApplication()
    {

    }
  };

  // Initializing the singleton pointer (needs to be initialized outside class)
  Application* Application::s_Application;
}