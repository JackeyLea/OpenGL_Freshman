#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QKeyEvent>
#include <QApplication>
#include <QSurfaceFormat>
#include <QDebug>

class GLWidget : public QOpenGLWidget,public QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent=nullptr);
    ~GLWidget();

    void setTriangleChecked(bool check);
    void setQuadChecked(bool check);

    void updown(float y);
    void leftright(float x);
    void remoteclose(float z);

    void reset();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QOpenGLShaderProgram *program;

    GLuint m_vboIds[4];

    QMatrix4x4 m_projection;
    QMatrix4x4 m_modelView;

    float rx,ry,rz,qx,qy,qz;
    bool rchecked,qchecked;
};

#endif // GLWIDGET_H
