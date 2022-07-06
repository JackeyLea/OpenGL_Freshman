#include "glwindow.h"

#include <GL/gl.h>

const char* vsrc="#version 330 core\n"
                 "in vec3 pos;\n"
                 "uniform mat4 mvpMatrix;\n"
                 "void main(){\n"
                 "    gl_Position=mvpMatrix * vec4(pos,1.0);\n"
                 "}";

const char* fsrc="void main(){\n"
                 "    gl_FragColor=vec4(1.0f,1.0f,1.0f,1.0f);\n"
                 "}";

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
    glEnable(GL_DEPTH_TEST);//使用深度缓冲区测试

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(QOpenGLShader::Vertex,vsrc);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment,fsrc);
    program->bindAttributeLocation("pos",0);
    program->link();//激活Program对象
    program->bind();

    vao.create();
    vao.bind();

    float vertices[]={
        // 位置 // 颜色
        0.5f, -0.5f, 0.0f,// 右下
        -0.5f, -0.5f, 0.0f, // 左下
        0.0f, 0.5f, 0.0f// 顶部
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices,sizeof(vertices)*sizeof (float));

    program->enableAttributeArray(0);
    program->setAttributeBuffer(0,GL_FLOAT,0,3,3*sizeof(float));

    vao.release();
    vbo.release();
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
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    program->bind();
    vao.bind();
    m_modelView.setToIdentity();
    m_modelView.translate(-1.5f,0.0f,-6.0f);
    program->setUniformValue("mvpMatrix",m_projection*m_modelView);
    glDrawArrays(GL_TRIANGLES,0,3);
    vao.release();
    program->release();
}
