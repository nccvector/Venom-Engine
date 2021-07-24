#include "Core/Log.h"
#include "Core/Window.h"

namespace Venom
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

  class Application
  {
  public:
    Application()
    {
      // Creating a new Window
      m_Window = std::unique_ptr<Window>(new Venom::Window());

      // Binding application event to the window instance
      m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

      // Initializing window
      m_Window->Init();
    }
    ~Application() 
    {
    }

    void OnEvent(Event& e)
    {
      Venom::LogInfo("Application Event Triggered");
    }

    void Run()
    {
      // Simulation loop
      Venom::LogInfo("Starting the loop");
      while (!glfwWindowShouldClose(m_Window->Get()))
      {
        // Render here...
        glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window->OnUpdate();
      }
    }

  private:
    // Unique pointer to the Window Object
    std::unique_ptr<Window> m_Window;

    // TO BE DEFINED IN CLIENT
    Application* CreateApplication()
    {

    }
  };
}

int main()
{
  Venom::Log::Init(); // INITIALIZING LOG IMPORTANT!!!

  // Creating an application
  Venom::Application app;
  app.Run();

  return 0;
}