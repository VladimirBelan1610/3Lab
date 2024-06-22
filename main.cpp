#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "ByFolderCalcStrateg.h"
#include "ByTypeCalcStrateg.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream stream(stdin);
    qDebug() << "Enter the directory path:";
    QString directory = stream.readLine();

    ByFolderCalcStrateg byFolderStrategy;
    ByTypeCalcStrateg byTypeStrategy;

    QMap<QString, double> sizeByFolder = byFolderStrategy.calculateSize(directory);
    QMap<QString, double> sizeByType = byTypeStrategy.calculateSize(directory);

    // Вывод результатов вычислений на экран
    qDebug() << "Size calculation by folder:";
    for (auto it = sizeByFolder.begin(); it != sizeByFolder.end(); ++it) {
        qDebug() << it.key() << ": " << it.value() << "KB";
    }

    qDebug() << "\nSize calculation by type:";
    for (auto it = sizeByType.begin(); it != sizeByType.end(); ++it) {
        qDebug() << it.key() << ": " << it.value() << "KB";
    }

    return a.exec();
}
