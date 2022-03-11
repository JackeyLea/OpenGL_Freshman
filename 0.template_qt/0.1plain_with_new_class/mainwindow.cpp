#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    glWidget = new GLWidget(this->centralWidget());
    glWidget->resize(this->centralWidget()->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    glWidget->resize(this->centralWidget()->size());
}

