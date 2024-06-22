#ifndef BYFOLDERCALCSTRATEG_H
#define BYFOLDERCALCSTRATEG_H

#include "CalculationStrategy.h"

#include "CalculationStrategy.h"

class ByFolderCalcStrateg : public CalculationStrategy
{
public:
    QMap<QString, double> calculateSize(const QString& directory) override;
    double calculateFolderSize(const QString& folderPath);
};

#endif // BYFOLDERCALCSTRATEG_H
