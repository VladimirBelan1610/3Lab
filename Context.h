#ifndef CONTEXT_H
#define CONTEXT_H
#include "CalculationStrategy.h"
#include <QString>
#include <iostream>
using namespace std;
class Context
{
public:
    Context(CalculationStrategy* cont): p(cont) {};
    ~Context() { delete p; }
    QMap<QString, double> calculateSize( const QString & directory )
    {
        return p->calculateSize(directory);
    }
private:
    CalculationStrategy* p;
};

#endif // CONTEXT_H
