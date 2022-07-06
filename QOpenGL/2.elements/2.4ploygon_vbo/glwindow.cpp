#include "glwindow.h"

const char *vsrc =
        "#version 330 core\n"
        "in vec4 vPosition;                        \n"
        "void main() {                             \n"
        "   gl_Position = vPosition;               \n"
        "}                                         \n";

const char *fsrc =
        "void main() {                              \n"
        "   gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}                                          \n";

GLWindow::GLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{}

GLWindow::~GLWindow()
{}

void GLWindow::initializeGL()
{
    // 为当前环境初始化OpenGL函数
    initializeOpenGLFunctions();

    // 创建着色器程序
    program = new QOpenGLShaderProgram;
    program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,vsrc);
    program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,fsrc);

    program->link();
    program->bind();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,qMax(h,1));//设置视角范围
    update();//qt自带的界面刷新函数
}

void GLWindow::paintGL()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     // 顶点位置
     GLfloat vertices[] = {
         -0.5f, 0.5f,
         -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f, 0.5f
     };

     GLuint vPosition = program->attributeLocation("vPosition");
     glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, vertices);
     glEnableVertexAttribArray(vPosition);

     // 绘制
     glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
