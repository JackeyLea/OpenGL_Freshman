#include "glwidget.h"

QVector3D globalAmbient = QVector3D(1.2f,1.0f,2.0f);//全局环境光

//自定义灯光
QVector3D lightPos = QVector3D(2.5f,2.0f,10.0f);//自定义灯光位置
QVector3D eyePos = QVector3D(0.0f,0.0f,8.0f);

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , mFullScreen(false)
    ,m_xrot(0.0f)
    ,m_yrot(0.0f)
    ,m_zrot(0.0f)
{
    img = QImage(":/glsl/bird.jpg");
    QSurfaceFormat format;
    format.setSamples(24);

    setFormat(format);
    showNormal();
}

GLWidget::~GLWidget()
{
    program->deleteLater();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();//初始化OpenGL上下文内容
    glClearColor(0.0f,0.0f,0.0f,1.0f);//将缓冲区清空为RGBA指定的颜色
    //使用颜色缓冲区、深度缓冲区、RGBA、alpha支持
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_RGBA|GL_ALPHA_BITS);
    glDisable(GL_DEPTH_TEST);//使用深度缓冲区测试
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendColor(1.0f,1.0f,1.0f,0.5f);
    glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE,GL_SRC_ALPHA,GL_ONE);

    qDebug()<<"Used OpenGL Version: "<<context()->format().majorVersion()<<"."<<context()->format().minorVersion();

    qDebug()<<"OpenGL info: ";
    qDebug()<<"             VENDOR:        "<<(const char*)glGetString(GL_VENDOR);
    qDebug()<<"             RENDERER:      "<<(const char*)glGetString(GL_RENDERER);
    qDebug()<<"             VERSION:       "<<(const char*)glGetString(GL_VERSION);
    qDebug()<<"             GLSL VERSION:  "<<(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/glsl/vsrc.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/glsl/fsrc.frag");
    program->bindAttributeLocation("pos",0);
    program->bindAttributeLocation("texCoord",1);
    program->bindAttributeLocation("a_normal",2);
    program->link();//激活Program对象
    program->bind();

    vao.create();
    vao.bind();

    float vertices[]={
        // Front face
        -1.0f, -1.0f, 1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,
        1.0f, -1.0f, 1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,
        1.0f, 1.0f, 1.0f,1.0f,1.0f,0.0f,0.0f,1.0f,
        -1.0f, 1.0f, 1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,

        // Back face
        -1.0f, -1.0f, -1.0f,1.0f,0.0f,0.0f,0.0f,-1.0f,
        -1.0f, 1.0f, -1.0f,1.0f,1.0f,0.0f,0.0f,-1.0f,
        1.0f, 1.0f, -1.0f,0.0f,1.0f,0.0f,0.0f,-1.0f,
        1.0f, -1.0f, -1.0f,0.0f,0.0f,0.0f,0.0f,-1.0f,

        // Top face
        -1.0f, 1.0f, -1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
        -1.0f, 1.0f, 1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,
        1.0f, 1.0f, 1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
        1.0f, 1.0f, -1.0f,1.0f,1.0f,0.0f,1.0f,0.0f,

        // Bottom face
        -1.0f, -1.0f, -1.0f,1.0f,1.0f,0.0f,-1.0f,0.0f,
        1.0f, -1.0f, -1.0f,0.0f,1.0f,0.0f,-1.0f,0.0f,
        1.0f, -1.0f, 1.0f,0.0f,0.0f,0.0f,-1.0f,0.0f,
        -1.0f, -1.0f, 1.0f,1.0f,0.0f,0.0f,-1.0f,0.0f,

        // Right face
        1.0f, -1.0f, -1.0f,1.0f,0.0f,1.0f,0.0f,0.0f,
        1.0f, 1.0f, -1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,
        1.0f, 1.0f, 1.0f,0.0f,1.0f,1.0f,0.0f,0.0f,
        1.0f, -1.0f, 1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,

        // Left face
        -1.0f, -1.0f, -1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,
        -1.0f, -1.0f, 1.0f,1.0f,0.0f,-1.0f,0.0f,0.0f,
        -1.0f, 1.0f, 1.0f,1.0f,1.0f,-1.0f,0.0f,0.0f,
        -1.0f, 1.0f, -1.0f,0.0f,1.0f,-1.0f,0.0f,0.0f,
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices,sizeof(vertices)*sizeof(float));

    program->enableAttributeArray(0);
    program->enableAttributeArray(1);
    program->enableAttributeArray(2);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 8*sizeof(GLfloat));
    program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 2, 8*sizeof(GLfloat));
    program->setAttributeBuffer(2,GL_FLOAT,5*sizeof(GLfloat),3,8*sizeof(GLfloat));

    texture = new QOpenGLTexture(img);
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);

    vao.release();
    vbo.release();
    program->release();
}

/* 下面的代码的作用是不管窗口的大小是否已经改变(假定您没有使用全屏模式)都重新设置OpenGL场景的大小。
 *甚至您无法改变窗口的大小时(例如您在全屏模式下)，它至少仍将运行一次--在程序开始时设置我们的透视图。
 *OpenGL场景的尺寸将被设置成它显示时所在窗口的大小。 */
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,qMax(h,1));//设置视角范围
    m_projection.setToIdentity();
    m_projection.perspective(45,(float)w/float(h),1,1000);
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

    program->bind();
    vbo.bind();

    QMatrix4x4 viewMatrix;
    viewMatrix.lookAt(eyePos,QVector3D(0,0,-20),QVector3D(0,1,0));

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(0.0f, 0.0f, -5.0f);
    modelMatrix.rotate(m_xrot, 1.0, 0.0, 0.0);
    modelMatrix.rotate(m_yrot, 0.0, 1.0, 0.0);
    modelMatrix.rotate(m_zrot, 0.0, 0.0, 1.0);

    QMatrix4x4 mvpMatrix = m_projection * viewMatrix * modelMatrix;
    program->setUniformValue("mvpMatrix", mvpMatrix);
    program->setUniformValue("modelMatrix",modelMatrix);
    program->setUniformValue("viewPos",eyePos);
    program->setUniformValue("lightPos",lightPos);
    program->setUniformValue("lightColor",globalAmbient);

    if(texture->isCreated()) texture->bind();

    glDrawArrays(GL_QUADS,0,24);

    vbo.release();
    program->release();

    m_xrot+=0.1f;
    m_yrot+=0.1f;
    m_zrot+=0.1f;
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
    }
}
