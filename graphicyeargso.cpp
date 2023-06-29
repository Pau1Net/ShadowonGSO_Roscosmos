//График годовой. Qtest
#include "graphicyeargso.h"
#include "ui_graphicyeargso.h"
#include "onedaygso.h"

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

double* CalcShadowDuration()
{
    OneDayGSO CountDuration = OneDayGSO();
    int days = StartingDate.daysInYear();
    QDate date = QDate(2023,01,01);
    double* result = new double[days];
    for(int i = 0; i < days; i++)
    {
        QDate curDate = date.addDays(i);
        result[i] = CountDuration.CountShadowDuration(curDate);
    }
    return result;
}

void GraphicYearGSO::DrawGraphic(int degrees)
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

    double* result = CalcShadowDuration();
    int daysShadow = 0;

    //посчитать кол-во дней с тенью
    for(int i = 0; i < 365; i++)
    {
        if (result[i] != -1) daysShadow++;
    }

    daysShadow = 0;
    for (int i = 0; i< 182; i++)
    {
        if (result[i] != -1) daysShadow++;
    }

    QVector<QCPGraphData> ShadowGrowSpring(daysShadow), ShadowWeakSpring(daysShadow);

    daysShadow = 0;
    for (int i = 182; i< 365; i++)
    {
        if (result[i] != -1) daysShadow++;
    }

    QVector<QCPGraphData> ShadowGrowAutumn(daysShadow), ShadowWeakAutumn(daysShadow);

    int curtime = (degrees - 45)/15; //московское время
    double time = 3600*curtime;

    int days = 0; //для счета дней daysShadow

    for (int i=0; i < 182;i++)
    {
        if (result[i] != -1)
        {
            double znachkey;
            znachkey = ybegin + time + result[i]/2;
            if (znachkey < ybegin)
            {
                ShadowGrowSpring[days].value = yend + time + result[i]/2;
            }
            else ShadowGrowSpring[days].value = ybegin + time + result[i]/2;
            ShadowGrowSpring[days].key = xbegin + 86400*i;

            znachkey = ybegin + time - result[i]/2;
            if (znachkey < ybegin)
            {
                ShadowWeakSpring[days].value = yend + time - result[i]/2;
            }
            else ShadowWeakSpring[days].value = ybegin + time - result[i]/2;
            ShadowWeakSpring[days].key = xbegin + 86400*i;

            days++;
        }
    }

    days = 0;
    for (int i=181; i < 365;i++)
    {

        if (result[i] != -1)
        {
            double znachkey;
            znachkey = ybegin + time + result[i]/2;
            if (znachkey < ybegin)
            {
                ShadowGrowAutumn[days].value = yend + time + result[i]/2;

            }
            else ShadowGrowAutumn[days].value = ybegin + time + result[i]/2;
            ShadowGrowAutumn[days].key = xbegin + 86400*i;

            znachkey = ybegin + time - result[i]/2;
            if (znachkey < ybegin)
            {
                ShadowWeakAutumn[days].value = yend + time - result[i]/2;

            } else ShadowWeakAutumn[days].value = ybegin + time - result[i]/2;

            ShadowWeakAutumn[days].key = xbegin + 86400*i;
            days++;
        }
    }

    ui->widget->rescaleAxes();

    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->graph(0)->data()->set(ShadowGrowSpring);
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::blue));
    ui->widget->graph(1)->data()->set(ShadowWeakSpring);

    ui->widget->addGraph();
    ui->widget->graph(2)->setPen(QPen(Qt::red));
    ui->widget->graph(2)->data()->set(ShadowGrowAutumn);
    ui->widget->addGraph();
    ui->widget->graph(3)->setPen(QPen(Qt::blue));
    ui->widget->graph(3)->data()->set(ShadowWeakAutumn);
    ui->widget->replot();
}
