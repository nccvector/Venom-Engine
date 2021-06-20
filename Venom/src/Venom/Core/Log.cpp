#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Venom
{
  std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
  std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

  void Log::Init()
  {
    // Setting logging pattern and intializing the client and core loggers
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_CoreLogger = spdlog::stdout_color_mt("VENOM");
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("APP");
    s_ClientLogger->set_level(spdlog::level::trace);
  }

  // Venom-Engine Core Logging Functions
  void CoreLogInfo(std::string msg){ Log::GetCoreLogger()->info(msg); }
  void CoreLogWarn(std::string msg) { Log::GetCoreLogger()->warn(msg); }
  void CoreLogError(std::string msg) { Log::GetCoreLogger()->error(msg); }

  // Venom-Engine App Logging Functions
  void LogInfo(std::string msg) { Log::GetClientLogger()->info(msg); }
  void LogWarn(std::string msg) { Log::GetClientLogger()->warn(msg); }
  void LogError(std::string msg) { Log::GetClientLogger()->error(msg); }
}