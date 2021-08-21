#include "MainWindow.h"
#include "UIMainWindow.h"

#include "MyOpenGLWidget.h"

#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inserting the opengl widget
    MyOpenGLWidget *openglWidget = new MyOpenGLWidget(ui->centralwidget);
    ui->glContainer->addWidget(openglWidget);

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