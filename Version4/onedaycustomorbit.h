#ifndef ONEDAYCUSTOMORBIT_H
#define ONEDAYCUSTOMORBIT_H
#include <QDate>
#include <QTime>
#include <QVector>


static const QDate StartingDate = QDate(2023,3,21); //убрано из onedaygso, из-за совместно зависемых функций.
static const QTime StartingTime = QTime(9,4);

struct ShadowData {
    double start;
    double end;
};

class OneDayCustomOrbit
{
public:
    OneDayCustomOrbit();
    double ReducePosSun(double,double,QDate);
    double CountShadowDuration();
    QVector<ShadowData> CountShadowDurationM();
//    QVector<double> CalculateUS();
//    QVector<double> CalculateTet(QVector<double> us_values, double om);//om - омега малая(аргумент)
//    QVector<double> CalculateRka(QVector<double> tet_values, double r_a, double r_p);
private:
    double exp;
    int hours = StartingTime.hour();
    int minutes = StartingTime.minute();

};

#endif // ONEDAYCUSTOMORBIT_H
