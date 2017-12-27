#ifndef UTILS_H
#define UTILS_H

#include<QMainWindow>


class utils
{
public:
    utils();
    static QString GetDormitoryNumber(QString originNumber);
    static void UpdateElectronicInfo(QString DormotroyNumber);
};

#endif // UTILS_H
