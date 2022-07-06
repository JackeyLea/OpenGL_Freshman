#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QApplication>
#include <QSurfaceFormat>
#include <QDebug>

#include <QtMath>

class GLWidget : public QOpenGLWidget,public QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void point();
    void line();
    void circle();
    void triangle();
    void quad();
    void star();
    void mySin();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);

private:
    bool mFullScreen;

    uint mode;

    int i;
    int j;

    float R;
    float Pi;
    int n;

    float factor;
};

#endif // GLWIDGET_H
