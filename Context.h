#ifndef CONTEXT_H
#define CONTEXT_H
#include <QString>
#include <QMap>
#include "CalculationStrategy.h"
#include <memory>
using namespace std;
class Context
{
public:
    Context(unique_ptr<CalculationStrategy> st) : calcstrategy(move(st)) {}; //Это конструктор класса Context, который принимает
    //уникальный указатель на объект типа CalculationStrategy. calcstrategy(move(st)): Это список инициализации конструктора,
    //который инициализирует член данных calcstrategy, перемещая (move) переданный уникальный указатель st.

    //Использование unique_ptr (умного указателя) гарантирует, что объект стратегии будет автоматически уничтожен, когда он выйдет из
    //области видимости, и предотвращает утечки памяти.

    void set(unique_ptr<CalculationStrategy> str) // Это метод, который позволяет установить новую стратегию вычисления размеров.
    {
        this->calcstrategy = move(str); //Этот код перемещает (move) переданный уникальный указатель str в член данных calcstrategy.
        //Перемещение уникального указателя передает владение объектом от одного указателя к другому, обеспечивая безопасность памяти.
    }
    QMap<QString, double> calculate(const QString& dir) //Это метод, который использует текущую стратегию для вычисления размеров файлов
                                                       //и папок в указанной директории.
    {
        return calcstrategy->calculateSize(dir); //Этот код вызывает метод calculateSize текущей стратегии, передавая ей путь к
                                                 //директории и возвращая результат.
    }
private:
    unique_ptr<CalculationStrategy> calcstrategy; //Это член данных класса Context, который хранит уникальный указатель на объект типа
    //CalculationStrategy. Использование unique_ptr обеспечивает автоматическое управление временем жизни объекта стратегии.
};
#endif // CONTEXT_H
