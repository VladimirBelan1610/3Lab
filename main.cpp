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
    QTextStream stream(stdin); //Создаются потоки для ввода и вывода
    QTextStream out(stdout);
    cout << "Enter the directory path:"; //Программа запрашивает у пользователя путь к директории:
    QString directory = stream.readLine(); //stream — это объект класса QTextStream, который был создан и связан с стандартным вводом
    //Он используется для чтения текстовых данных.
    unique_ptr<Context> context; //это умный указатель из библиотеки <memory>. Он автоматически управляет временем жизни объекта,
    //на который указывает, и гарантирует, что объект будет удален, когда указатель выходит из области видимости.
    cout << "Chose strategy : " << "\n" //Программа запрашивает у пользователя выбор стратегии для вычисления размеров:
         << "1 - for File Type Strategy " <<"\n"
         << "2 - for Folder Strategy :  " << "\n";
    QString c = 0;
    stream >> c;
    if (c == "1") //В зависимости от выбора пользователя создается объект Context с соответствующей стратегией:
    {
        context = make_unique<Context>(make_unique<ByFolderCalcStrateg>()); //Если пользователь выбирает "1", используется стратегия
        //ByFolderCalcStrateg.
        //make_unique<ByFolderCalcStrateg>() создает объект типа
        //ByFolderCalcStrateg и возвращает умный указатель на него. make_unique<Context>(...) создает объект типа Context, передавая ему
        //умный указатель на объект типа ByFolderCalcStrateg.
    }
    else if (c == "2") //Если пользователь выбирает "2", используется стратегия ByTypeCalcStrateg.
    {
        context = make_unique<Context>(make_unique<ByTypeCalcStrateg>());
    }
    else
    {
        out << "ERROR" << "\n"; //Если введено что-то другое, выводится сообщение об ошибке и программа завершает работу.
        return -1;
    }
    QMap<QString, double> strat = context->calculate(directory); //После выбора стратегии вызывается метод calculate объекта context,
                                                                //который возвращает карту QMap с размерами файлов/папок:
    // Вывод результатов вычислений на экран

    //strat — это переменная типа QMap<QString, double>, которая будет хранить результат вызова метода calculate.
   // context — это указатель на объект класса Context. calculate — это метод класса Context, который принимает параметр directory.
   //directory — это аргумент, передаваемый методу calculate. Предполагается, что это переменная, представляющая директорию


    cout << "Size calculation :" << endl; //Результаты вычислений выводятся на экран:
    for (auto it = strat.begin(); it != strat.end(); ++it) {
        QString name = it.key(); //it.key() возвращает текущий ключ (имя файла или папки).
        double size = it.value(); // размер файла/папки. it.value() возвращает текущее значение (размер файла или папки).
        int totalSize = calculateFolderSize(directory); //функция calculateFolderSize принимает параметр directory и возвращает общий
        //размер всех файлов и папок в этой директории.
        QString percentage = percentageCalc(size, totalSize ); //функция percentageCalc принимает два параметра (size и totalSize) и
        //возвращает строку, представляющую процентное соотношение размера текущего файла/папки к общему размеру директории.
        double value = it.value()/1024 ; //Преобразование размера из байт в килобайты путем деления на 1024.
        cout << name.toStdString() << ": " << value << "KB " << percentage.toStdString() << "\n";
    }
    cout << "\n";
    return 0;
}
