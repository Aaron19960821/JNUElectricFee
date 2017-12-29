#ifndef UTILS_H
#define UTILS_H

#include<QMainWindow>
#include<QObject>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkCookie>
#include<QNetworkCookieJar>

class httpUtilsJNUElectric:public QObject
{
    Q_OBJECT
public:
    explicit httpUtilsJNUElectric();
    void setAccount(QString account);
    static QString GetDormitoryNumber(QString originNumber);
    void UpdateElectronicInfo();
    void Login();
    void GetBalance();
    void GetCost();
    QJsonObject* GetBalanceInfo();
    QJsonObject* GetCostInfo();
    ~httpUtilsJNUElectric();

signals:
    void balanceUpdated();
    void costUpdated();
    void networkError();

private:
    QNetworkAccessManager* manager;
    QNetworkCookieJar* cookies;
    QString userId;
    QString* account;
    QJsonObject* costInfo;
    QJsonObject* balanceInfo;

private:
};

#endif // UTILS_H
