#include "utils.h"

utils::utils()
{
}

//get the standard dormitory number from the input
QString utils::GetDormitoryNumber(QString originNumber)
{
    int buildingIndexStart = originNumber.lastIndexOf(QChar('T'));
    int roomIndexStart = originNumber.lastIndexOf(QChar('-'));
    int buildingIndex = originNumber.mid(buildingIndexStart+1, roomIndexStart - buildingIndexStart - 1).toInt();
    int roomIndex = originNumber.mid(roomIndexStart+1, originNumber.length()-roomIndexStart-1).toInt();
    return QString('T').append(QString::number(buildingIndex)).append(QString::number(roomIndex));
}
