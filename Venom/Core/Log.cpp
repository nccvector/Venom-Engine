#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Venom
{
  std::shared_ptr<spdlog::logger> Log::s_Logger;

  void Log::Init()
  {
    // Setting logging pattern and intializing the client and core loggers
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_Logger = spdlog::stdout_color_mt("Venom-Engine");
    s_Logger->set_level(spdlog::level::trace);
  }

  // Venom-Engine Logging Functions
  void LogInfo(std::string msg) { Log::GetLogger()->info(msg); }
  void LogWarn(std::string msg) { Log::GetLogger()->warn(msg); }
  void LogError(std::string msg) { Log::GetLogger()->error(msg); }
}