#include "glwindow.h"

#include <GL/gl.h>

const char* vsrc="#version 330 core\n"
                 "in vec3 inPos;\n"
                 "in vec4 inColor;\n"
                 "out vec4 outColor;\n"
                 "void main(){\n"
                 "    gl_Position=vec4(inPos,1.0);\n"
                 "    outColor = inColor;\n"
                 "}";

const char* fsrc="#version 330 core\n"
                 "in vec4 outColor;\n"
                 "void main(){\n"
                 "    gl_FragColor=outColor;\n"
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
    program->bindAttributeLocation("inPos",0);
    program->bindAttributeLocation("inColor",1);
    program->link();//激活Program对象
    program->bind();

    vao.create();
    vao.bind();

    float vertices[]={
        // 位置 // 颜色
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 右下 颜色对应红色(1.0f, 0.0f, 0.0f)
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 左下 颜色对应绿色
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // 顶部 颜色对应蓝色
        0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices,sizeof(vertices)*sizeof (float));

    program->enableAttributeArray(0);
    program->enableAttributeArray(1);
    program->setAttributeBuffer(0,GL_FLOAT,0,3,6*sizeof (float));
    program->setAttributeBuffer(1,GL_FLOAT,3*sizeof(float),3,6*sizeof(float));

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
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    program->bind();
    vao.bind();
    glDrawArrays(GL_QUADS,0,4);
    vao.release();
    program->release();
}

