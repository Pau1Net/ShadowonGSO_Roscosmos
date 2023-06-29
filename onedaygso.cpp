//расчет солнечного угла
#include "onedaygso.h"
#include <math.h>
#define _USE_MATH_DEFINES

OneDayGSO::OneDayGSO()
{

}

double OneDayGSO::CountShadowDuration(QDate date)
{
    int numDays = StartingDate.daysTo(date);
    double sunAngle = numDays*fi*radian;
    sunAngle = epsilon * radian * sin(sunAngle);
    sunAngle = cos(sunAngle);

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
