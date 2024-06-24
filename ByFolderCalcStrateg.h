#ifndef BYFOLDERCALCSTRATEG_H
#define BYFOLDERCALCSTRATEG_H

#include "CalculationStrategy.h"
#include <QDir>
#include <QFileInfo>
int calculateFolderSize(const QString& folderPath);
class ByFolderCalcStrateg : public CalculationStrategy
{
public:
    QMap<QString, double> calculateSize(const QString& directory) override;
};

#endif // BYFOLDERCALCSTRATEG_H
