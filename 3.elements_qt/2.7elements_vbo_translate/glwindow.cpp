#include "glwindow.h"

#define GLSL_VERSION "#version 330 core\n"

#define GET_GLSTR(x) GLSL_VERSION#x

const char *vsrc = GET_GLSTR(
        in vec4 aPos;
        uniform mat4 mvpMatrix;
        void main(){
            gl_Position = mvpMatrix * aPos;
        }
);
const char *fsrc=GET_GLSTR(
        void main(){
            gl_FragColor = vec4(1.0,1.0,1.0,1.0f);
        }
);

GLWindow::GLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{}

GLWindow::~GLWindow()
{
    glDeleteBuffers(2,&m_vboIds[0]);
}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();//初始化OpenGL上下文内容
    glClearColor(0.0f,0.0f,0.0f,1.0f);//将缓冲区清空为RGBA指定的颜色
    //使用颜色缓冲区、深度缓冲区、RGBA、alpha支持
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);
    glEnable(GL_DEPTH_TEST);//使用深度缓冲区测试

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(QOpenGLShader::Vertex,vsrc);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment,fsrc);
    program->bindAttributeLocation("aPos",0);
    program->link();//激活Program对象
    program->bind();

    glGenBuffers(2, &m_vboIds[0]);
    GLfloat triangleVertices[] = {
        0.0f, 1.0f, 0.0f,
        -1.0f,-1.0f, 0.0f,
        1.0f,-1.0f, 0.0f,
    };
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    GLfloat quadVertices[] = {
         1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
         1.0f,-1.0f, 0.0f,
        -1.0f,-1.0f, 0.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

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
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);

    program->bind();
    m_modelView.setToIdentity();
    m_modelView.translate(-1.5f, 0.0f, -6.0f);
    program->setUniformValue("mvpMatrix", m_projection * m_modelView);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_modelView.translate(3.0f, 0.0f, 0.0f);
    program->setUniformValue("mvpMatrix", m_projection * m_modelView);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    program->release();
}

