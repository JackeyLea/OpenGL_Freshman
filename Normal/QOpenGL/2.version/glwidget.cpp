#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , mFullScreen(false)
{
    QSurfaceFormat format;
    format.setSamples(24);

    setFormat(format);
    showNormal();
}

GLWidget::~GLWidget()
{}

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
    }
}
