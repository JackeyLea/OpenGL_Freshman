#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

class GLWidget : public QOpenGLWidget,public QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent=nullptr);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // GLWIDGET_H
