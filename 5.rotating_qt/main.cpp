#include "glwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWindow w;
    QSurfaceFormat surfaceFmt;
    surfaceFmt.setSamples(4);
    w.setFormat(surfaceFmt);
    w.show();
    return a.exec();
}
