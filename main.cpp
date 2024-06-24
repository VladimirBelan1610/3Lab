#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "ByFolderCalcStrateg.h"
#include "ByTypeCalcStrateg.h"
#include <Context.h>

using namespace std;
QString percentageCalc(double size, double total_size) { //Функция для вычисления процентного соотношения размера текущего файла/папки size от
    // общего размера директории total_size
    if (total_size != 0 && size != 0) { //Если общий размер директории и размер текущей папки/файла не равны 0, то
        double percent = (size/total_size) * 100.0;
        if (percent < 0.01) return "< 0.01 %"; //для обработки очень маленьких файлов
        else return QString::number(percent, 'f', 2) + " %"; //возвращаем процент в фиксированном формате(f) с 2 знаками после запятой в виде строки
    }
    else { return "0.00 %"; }
}

int main()
{

    QTextStream stream(stdin);
    QTextStream out(stdout);
    qDebug() << "Enter the directory path:";
    QString directory = stream.readLine();
    ByFolderCalcStrateg* byFolderStrategy = new ByFolderCalcStrateg();
    ByTypeCalcStrateg* byTypeStrategy = new ByTypeCalcStrateg();
    Context* contextByFolder = new Context(new ByFolderCalcStrateg());
    Context* contextByType = new Context(new ByTypeCalcStrateg());
    QMap<QString, double> sizeByFolder = contextByFolder->calculateSize(directory);
    QMap<QString, double> sizeByType = contextByType->calculateSize(directory);
    // Вывод результатов вычислений на экран
    cout << "Size calculation by folder:";
    for (auto it = sizeByFolder.begin(); it != sizeByFolder.end(); ++it) {
        QString name = it.key();
        double size = it.value(); // размер файла/папки
        double totalSize = byFolderStrategy->calculateFolderSize(directory);
        QString percentage = percentageCalc(size, totalSize );
        cout << name.toStdString() << ": " << it.value() << "KB " << percentage.toStdString() << "\n";
    }
    qDebug() << "\nSize calculation by type:";
    for (auto it = sizeByType.begin(); it != sizeByType.end(); ++it) {
        QString name = it.key();
        double size = it.value(); // размер файла/папки
        double totalSize = byFolderStrategy->calculateFolderSize(directory);
        QString percentage = percentageCalc(size, totalSize );
        cout << name.toStdString() << ": " << it.value() << "KB " << percentage.toStdString() << "\n";
    }
    // Освобождение ресурсов
    delete contextByFolder;
    delete contextByType;
    // Не забываем освободить также объекты стратегий
    delete byFolderStrategy;
    delete byTypeStrategy;
    return 0;
}
