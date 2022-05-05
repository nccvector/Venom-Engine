#include "Application.h"
#include "Console.h"

int main()
{
    LOG_INIT();
    LOG("[error] Starting application...");
    Application app;
    app.run();

    return 0;
}