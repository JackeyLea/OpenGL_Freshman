#include "glwindow.h"

const char* vertexSource =
        "#version 330\n"
        "layout(location = 0) in vec2 position;\n"
        "layout(location = 1) in vec2 texCoord;\n"
        "uniform mat4 matrix;\n"
        "out vec4 texc;\n"
        "void main( void )\n"
        "{\n"
        " gl_Position = matrix * vec4(position, 0.0, 1.0);\n"
        " texc = vec4(texCoord, 0.0, 1.0);\n"
        "}\n";

const char* fragmentSource =
        "#version 330\n"
        "uniform sampler2D texture;\n"
        "in vec4 texc;\n"
        "out vec4 fragColor;\n"
        "void main( void )\n"
        "{\n"
        " fragColor = texture2D(texture, texc.st);\n"
        "}\n";


GLWindow::GLWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setFocus();
    setMouseTracking(true);
}

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
    program->addShaderFromSourceCode(QOpenGLShader::Vertex,vertexSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment,fragmentSource);
    program->bindAttributeLocation("position",0);
    program->link();
    program->bind();

    vao.create();
    vao.bind();

    float vertex[]={ -1.0, 1.0,  0.0, 0.0,
                     1.0, 1.0,  1.0, 0.0,
                     1.0, -1.0, 1.0, 1.0,
                    -1.0, -1.0, 0.0, 1.0 };

    vbo.create();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.bind();
    vbo.allocate(vertex,sizeof(vertex)*sizeof(float));

    program->enableAttributeArray(0);
    program->enableAttributeArray(1);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 4*sizeof(GLfloat));
    program->setAttributeBuffer(1, GL_FLOAT, 2*sizeof(GLfloat), 2, 4*sizeof(GLfloat));

    texture = new QOpenGLTexture(_img);

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

    if(_img.isNull()) return;

    QMatrix4x4 m;
    float l=-1.0;
    float r=1.0f;
    float t=-1.0f;
    float b=1.0f;
    if(zoom){
        // calculate new ortho limits
        QPoint gp = QCursor::pos();
        QPoint p = this->mapFromGlobal(gp);

        float px = p.x() / (float) this->width();
        float py = 1.0 - p.y() / (float) this->height(); // remember to flip y

        // rescale to -1,1
        px = (px - 0.5) * 2.;
        py = (py - 0.5) * 2.;

        // modify lrtb
        l = px - 0.1;
        r = px + 0.1;
        t = py - 0.1;
        b = py + 0.1;
    }
    m.ortho(l,r,t,b,-1.0,1.0);

    program->bind();
    vao.bind();
    program->setUniformValue("matrix",m);
    if(texture->isCreated()) texture->bind();
    glDrawArrays(GL_TRIANGLE_FAN,0,4);
    vao.release();
    program->release();
}

void GLWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        zoom = true;
        return;
    }
    QWidget::keyPressEvent(event);
}

void GLWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        zoom=false;
        return;
    }
    QWidget::keyReleaseEvent(event);
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    update();
}
