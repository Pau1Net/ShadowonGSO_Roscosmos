#include "onedaycustomorbit.h"
#include <QDate>
#include "onedaygso.h"
#include <QVector>
#include <QPair>
#include <QDebug>

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
    // Исходные значения
    double r_a_original = 36000.0;
    double r_p_original = 400.0;
    double r_a = r_a_original + radiusEarth;
    double r_p = r_p_original + radiusEarth;
    double a = (r_a + r_p)/2;
    double e = (r_a - r_p) / (r_a + r_p);
    double p = a * (1 - pow(e, 2));
    double om = 180;

    QVector<QPair<double, double>> shadowBorders;
    bool inShadow = false;
    double shadowStart, shadowEnd;

    double radO, u, eta, u_s, tet, r_ka;
    for (int i = 0; i <= 360; i++)
    {
        radO = (360 - i) * radian;
        u = StartingDate.daysTo(QDate::currentDate())*2*M_PI;
        eta = sqrt(1.0 - pow(exp,2.0));

        if (eta == 0)
            continue;

        u_s = (cos(u)*cos(radO) + sin(u)*sin(radO)*epsilon) / cos(eta);
        tet = u_s - om;
        r_ka = p / (1 + e * cos(tet));

        if (std::abs(r_ka) < 1e-9 || radiusEarth > r_ka)
            continue;

        double radiusShadow = sqrt(pow(r_ka,2) - pow(radiusEarth,2));
        double betaT = radiusShadow / r_ka;
        double sunAngle = sqrt(1.0 - pow(exp,2.0));
        double shadowCondition = betaT / sunAngle;

        if (shadowCondition > 1 || shadowCondition < -1)
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

        minutes -= 4;
        if (minutes < 0)
        {
            minutes += 60;
            hours--;
        }
    }

    if (inShadow)
    {
        shadowEnd = 360;
        shadowBorders.append(qMakePair(shadowStart, shadowEnd));
    }

    return shadowBorders;
}
