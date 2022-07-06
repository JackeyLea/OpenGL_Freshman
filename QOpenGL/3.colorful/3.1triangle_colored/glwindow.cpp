#include "glwindow.h"

GLWindow::GLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{}

GLWindow::~GLWindow()
{}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();//初始化OpenGL上下文内容
    glClearColor(0.0f,0.0f,0.0f,1.0f);//将缓冲区清空为RGBA指定的颜色
    //使用颜色缓冲区、深度缓冲区、RGBA、alpha支持
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);
    glEnable(GL_DEPTH_TEST);//使用深度缓冲区测试
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,qMax(h,1));//设置视角范围
    update();//qt自带的界面刷新函数
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,0,0);
    glVertex3f(-0.5,0,0);
    glColor3f(0,1.0f,0);
    glVertex3f(0,1,0);
    glColor3f(0,0,1.0f);
    glVertex3f(0.5,0,0);
    glEnd();
}

