//расчет солнечного угла
#include "onedaygso.h"
#include "onedaycustomorbit.h"
#include <math.h>
#include <QLabel>
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
    if (sunAngle > 0) {
        //Солнце в северной части(+)
    }
    else{
        //Солнце в южной части
    }

    if (betaT/sunAngle > 1 || betaT/sunAngle < -1)
    {
        return -1;
    }
    else
    {
    double result = (86164.0/3.14*acos(betaT/sunAngle));
        return result;
    }
}

//функция работает неправильно. Не использовать.
double OneDayGSO::CountShadowDurationByOrbitHeight(double apoapsis, double periapsis)
{
    double radiusKA = (apoapsis + periapsis) / 2 + radiusEarth;

    double radiusShadow = sqrt(pow(radiusKA, 2)-pow(radiusEarth, 2));

    double betaT = radiusShadow/radiusKA;

    double result;

    if (betaT/sunAngle > 1 || betaT/sunAngle < -1)
    {
        result = -1;
    }
    else
    {
        result = (86164.0/3.14*acos(betaT/sunAngle));
    }

    QLabel *label = new QLabel;
    label->setText(QString("Shadow duration for orbit height %1: %2\n")
                   .arg((apoapsis + periapsis) / 2).arg(result));
    label->show();

    return result;
}
