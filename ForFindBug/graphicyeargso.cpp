#include "graphicyeargso.h"
#include "ui_graphicyeargso.h"
#include "onedaycustomorbit.h"
#include <QVector>
#include <QPair>

GraphicYearGSO::GraphicYearGSO(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicYearGSO)
{
    ui->setupUi(this);
}

GraphicYearGSO::~GraphicYearGSO()
{
    delete ui;
}

//Функция расчета тени с использованием наклонения.
QVector<QPair<double, double>> CalcShadowDurationM(double i, double o)
{
    OneDayCustomOrbit CountDuration = OneDayCustomOrbit();
    int days = StartingDate.daysInYear();
    QDate date = QDate(2023,01,01);
    QVector<QPair<double, double>> result;
    for(int j = 0; j < days; j++)
    {
        QDate curDate = date.addDays(j);
        CountDuration.ReducePosSun(i, o, curDate);
        QVector<QPair<double, double>> dayResult = CountDuration.CountShadowDurationM();
        result.append(dayResult);
    }
    return result;
}

//Строим графики с использованием наклонения и ДВУ
void GraphicYearGSO::DrawGraphic(int degrees, double i, double o)
{
    QDateTime xnum;
    QDate datebegin = QDate(2023,1,1);
    QDate dateend = QDate(2023,12,31);

    xnum = QDateTime(datebegin);
    double xbegin = xnum.toTime_t();

    xnum = QDateTime(dateend);
    double xend = xnum.toTime_t();

    QSharedPointer <QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd.MM");
    dateTicker->setTickCount(12);
    ui->widget->xAxis->setTicker(dateTicker);
    ui->widget->xAxis->setRange(xbegin,xend);

    QDateTime ynum;
    QTime timebegin = QTime(0,0,0);

    ynum.setTime(timebegin);
    double ybegin = ynum.toTime_t() - 14*3600; //14 для начала от 00:00

    double yend = ybegin+86400;

    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
    timeTicker->setDateTimeFormat("hh:mm");
    timeTicker->setTickCount(24);
    ui->widget->yAxis->setTicker(timeTicker);
    ui->widget->yAxis->setRange(ybegin,yend);

    QVector<QPair<double, double>> result = CalcShadowDurationM(i, o);
    int daysInYear = StartingDate.daysInYear();

    QCPRange xRange = ui->widget->xAxis->range();
    QCPRange yRange = ui->widget->yAxis->range();

    const int maxGraphs = 100; // Лимит на количество графиков
    int graphCount = 0;

    for(int day = 0; day < daysInYear && graphCount < maxGraphs; day++)
    {
        ui->widget->addGraph();
        double x = xRange.lower + day * (xRange.upper - xRange.lower) / daysInYear;
        for(int resIdx = 0; resIdx < result.size(); resIdx++)
        {
            double yBegin = yRange.lower + result[resIdx].first * (yRange.upper - yRange.lower);
            double yEnd = yRange.lower + result[resIdx].second * (yRange.upper - yRange.lower);
            ui->widget->graph(graphCount)->addData(x, yBegin);
            ui->widget->graph(graphCount)->addData(x, yEnd);
        }
        graphCount++;
    }
}
