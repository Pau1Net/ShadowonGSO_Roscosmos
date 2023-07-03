#include "heichttest.h"
#include "ui_heichttest.h"
#include "onedaygso.h"
#include "customshadowdurationoneday.h"
#include "customshadowdurationoneday.cpp"
#include "onedaycustomorbit.h"
#include <QLabel>
#include <cmath>

heichttest::heichttest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::heichttest)
{
    ui->setupUi(this);
}

heichttest::~heichttest()
{
    delete ui;
}

//double calculateShadowDuration(double orbitHeight, double numDays)
//{
//    OneDayGSO oneDay;
//    double sunAngle = numDays*fi*radian;
//    sunAngle = epsilon * radian * sin(sunAngle);
//    sunAngle = cos(sunAngle);

//    double shadowDuration = oneDay.CountShadowDuration(sunAngle, orbitHeight);
//    return shadowDuration;
//}

//double orbitHeight1 = 400;
//double orbitHeight2 = 36000;
//double numDays = 81;

//void calculateShadowDurationDifference(double orbitHeight1, orbitHeight2, numDays)
//{
//    double shadowDuration1 = calculateShadowDuration(orbitHeight1, numDays);
//    double shadowDuration2 = calculateShadowDuration(orbitHeight2, numDays);

//    double difference = abs(shadowDuration1 - shadowDuration2) / ((shadowDuration1 + shadowDuration2) / 2) * 100;

//    QLabel *label = new QLabel;
//    label->setText(QString("Shadow duration for orbit height %1: %2\n"
//                           "Shadow duration for orbit height %3: %4\n"
//                           "Difference in shadow duration: %5\n")
//                   .arg(orbitHeight1).arg(shadowDuration1)
//                   .arg(orbitHeight2).arg(shadowDuration2)
//                   .arg(difference));
//    if (difference < 2)
//    {
//        label->setText(label->text() + "The difference in shadow duration is less than 2%");
//    }
//    else
//    {
//        label->setText(label->text() + "The difference in shadow duration is greater than 2%");
//    }

//    label->show();
//}

//calculateShadowDurationDifference(orbitHeight1, orbitHeight2, numDays);
void calculateShadowDurationDifference(){
    OneDayGSO oneDay;
    oneDay.setSunAngle(1.0);
    double shadowDuration = oneDay.CountShadowDurationByOrbitHeight(400, 36000);
}
