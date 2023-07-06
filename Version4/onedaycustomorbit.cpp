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
    double e = epsilon*radian;
    double radI = i*radian;
    double radO = o*radian;
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
        double result = (86164.0/3.14*acos(betaT/sunAngle));
        return result;
    }
}

//QVector<double> OneDayCustomOrbit::CalculateUS()
//{
//    QVector<double> us_values;
//    double radO ;
//    double u;
//    double eta;

//    for (int i = 0; i <= 360; i++)
//    {
//        radO = (360 - i) * radian;
//        u = StartingDate.daysTo(QDate::currentDate())*fi*radian;
//        eta = sqrt(1.0 - pow(exp,2.0));
//        if (eta == 0)
//        {
//            us_values.push_back(-1);
//        }
//        else
//        {
//            u_s = (cos(u) * cos(radO) + sin(u) * sin(radO) * epsilon) / eta;
//            us_values.push_back(u_s);
//        }
//        minutes -= 4;
//        if (minutes < 0){
//            minutes += 60;
//            hours--;
//        }
//    }
//    return us_values;

//}
////получение истинной аномалии
//QVector<double> OneDayCustomOrbit::CalculateTet(QVector<double> us_values, double om)
//{
//    QVector<double> tet_values;
//    double tet;
//    for (int i = 0; i < us_values.size(); i++)
//    {
//        tet = us_values[i] - om;
//        tet_values.push_back(tet);
//    }
//    return tet_values;
//}
////получение радиуса
//QVector<double> OneDayCustomOrbit::CalculateRka(QVector<double> tet_values, double r_a, double r_p)
//{
//    QVector<double> rka_values;
//    double r_ka, e, p, tet;
//    double a;
//    a = (r_a + r_p) / 2 ;
//    e = (r_a - r_p) / (r_a + r_p);
//    p = a * (1 - pow(e, 2));
//    for(int i = 0; i < tet_values.size(); i++)
//    {
//        tet = tet_values[i];
//        r_ka = p/ (1 + e*cos(tet));
//        rka_values.push_back(r_ka);
//    }
//    return rka_values;
//}

//QVector<QPair<double, double> > OneDayCustomOrbit::CountShadowDurationM(QVector<double> rka_values)
//{
//    QVector<QPair<double, double> > shadowBorders;//вектор для хранения границ тени
//    double sunAngle, betaT;
//    bool inShadow = false; //флаг
//    double shadowStart, shadowEnd;

//    for(int i = 0; i < rka_values.size(); i++)
//    {
//        double radiusShadow = sqrt(pow(rka_values[i], 2) - pow(radiusEarth,2));
//        betaT = radiusShadow/rka_values[i];

//        sunAngle = sqrt((1.0 - pow(exp,2.0)));

//        if (betaT/sunAngle > 1 || betaT/sunAngle < -1)
//        {
//            if (inShadow)
//            {
//                //Если были в тени и вышли из нее запоминаем конец тени
//                shadowEnd = i;
//                shadowBorders.append(qMakePair(shadowStart, shadowEnd));
//                inShadow = false;
//            }
//        }
//        else
//        {
//            if (!inShadow)
//            {
//                //Если только что вошли в тень запоминаем начало
//                shadowStart = i;
//                inShadow = true;
//            }
//        }
//    }

//    if (inShadow)
//    {
//        //Если в момент окончания расчета попали в тень
//        shadowEnd = rka_values.size()-1;
//        shadowBorders.append(qMakePair(shadowStart,shadowEnd));
//    }

//    return shadowBorders;
//}
//// объединение функций в одну.
////тестовый вариант(работает).

