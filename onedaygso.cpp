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

double OneDayGSO::CountShadowDurationByOrbitHeight(double apoapsis, double periapsis)
{
    // Расчет радиуса орбиты на основе высоты апоцентра и перицентра
    double radiusKA = (apoapsis + periapsis) / 2 + radiusEarth;

    // Расчет радиуса тени
    double radiusShadow = sqrt(pow(radiusKA,2)-pow(radiusEarth,2));

    // Расчет betaT
    double betaT = radiusShadow / radiusKA;

    // Расчет продолжительности тени
    double result;
    if (betaT/sunAngle > 1 || betaT/sunAngle < -1)
    {
        result = -1;
    }
    else
    {
        result = (86164.0/M_PI*acos(betaT/sunAngle));
    }

    // Создание и отображение метки с результатами
    QLabel *label = new QLabel;
    label->setText(QString("Shadow duration for orbit height %1: %2\n")
                   .arg((apoapsis + periapsis) / 2).arg(result));

    label->show();

    return result;
}

