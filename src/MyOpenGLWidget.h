#ifndef WINDOW_H
#define WINDOW_H

#include "pandaFramework.h"
#include "pandaSystem.h"

#include "genericAsyncTask.h"
#include "asyncTaskManager.h"

#include <QResizeEvent>
#include <QtWidgets/QWidget>

class MyOpenGLWidget : public QWidget
{
//    Q_OBJECT
public:
    MyOpenGLWidget(QWidget* parent);
    ~MyOpenGLWidget();

protected:
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

public:
    PandaFramework *framework;
    WindowProperties prop;
    WindowFramework *window;
};

#endif //WINDOW_H
