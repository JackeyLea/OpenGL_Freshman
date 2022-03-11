#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <QImage>

class GLWindow : public QOpenGLWidget , public QOpenGLFunctions
{
public:
    GLWindow(QWidget *parent = nullptr);
    ~GLWindow();

protected:
    void initializeGL();//初始化参数函数
    void resizeGL(int w,int h);//调整界面尺寸回调函数
    void paintGL();//绘图函数
private:
    QOpenGLShaderProgram *program;

    QMatrix4x4 m_projection;
    QMatrix4x4 m_modelView;

    GLuint m_vboIds[2];
    GLuint m_texture;
    GLuint m_textureUniform;

    GLfloat m_xrot;
    GLfloat m_yrot;
    GLfloat m_zrot;
};
#endif // GLWINDOW_H
