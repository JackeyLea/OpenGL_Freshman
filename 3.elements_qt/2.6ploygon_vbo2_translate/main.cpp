#include "glwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWindow w;
    w.resize(500,500);
    w.show();
    return a.exec();
}
