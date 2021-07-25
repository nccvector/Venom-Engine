#include "Log.h"

namespace Venom
{
  // Initializing the s_Logger static var outside of the class
  std::shared_ptr<spdlog::logger> Log::s_Logger;

  std::shared_ptr<spdlog::logger> &Log::Get()
  {
    if(!Log::s_Logger)
    {
      // Setting logging pattern and intializing the client and core loggers
      spdlog::set_pattern("%^[%T] %n: %v%$");

      Log::s_Logger = spdlog::stdout_color_mt("Venom-Engine");
      Log::s_Logger->set_level(spdlog::level::trace);
    }

    return Log::s_Logger;
  }
}