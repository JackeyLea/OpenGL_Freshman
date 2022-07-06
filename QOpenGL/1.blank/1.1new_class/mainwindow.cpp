#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mFullScreen(false)
{
    ui->setupUi(this);

    glWidget = new GLWidget(this);
    glWidget->resize(this->size());
}

MainWindow::~MainWindow()
{
    glWidget->deleteLater();
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    glWidget->resize(this->size());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
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
