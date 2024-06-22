#include "ByTypeCalcStrateg.h"
#include <QDir>
#include <QMap>
#include <QStringList>

QMap<QString, double> ByTypeCalcStrateg::calculateSize(const QString& directory)
{
    QMap<QString, double> result;

    QDir dir(directory);
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    QMap<QString, qint64> typeSizes;

    for (const QFileInfo& fileInfo : list) {
        if (fileInfo.isFile()) {
            QString fileType = fileInfo.suffix().toLower();
            typeSizes[fileType] += fileInfo.size();
        }
    }

    for (auto it = typeSizes.begin(); it != typeSizes.end(); ++it) {
        result[it.key()] = it.value() / 1024.0; // Convert bytes to KB
    }

    return result;
}
