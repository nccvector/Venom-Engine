#include "Application.h"
#include "Gui/ImGuiLayer.h"

namespace Venom
{
  // Initializing the PRIVATE singleton pointer (needs to be initialized outside class)
  Application* Application::s_Application = nullptr;

  // PUBLIC
  Application* Application::Get()
  {
    if(!Application::s_Application)
      Application::s_Application = new Application();
    
    return Application::s_Application;
  }

  Application::~Application()
  {
  }

  void Application::OnEvent(Event& e)
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

  void Application::PushLayer(Layer* layer)
  {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* overlay)
  {
    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
  }

  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    VENOM_INFO("Application::Window is closed");
    return true;
  }

  void Application::Run()
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

  // PRIVATE
  Application::Application()
  {
    // Creating a new Window
      m_Window = std::unique_ptr<Window>(new Venom::Window());

      // Binding application event to the window instance
      m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

      // Initializing window
      m_Window->Init();

      // Pushing ImGui Overlay
      Application::PushOverlay(new ImGuiLayer);
  }
}