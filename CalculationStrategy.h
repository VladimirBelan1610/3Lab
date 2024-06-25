#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H

#include <QMap>
#include <QString>

class CalculationStrategy //объявление класса CalculationStrategy, который является абстрактным классом
{
public:
    virtual QMap<QString, double> calculateSize(const QString& directory) = 0; //константная ссылка на объект типа QString,
                                                                            //представляющая путь к директории, размер которой нужно вычислить.
}; //В данном случае это карта (QMap), где ключами являются строки (QString), а значениями — числа с плавающей точкой (double).
  //Этот контейнер используется для хранения пар "имя файла/папки - размер".

#endif // CALCULATIONSTRATEGY_H
