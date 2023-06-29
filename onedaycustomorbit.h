#ifndef ONEDAYCUSTOMORBIT_H
#define ONEDAYCUSTOMORBIT_H
#include <QDate>


class OneDayCustomOrbit
{
public:
    OneDayCustomOrbit();
    double ReducePosSun(double,double,QDate);
    double CountShadowDuration();
private:
    double exp;
};

#endif // ONEDAYCUSTOMORBIT_H
