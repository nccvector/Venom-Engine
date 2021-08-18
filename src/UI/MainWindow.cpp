#include "MainWindow.h"
#include "UIMainWindow.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

protected:
    void initializeGL() override
    {
        initializeOpenGLFunctions();
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    }

    void resizeGL(int w, int h) override
    {

    }

    void paintGL() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inserting the opengl widget
    MyGLWidget *openglWidget = new MyGLWidget(nullptr);
    ui->glContainer->addWidget(openglWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}