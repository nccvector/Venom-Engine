#pragma once

namespace Venom {

	class Application
	{
	public:
    static Application* Get();
    static void Run();

  private:
    unsigned int Width;
    unsigned int Height;
    std::string Title;

    // Window pointer
    Application* app = NULL;

    // Constructor
    Application ();
	};

}