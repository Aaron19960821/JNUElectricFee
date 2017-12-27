#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void Update();
    ~MainWindow();

private:
    //update the electronic fee
    Ui::MainWindow *ui;
    QTimer* flushTimer;
};

#endif // MAINWINDOW_H
