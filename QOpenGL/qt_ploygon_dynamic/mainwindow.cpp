#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnUp_clicked()
{
    ui->openGLWidget->yAdd();
    ui->openGLWidget->update();
}


void MainWindow::on_btnDown_clicked()
{
    ui->openGLWidget->ySub();
    ui->openGLWidget->update();
}


void MainWindow::on_btnLeft_clicked()
{
    ui->openGLWidget->xSub();
    ui->openGLWidget->update();
}


void MainWindow::on_btnRight_clicked()
{
    ui->openGLWidget->xAdd();
    ui->openGLWidget->update();
}


void MainWindow::on_btnRemote_clicked()
{
    ui->openGLWidget->zAdd();
    ui->openGLWidget->update();
}


void MainWindow::on_btnClose_clicked()
{
    ui->openGLWidget->zSub();
    ui->openGLWidget->update();
}

