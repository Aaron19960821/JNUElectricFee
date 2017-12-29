
#include "cryptutils.h"
#include "crypt/qaesencryption.h"
#include "urls.h"
#include <QString>
#include <QByteArray>
#include <QString>
#include <QDateTime>
#include <QDebug>

cryptUtils::cryptUtils()
{
}

QByteArray cryptUtils::getIdToken()
{
    QByteArray dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8();
    QByteArray* plainString = new QByteArray("{\"userID\":0,\"tokenTime\":\"");
    plainString->append(dateTime);
    plainString->append("\"}");
    plainString = cryptUtils::pkcs7Padding(plainString, 16);

    QAESEncryption* encryptor = new QAESEncryption(QAESEncryption::AES_128, QAESEncryption::CBC);
    QByteArray res = encryptor->encode(*plainString, QByteArray::fromHex(Urls::key), QByteArray::fromHex(Urls::value));
    return res.toBase64().append(QString("%0A"));
}

QByteArray cryptUtils::getbalanceToken(QByteArray dateTime, QString userId)
{
    QByteArray* plainString = new QByteArray("{\"userID\":");
    plainString->append(userId);
    plainString->append(",\"tokenTime\":\"");
    plainString->append(dateTime);
    plainString->append("\"}");
    plainString = cryptUtils::pkcs7Padding(plainString, 16);

    QAESEncryption* encryptor = new QAESEncryption(QAESEncryption::AES_128, QAESEncryption::CBC);
    QByteArray res = encryptor->encode(*plainString, QByteArray::fromHex(Urls::key), QByteArray::fromHex(Urls::value));
    return res.QByteArray::toBase64().append(QString("%0A"));
}

QByteArray* cryptUtils::pkcs7Padding(QByteArray *origincode, int blockSize)
{
    int len = origincode->length();
    int offset = len%blockSize;
    int needPadding = 0;
    needPadding = blockSize - offset;
    for(int i = 0; i < needPadding; i++)
    {
        origincode->append(QChar(needPadding));
    }
    return origincode;
}
