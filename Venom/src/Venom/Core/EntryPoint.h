#pragma once

// External Application pointer
extern Venom::Application* Venom::CreateApplication();

int main()
{
  std::cout << "Venom Engine Started" << std::endl;
  auto app = Venom::CreateApplication();
  app->Run();
  delete app;
}