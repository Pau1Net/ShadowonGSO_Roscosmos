#include "onedaycustomorbit.h"
#include <QDate>
#include "onedaygso.h"

OneDayCustomOrbit::OneDayCustomOrbit()
{

}

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
