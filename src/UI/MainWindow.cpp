#include <Magnum/Platform/GLContext.h> // Platform

#include "MainWindow.h"
#include "UIMainWindow.h"

#include "MyOpenGLWidget.h"

#include <QtCore>

using namespace Magnum; // REMOVE THIS !!!

MainWindow::MainWindow(Platform::GLContext& context, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creating the OpenGL widget
    MyOpenGLWidget *openglWidget = new MyOpenGLWidget(context);
    // Adding the widget to glContainer (layout)
    ui->glContainer->addWidget(openglWidget);

    /* On macOS, this is needed in order to use GL 4.1 instead of GL 2.1. Qt
       doesn't do that on its own, sorry. If you get only GL 3.0 on Mesa, try
       uncommenting this as well -- however be aware that with the below code,
       AMD and NVidia GPUs will get stuck at the version that's specified in
       setVersion() (such as 4.1) instead of using the latest available (4.6).
       To fix that, you'd need to detect the driver used and then either set
       the version or not depending on what the particular driver likes best.
       It's a total mess, right? */
    #ifdef CORRADE_TARGET_APPLE
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    w.setFormat(format);
    #endif

    // Loading stylesheet
    QFile file("stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    this->setStyleSheet(stylesheet);
}

MainWindow::~MainWindow()
{
    delete ui;
}