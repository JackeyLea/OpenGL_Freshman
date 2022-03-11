#include "glwindow.h"

const char *vsrc =
        "#version 330 core                         \n"
        "in vec4 vPosition;                        \n"
        "uniform mat4 mvpMatrix;                   \n"
        "void main() {                             \n"
        "   gl_Position = mvpMatrix * vPosition;   \n"
        "}                                         \n";

const char *fsrc =
        "void main() {                              \n"
        "   gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}                                          \n";

GLWindow::GLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{}

GLWindow::~GLWindow()
{
    glDeleteBuffers(1,&vboIds[0]);
}

void GLWindow::initializeGL()
{
    // 为当前环境初始化OpenGL函数
    initializeOpenGLFunctions();

    // 创建着色器程序
    program = new QOpenGLShaderProgram;
    program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,vsrc);
    program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,fsrc);
    program->bindAttributeLocation("vPosition",0);

    program->link();
    program->bind();

    glGenBuffers(1,&vboIds[0]);
    GLfloat vertices[]={
        0.5f, 0.5f, 0.0f,
       -0.5f, 0.5f, 0.0f,
        0.5f,-0.5f, 0.0f,
       -0.5f,-0.5f, 0.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER,vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    program->release();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,qMax(h,1));//设置视角范围
    m_projection.setToIdentity();
    m_projection.perspective(45,(float)w/float(h),1,1000);
    m_modelView.setToIdentity();
    update();//qt自带的界面刷新函数
}

void GLWindow::paintGL()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     program->bind();
     m_modelView.setToIdentity();
     m_modelView.translate(-1.5f,0.0f,-6.0f);
     program->setUniformValue("mvpMatrix",m_projection*m_modelView);
     glBindBuffer(GL_ARRAY_BUFFER,vboIds[0]);
     program->enableAttributeArray(0);
     program->setAttributeBuffer(0,GL_FLOAT,0,3);
     glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);// 绘制
     program->release();
}
