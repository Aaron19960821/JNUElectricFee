#include "urls.h"
#include "httpUtilsJNUElectric.h"
#include "cryptutils.h"

#include <QObject>
#include <QJsonObject>
#include <QNetworkCookieJar>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDateTime>

httpUtilsJNUElectric::~httpUtilsJNUElectric()
{
}

httpUtilsJNUElectric::httpUtilsJNUElectric()
{
    this->manager = new QNetworkAccessManager();
    this->cookies = new QNetworkCookieJar();
    this->manager->setCookieJar(this->cookies);
}

void httpUtilsJNUElectric::setAccount(QString account)
{
    this->account = new QString(account);
}

QJsonObject* httpUtilsJNUElectric::GetBalanceInfo()
{
    return this->balanceInfo;
}

QJsonObject* httpUtilsJNUElectric::GetCostInfo()
{
    return this->costInfo;
}

//get the standard dormitory number from the input
QString httpUtilsJNUElectric::GetDormitoryNumber(QString originNumber)
{
    int buildingIndexStart = originNumber.lastIndexOf(QChar('T'));
    int roomIndexStart = originNumber.lastIndexOf(QChar('-'));
    if(buildingIndexStart>=0 && roomIndexStart>=0 && buildingIndexStart < roomIndexStart - 1)
    {
        int buildingIndex = originNumber.mid(buildingIndexStart+1, roomIndexStart-buildingIndexStart-1).toInt();
        int roomIndex = originNumber.mid(roomIndexStart+1, originNumber.length()-roomIndexStart-1).toInt();
        return QString('T').append(QString::number(buildingIndex)).append(QString::number(roomIndex).rightJustified(4, '0'));
    }
    else
    {
        return QString("Format Error");
    }
}

void httpUtilsJNUElectric::Login()
{
    QNetworkRequest* request = new QNetworkRequest();
    request->setUrl(QUrl(Urls::loginUrl));

    request->setRawHeader("Host", "10.136.2.5");
    request->setRawHeader("Referer", "http://10.136.2.5/jnuweb/");
    request->setRawHeader("Content-Type", "application/json; charset=utf-8");
    request->setRawHeader("Connection", "keep-alive");
    request->setRawHeader("X-Requested-With", "XMLHttpRequest");
    request->setRawHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36");
    request->setRawHeader("Accept", "*/*");
    request->setRawHeader("Accept-Encoding", "deflate");
    request->setRawHeader("Token", cryptUtils::getIdToken());
    request->setRawHeader("DateTime", QDateTime::currentDateTime().
                          toString("yyyy-mm-dd hh:mm:ss").toUtf8());

    QJsonObject* requestContent = new QJsonObject();
    requestContent->insert("user", QJsonValue(*account));
    requestContent->insert("password", QJsonValue(Urls::initPassword));

    QNetworkReply* reply = manager-> post(*request, QJsonDocument(*requestContent).toJson(QJsonDocument::Compact));

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        QList<QNetworkCookie> cookies = manager->cookieJar()->cookiesForUrl(QUrl(Urls::loginUrl));
        manager->cookieJar()->setCookiesFromUrl(cookies, QUrl(Urls::balanceUrl));
        manager->cookieJar()->setCookiesFromUrl(cookies, QUrl(Urls::costUrl));
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if(statusCode.toInt() == 200)
        {
            QByteArray responseContent = reply->readAll();
            QJsonObject content = QJsonDocument::fromJson(responseContent).object();
            QJsonArray resultList = content["d"].toObject()["ResultList"].toArray();
            int customerId = resultList[0].toObject()["customerId"].toInt();
            this -> userId = QString::number(customerId);
            this ->GetBalance();
            this ->GetCost();
        }
    });
}

void httpUtilsJNUElectric::GetBalance()
{
    QNetworkRequest* request = new QNetworkRequest();
    QByteArray dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8();
    request->setUrl(Urls::balanceUrl);

    request->setRawHeader("Accept","*/*");
    request->setRawHeader("Accept-Encoding", "deflate");
    request->setRawHeader("Accept-Language", "zh-CN,zh;q=0.9,en;q=0.8");
    request->setRawHeader("Content-Type", "application/json; charset=utf-8");
    request->setRawHeader("Connection", "keep-alive");
    request->setRawHeader("Host", "10.136.2.5");
    request->setRawHeader("Referer", "http://10.136.2.5/jnuweb/");
    request->setRawHeader("X-Requested-With", "XMLHttpRequest");
    request->setRawHeader("Content-Length", 0);
    request->setRawHeader("Token", cryptUtils::getbalanceToken(dateTime, this->userId));
    request->setRawHeader("DateTime", QDateTime::currentDateTime().
                          toString("yyyy-MM-dd hh:mm:ss").toUtf8());

    QByteArray* requestContent = new QByteArray("");

    QNetworkReply* reply = manager->post(*request, *requestContent);
    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if(statusCode.toInt() == 200)
        {
            QByteArray responseContent = reply->readAll();
            QJsonObject content = QJsonDocument::fromJson(responseContent).object();
            this->balanceInfo = &content;
            qDebug() << content;
            emit balanceUpdated();
        }
    });
}

void httpUtilsJNUElectric::GetCost()
{
    QNetworkRequest* request = new QNetworkRequest();
    QByteArray dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8();
    request->setUrl(Urls::costUrl);

    request->setRawHeader("Accept","*/*");
    request->setRawHeader("Accept-Encoding", "deflate");
    request->setRawHeader("Accept-Language", "zh-CN,zh;q=0.9,en;q=0.8");
    request->setRawHeader("Content-Type", "application/json; charset=utf-8");
    request->setRawHeader("Connection", "keep-alive");
    request->setRawHeader("Host", "10.136.2.5");
    request->setRawHeader("Referer", "http://10.136.2.5/jnuweb/");
    request->setRawHeader("X-Requested-With", "XMLHttpRequest");
    request->setRawHeader("Token", cryptUtils::getbalanceToken(dateTime, this->userId));
    request->setRawHeader("DateTime", QDateTime::currentDateTime().
                          toString("yyyy-MM-dd hh:mm:ss").toUtf8());

    QDateTime dateTimeQuery = QDateTime::currentDateTime();
    QString date = dateTimeQuery.toString("yyyy-MM-01");
    QString nextMonth = dateTimeQuery.addMonths(1).toString("yyyy-MM-dd");
    QJsonObject* requestContent = new QJsonObject();
    requestContent->insert("startDate", QJsonValue(date));
    requestContent->insert("endDate", QJsonValue(nextMonth));
    requestContent->insert("energyType", "0");

    QNetworkReply* reply = manager-> post(*request, QJsonDocument(*requestContent).toJson(QJsonDocument::Compact));

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if(statusCode.toInt() == 200)
        {
            QByteArray responseContent = reply->readAll();
            QJsonObject content = QJsonDocument::fromJson(responseContent).object();
            this->costInfo = &content;
            emit costUpdated();
        }
    });
}
