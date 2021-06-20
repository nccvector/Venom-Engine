#pragma once

#include <memory.h>
#include <spdlog/spdlog.h>

#include "Core.h"

namespace Venom
{
  class Log
  {
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

  private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
  };

  // Venom-Engine Core Logging Functions
  void CoreLogInfo(std::string msg);
  void CoreLogWarn(std::string msg);
  void CoreLogError(std::string msg);

  // Venom-Engine App Logging Functions
  void LogInfo(std::string msg);
  void LogWarn(std::string msg);
  void LogError(std::string msg);
}