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

    for(int i = 0; i < daysInYear; i++)
    {
        for(int i = 0; i < result.size(); i++)
        {
            double x = xRange.lower + i * (xRange.upper - xRange.lower) / result.size();
            double yBegin = yRange.lower + result[i].first * (yRange.upper - yRange.lower);
            double yEnd = yRange.lower + result[i].second * (yRange.upper - yRange.lower);
            ui->widget->addGraph();
            ui->widget->graph(i)->addData(x, yBegin);
            ui->widget->graph(i)->addData(x, yEnd);
        }
    }
}





//#include "graphicyeargso.h"
//#include "ui_graphicyeargso.h"
////#include "onedaygso.h"
//#include "onedaycustomorbit.h"

//GraphicYearGSO::GraphicYearGSO(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::GraphicYearGSO)
//{
//    ui->setupUi(this);
//}

//GraphicYearGSO::~GraphicYearGSO()
//{
//    delete ui;
//}

////Функция расчета тени с использованием наклонения.
//double* CalcShadowDuration(double i, double o)
//{
//    OneDayCustomOrbit CountDuration = OneDayCustomOrbit();
//    int days = StartingDate.daysInYear();
//    QDate date = QDate(2023,01,01);
//    double* result = new double[days];
//    for(int j = 0; j < days; j++)
//    {
//        QDate curDate = date.addDays(j);
//        CountDuration.ReducePosSun(i, o, curDate);
//        result[j] = CountDuration.CountShadowDuration();
//    }
//    return result;
//}
////Строим графики с использованием наклонения и ДВУ
//void GraphicYearGSO::DrawGraphic(int degrees, double i, double o)
//{
//    QDateTime xnum;
//    QDate datebegin = QDate(2023,1,1);
//    QDate dateend = QDate(2023,12,31);

//    xnum = QDateTime(datebegin);
//    double xbegin = xnum.toTime_t();

//    xnum = QDateTime(dateend);
//    double xend = xnum.toTime_t();

//    QSharedPointer <QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
//    dateTicker->setDateTimeFormat("dd.MM");
//    dateTicker->setTickCount(12);
//    ui->widget->xAxis->setTicker(dateTicker);
//    ui->widget->xAxis->setRange(xbegin,xend);

//    QDateTime ynum;
//    QTime timebegin = QTime(0,0,0);

//    ynum.setTime(timebegin);
//    double ybegin = ynum.toTime_t() - 14*3600; //14 для начала от 00:00

//    double yend = ybegin+86400;

//    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
//    timeTicker->setDateTimeFormat("hh:mm");
//    timeTicker->setTickCount(24);
//    ui->widget->yAxis->setTicker(timeTicker);
//    ui->widget->yAxis->setRange(ybegin,yend);

//    double* result = CalcShadowDuration(i, o);
//    int daysInYear = StartingDate.daysInYear();

//    QVector<QCPGraphData> ShadowGrowSpring(daysInYear), ShadowWeakSpring(daysInYear);
//    QVector<QCPGraphData> ShadowGrowAutumn(daysInYear), ShadowWeakAutumn(daysInYear);

//    int curtime = (degrees-45)/15; //московское время
//    double time = 3600*curtime;

//    for (int i=0; i < daysInYear/2 ;i++)
//    {
//        ShadowGrowSpring[i].key = xbegin + 86400*i;
//        ShadowWeakSpring[i].key = xbegin + 86400*i;

//        if (result[i] != -1)
//        {
//            double znachkey;
//            znachkey = ybegin + time + result[i]/2;
//            if (znachkey < ybegin)
//            {
//                ShadowGrowSpring[i].value = yend + time + result[i]/2;
//            }
//            else ShadowGrowSpring[i].value = ybegin + time + result[i]/2;

//            znachkey = ybegin + time - result[i]/2;
//            if (znachkey < ybegin)
//            {
//                ShadowWeakSpring[i].value = yend + time - result[i]/2;
//            }
//            else ShadowWeakSpring[i].value = ybegin + time - result[i]/2;
//        }
//        else
//        {
//            ShadowGrowSpring[i].value = qQNaN();
//            ShadowWeakSpring[i].value = qQNaN();
//        }
//    }

//    for (int i=daysInYear/2; i < daysInYear;i++)
//    {
//        ShadowGrowAutumn[i].key = xbegin + 86400*i;
//        ShadowWeakAutumn[i].key = xbegin + 86400*i;

//        if (result[i] != -1)
//        {
//            double znachkey;
//            znachkey = ybegin + time + result[i]/2;
//            if (znachkey < ybegin)
//            {
//                ShadowGrowAutumn[i].value = yend + time + result[i]/2;
//            }
//            else ShadowGrowAutumn[i].value = ybegin + time + result[i]/2;

//            znachkey = ybegin + time - result[i]/2;
//            if (znachkey < ybegin)
//            {
//                ShadowWeakAutumn[i].value = yend + time - result[i]/2;
//            }
//            else ShadowWeakAutumn[i].value = ybegin + time - result[i]/2;
//        }
//        else
//        {
//            ShadowGrowAutumn[i].value = qQNaN();
//            ShadowWeakAutumn[i].value = qQNaN();
//        }
//    }


//    //для отображения на одном графике используем этот код. Если нужно отображать каждый раз разный график, то в файле shadowdurationyear.cpp переместите
//    //из конструктора ShadowDurationYear экземпляр GraphicYear в функцию UI.(расскоментируйте, а в конструкторе - удалите).
//    QCPRange xRange = ui->widget->xAxis->range();
//    QCPRange yRange = ui->widget->yAxis->range();


//    ui->widget->addGraph();
//    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QPen(Qt::red));
//    ui->widget->graph(ui->widget->graphCount()-1)->data()->set(ShadowGrowSpring);

//    ui->widget->addGraph();
//    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QPen(Qt::blue));
//    ui->widget->graph(ui->widget->graphCount()-1)->data()->set(ShadowWeakSpring);

//    ui->widget->addGraph();
//    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QPen(Qt::red));
//    ui->widget->graph(ui->widget->graphCount()-1)->data()->set(ShadowGrowAutumn);

//    ui->widget->addGraph();
//    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QPen(Qt::blue));
//    ui->widget->graph(ui->widget->graphCount()-1)->data()->set(ShadowWeakAutumn);

//    ui->widget->xAxis->setRange(xRange);
//    ui->widget->yAxis->setRange(yRange);

//    ui->widget->replot();
//}
