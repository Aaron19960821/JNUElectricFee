#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "httpUtilsJNUElectric.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void Update();
    void balanceUpdate();
    void costUpdate();

private:
    //update the electronic fee
    void setDisplay(bool isOk);
    Ui::MainWindow *ui;
    QTimer* flushTimer;
    httpUtilsJNUElectric* connection;
};

#endif // MAINWINDOW_H
