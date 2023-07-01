//НУ и Константы
#ifndef ONEDAYGSO_H
#define ONEDAYGSO_H
#include <QDate>
#include <math.h>
#define _USE_MATH_DEFINES

static  const  double fi = 360.0/365.0;
static  const  double toRadian = 3.14/180.0;
static const double radiusKA = 42164.0;
static const double radiusEarth = 6371.0;
static const double radiusShadow = sqrt(pow(radiusKA,2)-pow(radiusEarth,2));//=41680
static const QDate StartingDate = QDate(2023,3,21);
static const double radian = M_PI/180.0;
static const double epsilon = 23.45;
static const double betaT = radiusShadow/radiusKA;

class OneDayGSO
{
public:
    OneDayGSO();
    double CountShadowDuration(QDate);
    double CountShadowDurationByOrbitHeight(double apoapsis, double periapsis);
    void setSunAngle(double angle) { sunAngle = angle; }

private:
    double sunAngle;
};

#endif // ONEDAYGSO_H
