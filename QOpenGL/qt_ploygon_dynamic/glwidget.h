#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class GLWidget : public QOpenGLWidget,public QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent=nullptr);

    void xAdd();
    void xSub();
    void yAdd();
    void ySub();
    void zAdd();
    void zSub();

protected:
    void initializeGL();//初始化参数函数
    void resizeGL(int w,int h);//调整界面尺寸回调函数
    void paintGL();//绘图函数

private:
    GLfloat m_x,m_y,m_z;
};

#endif // GLWIDGET_H
