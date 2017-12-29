#ifndef URLS_H
#define URLS_H

#include<QApplication>

namespace Urls
{
    const QString loginUrl = QString("http://10.136.2.5/jnuweb/WebService/JNUService.asmx/Login");
    const QString balanceUrl = QString("http://10.136.2.5/jnuweb/WebService/JNUService.asmx/GetUserInfo");
    const QString costUrl = QString("http://10.136.2.5/jnuweb/WebService/JNUService.asmx/GetBillCost");
    const QString initPassword = QString("2ay/7lGoIrXLc9KeacM7sg==");
    const QByteArray key = QByteArray("436574536f667445454d537973576562");
    const QByteArray value = QByteArray("1934577290ABCDEF1264147890ACAE45");
}

#endif // URLS_H
