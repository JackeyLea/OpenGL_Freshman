#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QtMath>

class GLWindow : public QOpenGLWidget , public QOpenGLFunctions
{
public:
    GLWindow(QWidget *parent = nullptr);
    ~GLWindow();

    void point();
    void line();
    void circle();
    void triangle();
    void quad();
    void star();
    void mySin();

protected:
    void initializeGL();//初始化参数函数
    void resizeGL(int w,int h);//调整界面尺寸回调函数
    void paintGL();//绘图函数

private:
    int i=0;
    int j=0;

    float R=0.5;
    float Pi=acos(-1);
    int n=60;

    float factor=0.1f;
};
#endif // GLWINDOW_H
