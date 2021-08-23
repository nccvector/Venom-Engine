#include "MyOpenGLWidget.h"

#include <QPainter>
#include <QMatrix4x4>
#include <QOpenGLFunctions>

// #include "shaders03.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
}

MyOpenGLWidget::~MyOpenGLWidget()
{

}

void MyOpenGLWidget::initializeGL()
{

}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    // Currently we are not handling width/height changes
    (void)width;
    (void)height;
}

void MyOpenGLWidget::paintGL()
{

}

