#ifndef SETTING_H
#define SETTING_H

#include <QString>

class setting
{
public:
    setting();
    setting(int seconds, int bound);
    int getFlushSeconds();
    int getAlertBound();
    QString getDormitoryNumber();
    void setDormitoryNumber(QString dormitoryNumber);
    void setFlushSeconds(int seconds);
    void setAlertBound(int bound);

private:
    int flushSeconds;
    int alertBound;
    QString dormotoryNumber;
};

#endif // SETTING_H
