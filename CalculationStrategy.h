#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H

#include <QMap>
#include <QString>

class CalculationStrategy
{
public:
    virtual QMap<QString, double> calculateSize(const QString& directory) = 0;
};

#endif // CALCULATIONSTRATEGY_H
