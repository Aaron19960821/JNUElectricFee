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

private slots:
    void setDisplay(bool isOk);
    void setStatusBar(int statusCode);

signals:
    void balanceLow(bool isLow);
    void statusSignal(int statusCode);
    void balanceUpdate(double balance);
    void electricityUpdate(double electricity);
    void waterUpdated(double water);
    void waterFeeUpdate(double waterFee);
    void electricityFeeUpdate(double electricityFee);


private:
    //update the electronic fee
    Ui::MainWindow *ui;
    QTimer flushTimer;
    httpUtilsJNUElectric connection;
};

#endif // MAINWINDOW_H
