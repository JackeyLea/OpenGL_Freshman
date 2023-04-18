#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , mFullScreen(false)
    , mode(0)
    , i(0)
    , j(0)
    , R(0.5)
    , Pi(qAcos(-1))
    , n(60)
    , factor(0.1f)
{
    QSurfaceFormat format;
    format.setSamples(24);

    setFormat(format);
    showNormal();
}

GLWidget::~GLWidget()
{}

void GLWidget::point()
{
    glPointSize(5.0f);//点的大小
    glBegin(GL_POINTS);
    glVertex2f(0.5f, 0.5f);
    glEnd();
    glFlush();
}

void GLWidget::line()
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

void GLWidget::circle()
{
    glBegin(GL_POLYGON); //画正n边形
    for (int i = 0; i<n; ++i)
        glVertex2f(R*qCos(2 * Pi / n*i), R*qSin(2 * Pi / n*i));
    glEnd();
    glFlush();
}

void GLWidget::triangle()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5,0,0);
    glVertex3f(0,1,0);
    glVertex3f(0.5,0,0);
    glEnd();
}

void GLWidget::quad()
{
    glBegin(GL_QUADS);
    glVertex3f(-0.5,0.5,0);
    glVertex3f(0.5,0.5,0);
    glVertex3f(0.5,-0.5,0);
    glVertex3f(-0.5,-0.5,0);
    glEnd();
}

void GLWidget::star()
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

void GLWidget::mySin()
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

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();//初始化OpenGL上下文内容
    glClearColor(0.0f,0.0f,0.0f,1.0f);//将缓冲区清空为RGBA指定的颜色
    //使用颜色缓冲区、深度缓冲区、RGBA、alpha支持
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);
    glEnable(GL_DEPTH_TEST);//使用深度缓冲区测试

    qDebug()<<"Used OpenGL Version: "<<context()->format().majorVersion()<<"."<<context()->format().minorVersion();

    qDebug()<<"OpenGL info: ";
    qDebug()<<"             VENDOR:        "<<(const char*)glGetString(GL_VENDOR);
    qDebug()<<"             RENDERER:      "<<(const char*)glGetString(GL_RENDERER);
    qDebug()<<"             VERSION:       "<<(const char*)glGetString(GL_VERSION);
    qDebug()<<"             GLSL VERSION:  "<<(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

/* 下面的代码的作用是不管窗口的大小是否已经改变(假定您没有使用全屏模式)都重新设置OpenGL场景的大小。
 *甚至您无法改变窗口的大小时(例如您在全屏模式下)，它至少仍将运行一次--在程序开始时设置我们的透视图。
 *OpenGL场景的尺寸将被设置成它显示时所在窗口的大小。 */
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,qMax(h,1));//设置视角范围
    update();//qt自带的界面刷新函数
}

/* 你想绘制的任何内容都是在下面的函数中
 *以后的每个教程中我都会在例程的此处增加新的代码。
 *如果您对OpenGL已经有所了解的话，您可以在glLoadIdentity()调用之后，
 *试着添加一些OpenGL代码来创建基本的图形。
 *目前我们所作的全部就是将屏幕清除成我们前面所决定的颜色，清除深度缓存并且重置场景。
 *此处并没有绘制如何东西。 */
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清除屏幕和深度缓存
    glLoadIdentity();	// 重置当前的模型观察矩阵

    switch(mode){
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

    update();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_F2:
    {
        mFullScreen=!mFullScreen;
        if(mFullScreen){
            showFullScreen();
        }else{
            showNormal();
        }
        update();
        break;
    }
    case Qt::Key_Escape:
    {
        qApp->exit();
        break;
    }
    case Qt::Key_Space:
    {
        mode = mode>=6?mode=0:++mode;
        break;
    }
    }
}
