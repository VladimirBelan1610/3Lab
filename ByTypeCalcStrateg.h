#ifndef BYTYPECALCSTRATEG_H
#define BYTYPECALCSTRATEG_H


#include "CalculationStrategy.h"

class ByTypeCalcStrateg : public CalculationStrategy
{
public:
    QMap<QString, double> calculateSize(const QString& directory) override;
};

#endif // BYTYPECALCSTRATEG_H
