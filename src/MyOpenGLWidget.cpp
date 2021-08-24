#include "MyOpenGLWidget.h"

#include <QDebug>
#include <QPainter>
#include <QMatrix4x4>
#include <QOpenGLFunctions>

// #include "shaders03.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    framework = new PandaFramework();
    framework->open_framework();

    framework->get_default_window_props(prop);

    // Snapping the panda display to top-left of parent widget
    LPoint2i p2i(0, 0);
    prop.set_origin(p2i);

    // Resize needs to be either called inside the "resize" method of custom widget
    // or can be binded with the resize function of the parent widget

    prop.set_parent_window((size_t)this->winId());

    // cout<<qw->winId()<<endl;

    window = framework->open_window(prop,0);
    window->setup_trackball();

    // Load the environment model.
    NodePath scene = window->load_model(framework->get_models(), "models/environment");
    // Reparent the model to render.
    scene.reparent_to(window->get_render());
    // Apply scale and position transforms to the model.
    scene.set_scale(0.25f, 0.25f, 0.25f);
    scene.set_pos(-8, 42, 0);
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
    prop.set_size(width, height);

    window->get_graphics_window()->request_properties(prop);

    qDebug() << width << " " << height;
}

void MyOpenGLWidget::paintGL()
{

}

