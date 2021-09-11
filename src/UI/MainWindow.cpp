#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creating the OpenGL widget
    ogreWindow = new QTOgreWindow();

    // Creating a widget out of Window object
    QWidget* renderingContainer = QWidget::createWindowContainer(ogreWindow);

    // Adding the widget to glContainer (layout)
    ui->glContainer->addWidget(renderingContainer);

    // // Un-comment this if there are problems with opengl (double check the opengl 
    // // linking in CMakeLists as well)
    // // // Setting up the OpenGL Widget by applying surface format
    // // // Need to apply format before calling show() method
    // // QSurfaceFormat format;
    // // format.setRenderableType(QSurfaceFormat::OpenGL);
    // // openglWidget->setFormat(format);
}

MainWindow::~MainWindow()
{
    delete ui;
}