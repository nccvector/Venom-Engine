#include "MainWindow.h"
#include "UIMainWindow.h"

#include "MyOpenGLWidget.h"

#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creating the OpenGL widget
    MyOpenGLWidget *openglWidget = new MyOpenGLWidget(ui->centralwidget);
    // Adding the widget to glContainer (layout)
    ui->glContainer->addWidget(openglWidget);

    // Un-comment this if there are problems with opengl (double check the opengl 
    // linking in CMakeLists as well)
    // // Setting up the OpenGL Widget by applying surface format
    // // Need to apply format before calling show() method
    // QSurfaceFormat format;
    // format.setRenderableType(QSurfaceFormat::OpenGL);
    // openglWidget->setFormat(format);

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