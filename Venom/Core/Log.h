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
    static std::shared_ptr<spdlog::logger> &Get();

  private:
    static std::shared_ptr<spdlog::logger> s_Logger;
  };
}

// LOGGING MACROS
#define VENOM_TRACE(...)    ::Venom::Log::Get()->trace(__VA_ARGS__)
#define VENOM_INFO(...)     ::Venom::Log::Get()->info(__VA_ARGS__)
#define VENOM_WARN(...)     ::Venom::Log::Get()->warn(__VA_ARGS__)
#define VENOM_ERROR(...)    ::Venom::Log::Get()->error(__VA_ARGS__)
#define VENOM_CRITICAL(...) ::Venom::Log::Get()->critical(__VA_ARGS__)