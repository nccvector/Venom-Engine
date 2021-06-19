#include <Venom.h>

/*
This is an example of a client application
*/

// Inheriting the VenomEngine Application
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

// Implementing the client function, which passes this application instance
// to VenomEngine EntryPoint
Venom::Application* Venom::CreateApplication()
{
  return new Sandbox();
}