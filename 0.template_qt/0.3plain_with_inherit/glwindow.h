#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GLWindow : public QOpenGLWidget , public QOpenGLFunctions
{
public:
    GLWindow(QWidget *parent = nullptr);
    ~GLWindow();

protected:
    void initializeGL();//初始化参数函数
    void resizeGL(int w,int h);//调整界面尺寸回调函数
    void paintGL();//绘图函数
};
#endif // GLWINDOW_H