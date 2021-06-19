#include "Application.h"
#include <iostream>

namespace Venom
{
  Application::Application()
  {

  }

  Application::~Application()
  {

  }

  void Application::Run()
  {
    while (true){
      std::cout << "Running" << std::endl;
    };
  }
} // namespace Venom
