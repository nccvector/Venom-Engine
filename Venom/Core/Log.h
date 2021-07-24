#pragma once

#include <memory.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Venom
{
  class Log
  {
  public:
    static void Init()
    {
      // Setting logging pattern and intializing the client and core loggers
      spdlog::set_pattern("%^[%T] %n: %v%$");

      s_Logger = spdlog::stdout_color_mt("Venom-Engine");
      s_Logger->set_level(spdlog::level::trace);
    }

    inline static std::shared_ptr<spdlog::logger> &GetLogger() { return s_Logger; }

  private:
    static std::shared_ptr<spdlog::logger> s_Logger;
  };

  // Initializing the s_Logger static var outside of the class
  std::shared_ptr<spdlog::logger> Log::s_Logger;
}

// LOGGING MACROS
#define VENOM_TRACE(...)    ::Venom::Log::GetLogger()->trace(__VA_ARGS__)
#define VENOM_INFO(...)     ::Venom::Log::GetLogger()->info(__VA_ARGS__)
#define VENOM_WARN(...)     ::Venom::Log::GetLogger()->warn(__VA_ARGS__)
#define VENOM_ERROR(...)    ::Venom::Log::GetLogger()->error(__VA_ARGS__)
#define VENOM_CRITICAL(...) ::Venom::Log::GetLogger()->critical(__VA_ARGS__)