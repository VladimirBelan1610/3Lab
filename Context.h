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
    Context(unique_ptr<CalculationStrategy> st) : calcstrategy(move(st)) {};
    void set(unique_ptr<CalculationStrategy> str)
    {
        this->calcstrategy = move(str);
    }
    QMap<QString, double> calculate(const QString& dir)
    {
        return calcstrategy->calculateSize(dir);
    }
private:
    unique_ptr<CalculationStrategy> calcstrategy;
};
#endif // CONTEXT_H
