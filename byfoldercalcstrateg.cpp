#include "ByFolderCalcStrateg.h"
#include <QDir>

QMap<QString, double> ByFolderCalcStrateg::calculateSize(const QString& directory)
{
    QDir dir(directory);
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    QMap<QString, double> folderSizes;

    for (const QFileInfo& fileInfo : list) {
        if (fileInfo.isDir()) {
            double folderSize = calculateFolderSize(fileInfo.absoluteFilePath()) / 1024.0; // Convert bytes to KB
            folderSizes.insert(fileInfo.fileName(), folderSize);
        } else {
            double fileSize = static_cast<double>(fileInfo.size()) / 1024.0; // Convert bytes to KB
            folderSizes.insert(fileInfo.fileName(), fileSize);
        }
    }

    return folderSizes;
}

double ByFolderCalcStrateg::calculateFolderSize(const QString& folderPath)
{
    QDir dir(folderPath);
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    qint64 totalSize = 0;

    for (const QFileInfo& fileInfo : list) {
        if (fileInfo.isDir()) {
            totalSize += calculateFolderSize(fileInfo.absoluteFilePath());
        } else {
            totalSize += fileInfo.size();
        }
    }

    return static_cast<double>(totalSize);
}
