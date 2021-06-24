#pragma once

#include <memory.h>
#include <spdlog/spdlog.h>

namespace Venom
{
  class Log
  {
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

  private:
    static std::shared_ptr<spdlog::logger> s_Logger;
  };

  // Venom-Engine Logging Functions
  void LogInfo(std::string msg);
  void LogWarn(std::string msg);
  void LogError(std::string msg);
}