#include <string>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

namespace Venom
{
  class Window
  {
  public:
    static Window *Get(); // Returns a window pointer
    void Run();

  private:
    static int s_Width, s_Height;
    static std::string s_Title;

    static Window *window; // Unique window instance

    // Constructor
    Window();

    // Private Functions
    void Init();
    void Loop();
  };
}