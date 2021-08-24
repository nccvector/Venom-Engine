#include "MainWindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    // this is the main loop
    Thread *current_thread = Thread::get_current_thread();
    while (w.openglWidget->framework->do_frame(current_thread)) {
        a.processEvents();
    }

    w.openglWidget->framework->close_framework();

    current_thread->prepare_for_exit();

    return 0;
}
