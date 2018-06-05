#include "setting.h"
#include <QString>

setting::setting()
{
    this->setAlertBound(20);
    this->setFlushSeconds(20000);
}

setting::setting(int seconds, int bound)
{
    this->setAlertBound(bound);
    this->setFlushSeconds(seconds);
}

QString setting::getDormitoryNumber()
{
    return this->dormotoryNumber;
}

int setting::getAlertBound()
{
    return this->alertBound;
}

int setting::getFlushSeconds()
{
    return this->flushSeconds;
}

void setting::setDormitoryNumber(QString dormitoryNumber)
{
    this->dormotoryNumber = dormitoryNumber;
}

void setting::setAlertBound(int bound)
{
    this->alertBound = bound;
}

void setting::setFlushSeconds(int seconds)
{
    this->flushSeconds = seconds;
}
