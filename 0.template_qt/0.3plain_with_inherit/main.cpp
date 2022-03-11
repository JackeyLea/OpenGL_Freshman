#include "glwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWindow w;
    QSurfaceFormat fmt;
    fmt.setSamples(4);
    w.setFormat(fmt);
    w.show();
    return a.exec();
}
