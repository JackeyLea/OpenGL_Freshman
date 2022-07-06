#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>

#include <QtMath>

class GLWindow : public QOpenGLWidget , public QOpenGLFunctions
{
public:
    GLWindow(QWidget *parent = nullptr);
    ~GLWindow();

protected:
    void initializeGL();//初始化参数函数
    void resizeGL(int w,int h);//调整界面尺寸回调函数
    void paintGL();//绘图函数

private:
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vao,vbo;

    QMatrix4x4 m_projection,m_modelView;
};
#endif // GLWINDOW_H
