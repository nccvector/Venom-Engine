#include "MyOpenGLWidget.h"

#include <QPainter>
#include <QMatrix4x4>
#include <QOpenGLFunctions>

#include "shaders03.h"

using namespace Magnum; // REMOVE THIS!!!

MyOpenGLWidget::MyOpenGLWidget(Platform::GLContext& context, QWidget* parent, Qt::WindowFlags f): QOpenGLWidget{parent, f}, _context(context) {
    /* TODO: Add your context format setup code here */
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    delete m_program;
    glDeleteBuffers(1, &m_vbo_triangle);
    glDeleteBuffers(1, &m_vbo_triangle_colors);
}

void MyOpenGLWidget::initializeGL()
{
    _context.create();

    /* TODO: Add your initialization code here */

    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vs_source);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs_source);
    m_program->link();
    m_attribute_coord2d = m_program->attributeLocation("coord2d");
    m_attribute_v_color = m_program->attributeLocation("v_color");
    // VBO Handling
    glGenBuffers(1, &m_vbo_triangle);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glGenBuffers(1, &m_vbo_triangle_colors);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_triangle_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors, GL_STATIC_DRAW);

    /* Clean up Magnum state when giving control back to Qt */
    GL::Context::current().resetState(GL::Context::State::EnterExternal);
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    // Currently we are not handling width/height changes
    (void)width;
    (void)height;
}

void MyOpenGLWidget::paintGL()
{
    /* Reset state to avoid Qt affecting Magnum */
    GL::Context::current().resetState(GL::Context::State::ExitExternal);

    /* Using framebuffer provided by Qt as default framebuffer */
    auto qtDefaultFramebuffer = GL::Framebuffer::wrap(defaultFramebufferObject(), {{}, {width(), height()}});

    qtDefaultFramebuffer.clear(GL::FramebufferClear::Color);

    /* TODO: Add your drawing code here */

//    glClearColor(.4f, .7f, .1f, 0.5f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();
    glEnableVertexAttribArray(m_attribute_v_color);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_triangle_colors);
    glVertexAttribPointer(m_attribute_v_color, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(m_attribute_coord2d);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_triangle);
    glVertexAttribPointer(m_attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(m_attribute_coord2d);
    glDisableVertexAttribArray(m_attribute_v_color);
    m_program->release();

    /* Clean up Magnum state when giving control back to Qt */
    GL::Context::current().resetState(GL::Context::State::EnterExternal);
}

