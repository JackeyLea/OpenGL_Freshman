#include "glwindow.h"

#include <QApplication>
#include <QImage>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);

    QImage img(":/resource/bird.jpg");

    GLWindow w;
    w.setTexture(img);
    w.show();
    return a.exec();
}