QVector<ShadowData> OneDayCustomOrbit::CountShadowDurationM()
{
   double om = 0;
   double r_a = 36000 + radiusEarth, r_p = 400 + radiusEarth, a;

   a = (r_a + r_p)/2;
   double e = (r_a - r_p) / (r_a + r_p);
   double p = a*(1 - pow(e,2));

   QVector<ShadowData> shadowBorders;
   double sunAngle, betaT;
   bool inShadow = false;
   ShadowData currentShadow;

   double radO, u, eta, u_s, tet, r_ka;
   for (int i = 0; i <= 360; i++)
   {
       radO = (360 - i) * radian;
       u = StartingDate.daysTo(QDate::currentDate())*fi*radian;
       eta = sqrt(1.0 - pow(exp,2.0));
       double denominator = eta;
       if (denominator != 0)
       {
           double cos_u_s = (cos(u) * cos(radO) + sin(u) * sin(radO) * epsilon*radian) / eta;
           u_s = acos(cos_u_s);
       }
       minutes -= 4;
       if (minutes < 0){
           minutes += 60;
           hours--;
       }
//это происходит из-за исправления более сложной функции на более легкую.Структруа(struct) отрабатывает неверно.
       tet = u_s - om;

       r_ka = p/(1+e * cos(tet));

       //функция, которая будет также рассматривать границы тени, но уже без QPair(тест)
       double radiusShadow = sqrt(pow(r_ka,2) - pow(radiusEarth,2));
       betaT = radiusShadow/r_ka;
       sunAngle = sqrt(1.0 - pow(exp,2.0));

       if (betaT/sunAngle > 1 || betaT/sunAngle < -1)
       {
           if (inShadow) //этот блок не работает. если убрать ничего не произойдет
           {
               currentShadow.end = i;
               shadowBorders.append(currentShadow);
               inShadow = false;
           }
       }
       else
       {
           if (!inShadow)
           {
               currentShadow.start = i;
               inShadow = true;
           }
       }

   }

   if (inShadow)
   {
       currentShadow.end = 360;
       shadowBorders.append(currentShadow);
   }

   return shadowBorders;
}






////Функция, принмающая в обработку массивы
//QVector<QPair<double, double> > OneDayCustomOrbit::CountShadowDurationM()
//{
//    //Расчет U
//    QVector<double> us_values;
//    double radO, u, eta;

//    for (int i = 0; i <= 360; i++) //    for (int i = 0; i <= 360; i++)
//        {
//            radO = (360 - i) * radian;
//            u = StartingDate.daysTo(QDate::currentDate())*fi*radian;
//            eta = sqrt(1.0 - pow(exp,2.0));
//            if (eta == 0)
//            {
//                us_values.push_back(-1);
//            }
//            else
//            {
//                u_s = (cos(u) * cos(radO) + sin(u) * sin(radO) * epsilon) / eta;
//                us_values.push_back(u_s);
//            }
//            minutes -= 4;
//            if (minutes < 0){
//                minutes += 60;
//                hours--;
//            }
//        }

//        //Расчет Tet
//        double om = 0;
//        QVector<double> tet_values;
//        double tet;

//        for (int i = 0; i < us_values.size(); i++)
//        {
//                tet = us_values[i] - om;
//                tet_values.push_back(tet);
//        }

//        //Расчет Rka
//        double r_a = 36000, r_p = 400, a;
//        QVector<double> rka_values;
//        double r_ka, e, p;
//        a = (r_a + r_p)/2;
//        e = (r_a - r_p) / (r_a + r_p);
//        p = a*(1 - pow(e,2));
//        for(int i = 0; i < tet_values.size(); i++)
//        {
//                tet = tet_values[i];
//                r_ka = p/ (1 + e*cos(tet));
//                rka_values.push_back(r_ka);
//        }

//        //Расчет продолжительности тени
//        QVector<QPair<double, double> > shadowBorders;
//        double sunAngle, betaT;
//        bool inShadow = false; //флаг
//        double shadowStart, shadowEnd;

//        for(int i = 0; i < rka_values.size(); i++)
//        {
//            double radiusShadow = sqrt(pow(rka_values[i], 2) - pow(radiusEarth,2));
//            betaT = radiusShadow/rka_values[i];

//            sunAngle = sqrt((1.0 - pow(exp,2.0)));

//            if (betaT/sunAngle > 1 || betaT/sunAngle < -1)
//            {
//                if (inShadow)
//                {
//                    //Если были в тени и вышли из нее запоминаем конец тени
//                    shadowEnd = i;
//                    shadowBorders.append(qMakePair(shadowStart, shadowEnd));
//                    inShadow = false;
//                }
//            }
//            else
//            {
//                if (!inShadow)
//                {
//                    //Если только что вошли в тень запоминаем начало
//                    shadowStart = i;
//                    inShadow = true;
//                }
//            }
//        }

//        if (inShadow)
//        {
//            //Если в момент окончания расчета попали в тень
//            shadowEnd = rka_values.size()-1;
//            shadowBorders.append(qMakePair(shadowStart,shadowEnd));
//        }

//        return shadowBorders;
//}

