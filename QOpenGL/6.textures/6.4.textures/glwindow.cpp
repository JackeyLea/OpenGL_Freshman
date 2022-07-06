#include "glwindow.h"

GLWindow::GLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
    ,m_xrot(0.0f)
    ,m_yrot(0.0f)
    ,m_zrot(0.0f)
{}

GLWindow::~GLWindow()
{
    glDeleteTextures(1, &m_texture);
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
    program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/resources/vsrc.glsl");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/resources/fsrc.glsl");
    program->bindAttributeLocation("aPos",0);
    program->bindAttributeLocation("inTexCoord",1);
    program->link();//激活Program对象
    program->bind();

    QImage image(":/resources/NeHe.bmp");
    image = image.convertToFormat(QImage::Format_BGR888);
    image = image.mirrored();
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_textureUniform = program->uniformLocation("texture");

    GLfloat quadVertices[] = {
        // Front face
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,

        // Back face
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        // Top face
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,

        // Bottom face
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        // Right face
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        // Left face
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
    };

    GLfloat quadCoord[] = {
        // Front face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        // Back face
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        // Top face
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        // Bottom face
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        // Right face
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        // Left face
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };
    glVertexAttribPointer(0, 3,GL_FLOAT, 0, 0, quadVertices);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, quadCoord);
    glEnableVertexAttribArray(1);
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
    m_modelView.translate(0.0f, 0.0f, -5.0f);
    m_modelView.rotate(m_xrot, 1.0, 0.0, 0.0);
    m_modelView.rotate(m_yrot, 0.0, 1.0, 0.0);
    m_modelView.rotate(m_zrot, 0.0, 0.0, 1.0);
    program->setUniformValue("mvpMatrix", m_projection * m_modelView);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform1i(m_textureUniform,0);
    program->release();

    m_xrot+=0.1f;
    m_yrot+=0.1f;
    m_zrot+=0.1f;

    update();
}
