#pragma once

// External Application pointer
extern Venom::Application* Venom::CreateApplication();

int main()
{
  Venom::Log::Init(); // INITIALIZING LOG IMPORTANT!!!

  Venom::CoreLogInfo("This is Core Info");
  Venom::CoreLogWarn("This is Core Warning");
  Venom::CoreLogError("This is Core Error");

  Venom::LogInfo("This is Client Info");
  Venom::LogWarn("This is Client Warning");
  Venom::LogError("This is Client Error");

  auto app = Venom::CreateApplication();
  app->Run();
  delete app;
}