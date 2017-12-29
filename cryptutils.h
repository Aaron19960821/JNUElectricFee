#ifndef CRYPTUTILS_H
#define CRYPTUTILS_H

#include"crypt/qaesencryption.h"
#include<QByteArray>
#include<QString>

class cryptUtils
{
public:
    cryptUtils();
    static QByteArray getIdToken();
    static QByteArray getbalanceToken(QByteArray dateTime, QString userId);
    static QByteArray* pkcs7Padding(QByteArray* origincode, int blockSize);

private:

};

#endif // CRYPTUTILS_H
