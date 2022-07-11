#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QKeyEvent>
#include <QApplication>
#include <QSurfaceFormat>
#include <QDebug>
#include <QImage>
#include <QOpenGLTexture>

class GLWidget : public QOpenGLWidget,public QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);

private:
    bool mFullScreen;

    QImage img;

    QOpenGLTexture *texture;

    QOpenGLShaderProgram *program;
    QOpenGLBuffer vao,vbo;

    QMatrix4x4 m_projection;
    QMatrix4x4 m_modelView;
    GLfloat m_xrot;
    GLfloat m_yrot;
    GLfloat m_zrot;
};

#endif // GLWIDGET_H
