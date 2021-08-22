#include <Magnum/Platform/GLContext.h> // May need for Platform

#include "MainWindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    Platform::GLContext context{NoCreate};

    QApplication a(argc, argv);
    MainWindow w{context};

    w.show();
    return a.exec();
}