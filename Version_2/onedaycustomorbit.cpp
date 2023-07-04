#include "onedaycustomorbit.h"
#include <QDate>
#include "onedaygso.h"
#include <QVector>
#include <QPair>

OneDayCustomOrbit::OneDayCustomOrbit()
{

}
//Главная формула расчета, с использованием наклонения и ДВУ. Все обозначения подробно описаны в onedaygso.h
double OneDayCustomOrbit::ReducePosSun(double i, double o, QDate date)
{
    double u = StartingDate.daysTo(date)*fi*radian;
    double e = epsilon*radian, radI = i*radian, radO = o*radian;
    exp = 0;
    exp = sin(radI)*sin(radO)*cos(u);
    double exp2 = 0, exp3 = 0, exp4 = 0;
    exp2 = cos(radI)*sin(e);
    exp3 = (sin(radI)*cos(radO)*cos(e));
    exp4 = sin(u)*(exp2-exp3);
    exp+=exp4;
    return exp;
}



double OneDayCustomOrbit::CountShadowDuration()
{
    double sunAngle = sqrt(1.0 - pow(exp,2.0));

    if (betaT/sunAngle > 1 || betaT/sunAngle < -1)
    {
        return -1;
    }
    else
    {
        double result = (86164.0/M_PI*acos(betaT/sunAngle));
        return result;
    }
}

QVector<QPair<double, double>> OneDayCustomOrbit::CountShadowDurationM()
{
    // Расчет U
    QVector<double> us_values;
    double radO, u, u_s, eta;
    for(int i = 0; i <= 360; i++)
    {
        radO = (360 - i) * radian;
        u = StartingDate.daysTo(QDate::currentDate())*2*M_PI;
        eta = sqrt(1.0 - pow(exp,2.0));
        double denominator = eta;
        if (denominator == 0)
        {
            us_values.push_back(-1);
        }
        else
        {
            u_s = (cos(u)*cos(radO) + sin(u)*sin(radO)*epsilon) / cos(eta);
            us_values.push_back(u_s);
        }
        minutes -= 4;
        if(minutes < 0) {
            minutes += 60;
            hours--;
        }
    }

    // Расчет Tet
    double om = 180; // Задайте значение om
    QVector<double> tet_values;
    double tet;
    for(int i = 0; i < us_values.size(); i++)
    {
        tet = us_values[i] - om;
        tet_values.push_back(tet);
    }

    // Расчет Rka
    double r_a = 36000, r_p = 400, a; // Задайте значения r_a, r_p, a
    QVector<double> rka_values;
    double r_ka, e, p;
    a = (r_a + r_p)/2 ;
    e = (r_a - r_p) / (r_a + r_p);
    p = a * (1 - pow(e, 2));
    for(int i = 0; i < tet_values.size(); i++)
    {
        tet = tet_values[i];
        r_ka = p / (1 + e * cos(tet));
        rka_values.push_back(r_ka);
    }

    // Подсчет продолжительности тени
    QVector<QPair<double, double> > shadowBorders;
    double sunAngle, betaT;
    bool inShadow = false;
    double shadowStart, shadowEnd;

    for(int i = 0; i < rka_values.size(); i++)
    {
        double radiusShadow = sqrt(pow(rka_values[i],2) - pow(radiusEarth,2));
        betaT = radiusShadow/rka_values[i];

        sunAngle = sqrt(1.0 - pow(exp,2.0));

        if (betaT/sunAngle > 1 || betaT/sunAngle < -1)
        {
            if (inShadow)
            {
                shadowEnd = i;
                shadowBorders.append(qMakePair(shadowStart, shadowEnd));
                inShadow = false;
            }
        }
        else
        {
            if (!inShadow)
            {
                shadowStart = i;
                inShadow = true;
            }
        }
    }

    if (inShadow)
    {
        shadowEnd = rka_values.size()-1;
        shadowBorders.append(qMakePair(shadowStart, shadowEnd));
    }

    return shadowBorders;
}

