#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

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
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_checkTriangle_clicked(bool checked);

    void on_checkQuad_clicked(bool checked);

    void on_btnUp_clicked();

    void on_btnDown_clicked();

    void on_btnLeft_clicked();

    void on_btnRight_clicked();

    void on_btnRemote_clicked();

    void on_btnClose_clicked();

    void on_btnReset_clicked();

private:
    Ui::MainWindow *ui;

    bool mFullScreen;
};

#endif // MAINWINDOW_H
