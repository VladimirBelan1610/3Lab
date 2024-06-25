#ifndef BYTYPECALCSTRATEG_H
#define BYTYPECALCSTRATEG_H


#include "CalculationStrategy.h"

class ByTypeCalcStrateg : public CalculationStrategy
{
public:
    QMap<QString, double> calculateSize(const QString& directory) override; //Объявление метода calculateSize, который переопределяет
    //чисто виртуальный метод из базового класса CalculationStrategy. Этот метод принимает строку QString, представляющую путь к
    //директории, и возвращает карту (QMap), где ключами являются строки (имена файлов или папок), а значениями — размеры в виде чисел с плавающей точкой (double)
};

#endif // BYTYPECALCSTRATEG_H
