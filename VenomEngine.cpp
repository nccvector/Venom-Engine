// SYSTEM INCLUDES
#include "Application.h"

using namespace Venom::Application;

int main(int argc, char **argv)
{
    try
    {
        Application::Singleton().initApp();
        Application::Singleton().getRoot()->startRendering();
        Application::Singleton().closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}