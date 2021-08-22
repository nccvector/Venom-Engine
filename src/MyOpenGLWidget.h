#ifndef WINDOW_H
#define WINDOW_H

#include <Corrade/Containers/Optional.h>
/* Magnum GL headers always have to be included before Qt ones */
#include <Magnum/GL/Framebuffer.h>
#include <Magnum/Platform/GLContext.h> // Platform

/* If your application is using anything from QtGui, you might get warnings
   about GLEW and errors regarding GLclampf. If that's the case, uncomment the
   following and place it as early as possible (but again *after* including
   Magnum GL headers) */
#if 1
typedef GLfloat GLclampf;
#undef __glew_h__ /* shh, Qt, shh */
#undef __GLEW_H__
#include <QtGui/qopenglfunctions.h>
/* This header is new since Qt 5.6 and gets transitively included by QtGui
   headers in recent Qt versions. This seems to be the only way to make the
   code keep compiling, but there's possibly a better solution. */
#define QOPENGLEXTRAFUNCTIONS_H
#include <QtGui/qopenglextrafunctions.h>
#endif

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

using namespace Magnum; // REMOVE THIS!!!

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
//    Q_OBJECT
public:
    explicit MyOpenGLWidget(Platform::GLContext& context, QWidget* parent = nullptr, Qt::WindowFlags f = {});
    ~MyOpenGLWidget();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;

private:
    Platform::GLContext& _context;

    QOpenGLShaderProgram *m_program;
    GLint m_attribute_coord2d, m_attribute_v_color;
    GLuint m_vbo_triangle, m_vbo_triangle_colors;
};

#endif //WINDOW_H
