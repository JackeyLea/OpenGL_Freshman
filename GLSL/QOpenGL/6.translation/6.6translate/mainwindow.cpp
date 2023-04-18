#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mFullScreen(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_checkTriangle_clicked(bool checked)
{
    ui->openGLWidget->setTriangleChecked(checked);
}

void MainWindow::on_checkQuad_clicked(bool checked)
{
    ui->openGLWidget->setQuadChecked(checked);
}

void MainWindow::on_btnUp_clicked()
{
    ui->openGLWidget->updown(0.5);
}

void MainWindow::on_btnDown_clicked()
{
    ui->openGLWidget->updown(-0.5);
}

void MainWindow::on_btnLeft_clicked()
{
    ui->openGLWidget->leftright(-0.5);
}

void MainWindow::on_btnRight_clicked()
{
    ui->openGLWidget->leftright(0.5);
}

void MainWindow::on_btnRemote_clicked()
{
    ui->openGLWidget->remoteclose(-0.5);
}

void MainWindow::on_btnClose_clicked()
{
    ui->openGLWidget->remoteclose(0.5);
}

void MainWindow::on_btnReset_clicked()
{
    ui->checkQuad->setChecked(true);
    ui->checkTriangle->setChecked(true);
    ui->openGLWidget->reset();
}
