#ifndef BYFOLDERCALCSTRATEG_H
#define BYFOLDERCALCSTRATEG_H

#include "CalculationStrategy.h"
#include <QDir>
#include <QFileInfo>
int calculateFolderSize(const QString& folderPath); //объявление функции, которая принимает строку QString, представляющую путь к папке,
                                                   //и возвращает целое число, представляющее размер папки.
class ByFolderCalcStrateg : public CalculationStrategy
{
public:
    QMap<QString, double> calculateSize(const QString& directory) override; //Объявление метода calculateSize, который переопределяет
    //чисто виртуальный метод из базового класса CalculationStrategy. Этот метод принимает строку QString, представляющую путь к
    //директории, и возвращает карту (QMap), где ключами являются строки (имена файлов или папок), а значениями — размеры в виде чисел с плавающей точкой (double)
};

#endif // BYFOLDERCALCSTRATEG_H
