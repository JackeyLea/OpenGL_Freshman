#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QKeyEvent>

#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *);

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    GLWidget *glWidget;

    bool mFullScreen;
};

#endif // MAINWINDOW_H
