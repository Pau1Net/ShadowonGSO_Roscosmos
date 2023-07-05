#ifndef ONEDAYCUSTOMORBIT_H
#define ONEDAYCUSTOMORBIT_H
#include <QDate>
#include <QTime>
#include <QPair>
#include <QVector>

static const QDate StartingDate = QDate(2023,3,21);
static const QTime StartingTime = QTime(9,4);

class OneDayCustomOrbit
{
public:
    OneDayCustomOrbit();
    double ReducePosSun(double,double,QDate);
    double CountShadowDuration();
    QVector<QPair<double, double>> CountShadowDurationM();
//    QVector<QPair<double, double> > CountShadowDurationM(QVector<double> rka_values);
    QVector<double> CalculateUS();
    QVector<double> CalculateTet(QVector<double> us_values, double om);
    QVector<double> CalculateRka(QVector<double> tet_values, double r_a, double r_p);
private:
    double exp;
    double u_s;
    int hours = StartingTime.hour();
    int minutes = StartingTime.minute();
};

#endif // ONEDAYCUSTOMORBIT_H
