#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <QImage>

class GLWindow : public QOpenGLWidget , public QOpenGLFunctions
{
public:
    GLWindow(QWidget *parent = nullptr);
    ~GLWindow();

    void setTexture(const QImage &image){
        _img = image;
    }

protected:
    void initializeGL();//初始化参数函数
    void resizeGL(int w,int h);//调整界面尺寸回调函数
    void paintGL();//绘图函数

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram *program;

    QImage _img;
    QOpenGLTexture *texture;

    bool zoom;
};
#endif // GLWINDOW_H
