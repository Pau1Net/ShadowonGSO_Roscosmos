#ifndef ONEDAYCUSTOMORBIT_H
#define ONEDAYCUSTOMORBIT_H
#include <QDate>

static const QDate StartingDate = QDate(2023,3,21);

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
