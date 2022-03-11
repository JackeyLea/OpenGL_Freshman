#include "glwindow.h"

const char* vsrc="#version 330 core\n"
                 "in vec3 inPos;\n"
                 "void main(){\n"
                 "    gl_Position=vec4(inPos,1.0);\n"
                 "}";

const char* fsrc="#version 330 core\n"
                 "void main(){\n"
                 "    gl_FragColor=vec4(1.0f,0.0f,1.0f,1.0f);\n"
                 "}";

GLWindow::GLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{}

GLWindow::~GLWindow()
{}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();//初始化OpenGL上下文内容
    glClearColor(1.0f,1.0f,0.0f,1.0f);//将缓冲区清空为RGBA指定的颜色
    //使用颜色缓冲区、深度缓冲区、RGBA、alpha支持
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);
    glEnable(GL_DEPTH_TEST);//使用深度缓冲区测试

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(QOpenGLShader::Vertex,vsrc);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment,fsrc);
    program->bindAttributeLocation("inPos",0);
    program->link();//激活Program对象
    program->bind();

    //3.初始化VAO,设置顶点数据状态(顶点，法线，纹理坐标等)
    vao.create();
    vao.bind();

    //2.初始化VBO,将顶点数据存储到buffer中,等待VAO激活后才能释放
    float vertices[]={
        // 位置
        0.5f, -0.5f, 0.0f,// 右下
        -0.5f, -0.5f, 0.0f,// 左下
        0.0f, 0.5f, 0.0f// 顶部
    };
    vbo.create();
    vbo.bind();//绑定到当前的OpenGL上下文
    vbo.allocate(vertices,sizeof(vertices)*sizeof(float));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    program->enableAttributeArray(0);
    program->enableAttributeArray(1);
    program->setAttributeBuffer(0,GL_FLOAT,0,3,3*sizeof (float));

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

    program->bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES,0,3);
    vao.release();
    program->release();
}

