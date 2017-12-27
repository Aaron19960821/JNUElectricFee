#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"

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

    QPalette displayStyle;
    displayStyle.setColor(QPalette::WindowText, Qt::red);
    displayStyle.setColor(QPalette::Background, Qt::red);

    ui->balanceDisplay->setSegmentStyle(QLCDNumber::Flat);
    ui->electricDisplay->setSegmentStyle(QLCDNumber::Flat);
    ui->electricFeeDisplay->setSegmentStyle(QLCDNumber::Flat);
    ui->waterDisplay->setSegmentStyle(QLCDNumber::Flat);
    ui->waterPriceDisplay->setSegmentStyle(QLCDNumber::Flat);

    ui->balanceDisplay->setStyleSheet("border:2px solid red;");
    ui->electricDisplay->setStyleSheet("border:2px solid red;");
    ui->electricFeeDisplay->setStyleSheet("border:2px solid red;");
    ui->waterDisplay->setStyleSheet("border:2px solid red;");
    ui->waterPriceDisplay->setStyleSheet("border:2px solid red;");

    ui->balanceDisplay->setPalette(displayStyle);
    ui->electricDisplay->setPalette(displayStyle);
    ui->electricFeeDisplay->setPalette(displayStyle);
    ui->waterDisplay->setPalette(displayStyle);
    ui->waterPriceDisplay->setPalette(displayStyle);

    ui->balanceDisplay->display(0.00);
    ui->electricDisplay->display(0.00);
    ui->electricFeeDisplay->display(0.00);
    ui->waterDisplay->display(0.00);
    ui->waterPriceDisplay->display(0.00);

    this->flushTimer = new QTimer(this);
    connect(flushTimer, SIGNAL(timeout()), SLOT(update()));
    this->flushTimer->start(200000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update()
{
   QString dormitoryNumber = this->ui->dormitoryInput->text();
   dormitoryNumber = utils::GetDormitoryNumber(dormitoryNumber);
}
