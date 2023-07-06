#include "graphicyearcustomorbit.h"
#include "ui_graphicyearcustomorbit.h"
#include "onedaycustomorbit.h"
#include <QVector>
#include <QPair>

graphicyearcustomorbit::graphicyearcustomorbit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphicyearcustomorbit)
{
    ui->setupUi(this);
}

graphicyearcustomorbit::~graphicyearcustomorbit()
{
    delete ui;
}

//QVector<QVector<QPair<double, double> > >* CalcSahdow(double i, double o)
//{
//    OneDayCustomOrbit CountDuration = OneDayCustomOrbit();
//    int days = StartingDate.daysInYear();
//    QDate date = QDate(23, 03, 21);
//    QVector<QVector<QPair<double, double> > >* result = new QVector<QVector<QPair<double, double>>>[days];
//    for (int j = 0; j < days; j++)
//    {
//        QDate curDate = date.addDays(j);
//        CountDuration.ReducePosSun(i,o,curDate);
//        QVector<double> us_values = CalculateUS();
//        QVector<double> tet_values = CalculateTet(us_values, om);


//    }
//}
