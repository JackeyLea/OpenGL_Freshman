#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnUp_clicked();

    void on_btnDown_clicked();

    void on_btnLeft_clicked();

    void on_btnRight_clicked();

    void on_btnRemote_clicked();

    void on_btnClose_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
