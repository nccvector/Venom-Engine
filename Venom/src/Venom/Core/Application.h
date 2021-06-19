#pragma once

#include "Core.h"

namespace Venom
{
  class Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();
  };

  Application* CreateApplication(); // TO BE DEFINED IN CLIENT
} // namespace Venom
