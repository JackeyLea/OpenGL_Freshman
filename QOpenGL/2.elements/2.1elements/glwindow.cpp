#include "glwindow.h"

#include <GL/gl.h>

GLWindow::GLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{}

GLWindow::~GLWindow()
{}

void GLWindow::point()
{
    glPointSize(5.0f);//点的大小
    glBegin(GL_POINTS);
    glVertex2f(0.5f, 0.5f);
    glEnd();
    glFlush();
}

void GLWindow::line()
{
    glEnable(GL_LINE_STIPPLE);//启动虚线模式
    glLineStipple(2, 0x0F0F); //0000111100001111
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);//关闭虚线模式
    glFlush();
}

void GLWindow::circle()
{
    glBegin(GL_POLYGON); //画正n边形
    for (int i = 0; i<n; ++i)
        glVertex2f(R*qCos(2 * Pi / n*i), R*qSin(2 * Pi / n*i));
    glEnd();
    glFlush();
}

void GLWindow::triangle()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5,0,0);
    glVertex3f(0,1,0);
    glVertex3f(0.5,0,0);
    glEnd();
}

void GLWindow::quad()
{
    glBegin(GL_QUADS);
    glVertex3f(-0.5,0.5,0);
    glVertex3f(0.5,0.5,0);
    glVertex3f(0.5,-0.5,0);
    glVertex3f(-0.5,-0.5,0);
    glEnd();
}

void GLWindow::star()
{
    GLfloat a = 1 / (2 - 2 * cos(72 * Pi / 180));
    GLfloat bx = a * cos(18 * Pi / 180);
    GLfloat by = a * sin(18 * Pi / 180);
    GLfloat cy = -a * cos(18 * Pi / 180);
    GLfloat
        PointA[2] = { 0, a },
        PointB[2] = { bx, by },
        PointC[2] = { 0.5, cy },
        PointD[2] = { -0.5, cy },
        PointE[2] = { -bx, by };
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2fv(PointA);
    glVertex2fv(PointC);
    glVertex2fv(PointE);
    glVertex2fv(PointB);
    glVertex2fv(PointD);
    glEnd();
    glFlush();
}

void GLWindow::mySin()
{
    GLfloat x;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);// 画x轴
    glVertex2f(1.0f, 0.0f);
    glVertex2f(0.0f, -1.0f);// 画y轴
    glVertex2f(0.0f, 1.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (x = -1.0f / factor; x<1.0f / factor; x += 0.01f)
    {
        glVertex2f(x*factor, sin(x)*factor);
    }
    glEnd();
    glFlush();
}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();//初始化OpenGL上下文内容
    glClearColor(0.0f,0.0f,0.0f,1.0f);//将缓冲区清空为RGBA指定的颜色
    //使用颜色缓冲区、深度缓冲区、RGBA、alpha支持
    glEnable(GL_DEPTH_TEST);//使用深度缓冲区测试
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,qMax(h,1));//设置视角范围
    update();//qt自带的界面刷新函数
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if(i>100){
        i=0;
        if(j>=6){
            j=0;
        }else j++;
    }

    switch(j){
    case 0:
        point();
        break;
    case 1:
        line();
        break;
    case 2:
        circle();
        break;
    case 3:
        triangle();
        break;
    case 4:
        quad();
        break;
    case 5:
        star();
        break;
    case 6:
        mySin();
        break;
    }
    i++;

    update();
}

