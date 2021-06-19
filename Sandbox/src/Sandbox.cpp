#include "Venom.h"

class Sandbox : public Venom::Application
{
  public:
  Sandbox()
  {

  }

  ~Sandbox()
  {

  }
};

int main()
{
  Sandbox* sandbox = new Sandbox();
  sandbox->Run();
  delete sandbox;
}