#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    m_x=m_y=m_z=0.0f;
}

void GLWidget::xAdd()
{
    m_x = m_x+0.1;
    update();
}

void GLWidget::xSub()
{
    m_x = m_x-0.1;
    update();
}

void GLWidget::yAdd()
{
    m_y = m_y+0.1;
    update();
}

void GLWidget::ySub()
{
    m_y = m_y-0.1;
    update();
}

void GLWidget::zAdd()
{
    m_z = m_z+0.01;
    update();
}

void GLWidget::zSub()
{
    m_z = m_z-0.01;
    update();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();//初始化OpenGL上下文内容
    glClearColor(0.0f,0.0f,0.0f,1.0f);//将缓冲区清空为RGBA指定的颜色
    //使用颜色缓冲区、深度缓冲区、RGBA、alpha支持
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);
    glEnable(GL_DEPTH_TEST);//使用深度缓冲区测试
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,qMax(h,1));//设置视角范围
    update();//qt自带的界面刷新函数
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);
    glLoadIdentity();

    glTranslatef(m_x,m_y,m_z);

    glBegin(GL_TRIANGLES);
    glColor3ub(255,0,0);
    glVertex3f(-0.5,0,0);
    glColor3ub(0,255,0);
    glVertex3f(0,1,0);
    glColor3ub(0,0,255);
    glVertex3f(0.5,0,0);
    glEnd();

    update();
}
