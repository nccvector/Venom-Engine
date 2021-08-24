#ifndef WINDOW_H
#define WINDOW_H

#include "pandaFramework.h"
#include "pandaSystem.h"

#include "genericAsyncTask.h"
#include "asyncTaskManager.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
//    Q_OBJECT
public:
    MyOpenGLWidget(QWidget* parent);
    ~MyOpenGLWidget();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

public:
    PandaFramework *framework;
    WindowProperties prop;
    WindowFramework *window;
};

#endif //WINDOW_H
