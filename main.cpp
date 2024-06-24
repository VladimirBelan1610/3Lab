#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include "ByFolderCalcStrateg.h"
#include "ByTypeCalcStrateg.h"
#include <Context.h>
#include <iostream>
#include <memory>
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
    cout << "Enter the directory path:";
    QString directory = stream.readLine();
    unique_ptr<Context> context;
    cout << "Chose strategy : " << "\n"
         << "1 - for File Type Strategy " <<"\n"
         << "2 - for Folder Strategy :  " << "\n";
    QString c = 0;
    stream >> c;
    if (c == "1")
    {
        context = make_unique<Context>(make_unique<ByFolderCalcStrateg>());
    }
    else if (c == "2")
    {
        context = make_unique<Context>(make_unique<ByTypeCalcStrateg>());
    }
    else
    {
        out << "ERROR" << "\n";
        return -1;
    }
    QMap<QString, double> strat = context->calculate(directory);
    // Вывод результатов вычислений на экран
    cout << "Size calculation :" << endl;
    for (auto it = strat.begin(); it != strat.end(); ++it) {
        QString name = it.key();
        double size = it.value(); // размер файла/папки
        int totalSize = calculateFolderSize(directory);
        QString percentage = percentageCalc(size, totalSize );
        double value = it.value()/1024 ;
        cout << name.toStdString() << ": " << value << "KB " << percentage.toStdString() << "\n";
    }
    cout << "\n";
    return 0;
}
