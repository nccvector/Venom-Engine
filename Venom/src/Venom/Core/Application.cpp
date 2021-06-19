#include "Application.h"
#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

namespace Venom
{
  Application::Application()
  {
    spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:>8} aligned, {:<8} aligned", "right", "left");
  }

  Application::~Application()
  {

  }

  void Application::Run()
  {
    while (true){
      // std::cout << "Running" << std::endl;
    };
  }
} // namespace Venom
