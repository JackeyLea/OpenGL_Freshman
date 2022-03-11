#include "glwindow.h"

GLWindow::GLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{
    img = QImage(":/resources/bird.jpg");
}

GLWindow::~GLWindow()
{}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();//初始化OpenGL上下文内容
    glClearColor(0.0f,0.0f,0.0f,1.0f);//将缓冲区清空为RGBA指定的颜色
    //使用颜色缓冲区、深度缓冲区、RGBA、alpha支持
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);
    glEnable(GL_DEPTH_TEST);//使用深度缓冲区测试

    program = new QOpenGLShaderProgram;
    program->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":/resources/vsrc.glsl");
    program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":/resources/fsrc.glsl");
    program->bindAttributeLocation("position",0);
    program->bindAttributeLocation("texCoord",1);
    program->link();//激活Program对象
    program->bind();

    vao.create();
    vao.bind();

    float vertex[]={
        -1.0, 1.0,  0.0, 0.0,
        1.0, 1.0,  1.0, 0.0,
        1.0, -1.0, 1.0, 1.0,
        -1.0, -1.0, 0.0, 1.0
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertex,sizeof(vertex)*sizeof(float));

    program->enableAttributeArray(0);
    program->enableAttributeArray(1);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 4*sizeof(GLfloat));
    program->setAttributeBuffer(1, GL_FLOAT, 2*sizeof(GLfloat), 2, 4*sizeof(GLfloat));

    texture = new QOpenGLTexture(img);

    vao.release();
    vbo.release();
    program->release();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,qMax(h,1));//设置视角范围
    update();//qt自带的界面刷新函数
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);

    if(img.isNull()) return;

    program->bind();
    vao.bind();
    if(texture->isCreated()) texture->bind();
    glDrawArrays(GL_TRIANGLE_FAN,0,4);
    vao.release();
    program->release();

    update();
}
