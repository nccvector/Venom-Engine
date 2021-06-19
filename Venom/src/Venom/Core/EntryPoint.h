#pragma once

// External Application pointer
extern Venom::Application* Venom::CreateApplication();

int main()
{
  Venom::Log::Init();

  auto app = Venom::CreateApplication();
  app->Run();
  delete app;
}