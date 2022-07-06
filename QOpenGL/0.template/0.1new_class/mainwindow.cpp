#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
