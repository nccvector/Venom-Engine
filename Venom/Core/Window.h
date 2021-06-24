#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace Venom {

	class Window
	{
	public:
    static Window* Get();
    static void Run();
    static void Init();
    static void Loop();

  private:
    unsigned int Width;
    unsigned int Height;
    std::string Title;

    // Window pointer
    Window* window = NULL;

    // Constructor
    Window ();
	};

}