//НУ и Константы
#ifndef ONEDAYGSO_H
#define ONEDAYGSO_H
#include <QDate>
#include <math.h>
#define _USE_MATH_DEFINES

static  const  double fi = 360.0/365.0; //среднее изменение положения Солнца за день
static  const  double toRadian = 3.14/180.0; //градусы в радианы
static const double radiusKA = 42164.0; //радиус ГСО
static const double radiusEarth = 6371.0;//радиус Земли
static const double radiusShadow = sqrt(pow(radiusKA,2)-pow(radiusEarth,2));//=41680. радиус тени Земли на ГСО
//static const QDate StartingDate = QDate(2023,3,21);//Начальный день расчета
static const double radian = 3.14/180.0; //Тоже градусы в радианы(зачем?)
static const double epsilon = 23.45;//Наклонение Солнца
static const double betaT = radiusShadow/radiusKA; //55стр

class OneDayGSO
{
public:
    OneDayGSO();
    double CountShadowDuration(QDate);
    double CountShadowDurationByOrbitHeight(double apoapsis, double periapsis);
    void setSunAngle(double angle) {sunAngle = angle; }
private:
    double sunAngle;
};

#endif // ONEDAYGSO_H
