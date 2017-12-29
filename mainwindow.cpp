#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httpUtilsJNUElectric.h"
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette overallStyle;
    overallStyle.setColor(QPalette::Background, Qt::black);
    this->setPalette(overallStyle);

    QPalette wordStyle;
    wordStyle.setColor(QPalette::WindowText, QColor(220,250,250));
    ui->balanceLabel->setPalette(wordStyle);
    ui->dormitoryNote->setPalette(wordStyle);
    ui->electricPrice->setPalette(wordStyle);
    ui->waterPrice->setPalette(wordStyle);
    ui->electricPrice->setPalette(wordStyle);
    ui->electricUsed->setPalette(wordStyle);
    ui->waterUsed->setPalette(wordStyle);
    ui->label->setPalette(wordStyle);

    setDisplay(false);

    ui->balanceDisplay->display(0.00);
    ui->electricDisplay->display(0.00);
    ui->electricFeeDisplay->display(0.00);
    ui->waterDisplay->display(0.00);
    ui->waterPriceDisplay->display(0.00);

    this->flushTimer = new QTimer(this);
    connect(flushTimer, SIGNAL(timeout()), this, SLOT(Update()));
    this->flushTimer->start(200000);

    connect(ui->flushButton, SIGNAL(released()), this, SLOT(Update()));

    this->connection = new httpUtilsJNUElectric();
    connect(this->connection, SIGNAL(balanceUpdated()), this, SLOT(balanceUpdate()));
    connect(this->connection, SIGNAL(costUpdated()), this, SLOT(costUpdate()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete connection;
}

void MainWindow::Update()
{
   QString dormitoryNumber = this->ui->dormitoryInput->text();
   dormitoryNumber = httpUtilsJNUElectric::GetDormitoryNumber(dormitoryNumber);

   this->connection->setAccount(dormitoryNumber);
   this->connection->Login();
}

void MainWindow::balanceUpdate()
{
    QJsonObject balanceInfo = *(this->connection->GetBalanceInfo());
    QJsonArray resultList = balanceInfo["d"].toObject()["ResultList"].toArray();
    QJsonArray roomInfo = resultList[0].toObject()["roomInfo"].toArray();
    double balance = roomInfo[1].toObject()["keyValue"].toString().toDouble();

    QJsonArray energyUnitPrice = resultList[0].toObject()["energyUnitPrice"].toArray();
    double electricUnitPrice = energyUnitPrice[0].toObject()["keyValue"].toString().mid(0,5).toDouble();
    double waterUnitPrice = energyUnitPrice[1].toObject()["keyValue"].toString().mid(0,1).toDouble();

    qDebug() << energyUnitPrice[0].toObject()["keyValue"].toString().mid(0,5);
    this->ui->balanceDisplay->display(balance);
    this->ui->electricFeeDisplay->display(electricUnitPrice);
    this->ui->waterPriceDisplay->display(waterUnitPrice);

    if(balance < 20.0)
    {
        setDisplay(false);
    }
    else
    {
        setDisplay(true);
    }
}

void MainWindow::costUpdate()
{
    QJsonObject costInfo = *(this->connection->GetCostInfo());
    QJsonArray resultList = costInfo["d"].toObject()["ResultList"].toArray();
    QJsonArray electricityDetail = resultList[0].toObject()["energyCostDetails"].toArray();
    double electricityUsed = electricityDetail[0].toObject()["billItemValues"].toArray()[0].toObject()["energyValue"].toDouble();

    qDebug() << resultList[0].toObject();
    QJsonArray coldWaterDetail = resultList[1].toObject()["energyCostDetails"].toArray();
    double coldWaterUsed = coldWaterDetail[0].toObject()["billItemValues"].toArray()[0].toObject()["energyValue"].toDouble();

    QJsonArray hotWaterDetail = resultList[2].toObject()["energyCostDetails"].toArray();
    double hotWaterUsed = coldWaterDetail[0].toObject()["billItemValues"].toArray()[0].toObject()["energyValue"].toDouble();

    this->ui->waterDisplay->display(hotWaterUsed+coldWaterUsed);
    this->ui->electricDisplay->display(electricityUsed);

}

void MainWindow::setDisplay(bool isOk)
{
    QPalette displayStyle;
    if(isOk)
    {
        displayStyle.setColor(QPalette::WindowText, Qt::green);
        displayStyle.setColor(QPalette::Background, Qt::green);
        ui->balanceDisplay->setStyleSheet("border: 2px solid green");
        ui->electricDisplay->setStyleSheet("border: 2px solid green");
        ui->electricFeeDisplay->setStyleSheet("border: 2px solid green");
        ui->waterDisplay->setStyleSheet("border: 2px solid green");
        ui->waterPriceDisplay->setStyleSheet("border: 2px solid green");
    }
    else
    {
        displayStyle.setColor(QPalette::WindowText, Qt::red);
        displayStyle.setColor(QPalette::Background, Qt::red);
        ui->balanceDisplay->setStyleSheet("border: 2px solid red");
        ui->electricDisplay->setStyleSheet("border: 2px solid red");
        ui->electricFeeDisplay->setStyleSheet("border: 2px solid red");
        ui->waterDisplay->setStyleSheet("border: 2px solid red");
        ui->waterPriceDisplay->setStyleSheet("border: 2px solid red");
    }
    ui->balanceDisplay->setPalette(displayStyle);
    ui->electricDisplay->setPalette(displayStyle);
    ui->electricFeeDisplay->setPalette(displayStyle);
    ui->waterDisplay->setPalette(displayStyle);
    ui->waterPriceDisplay->setPalette(displayStyle);
}
