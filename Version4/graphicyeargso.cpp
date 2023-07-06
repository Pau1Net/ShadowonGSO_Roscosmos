#include "graphicyeargso.h"
#include "ui_graphicyeargso.h"
//#include "onedaygso.h"
#include "onedaycustomorbit.h"
#include <QVector>
#include <QPair>
#include <QMap>
#include <QFile>
#include <QTextStream>

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

//QVector<ShadowData> CalcShadowDurationM(double i, double o)
//{
//    OneDayCustomOrbit CountDuration = OneDayCustomOrbit();
//    int days = StartingDate.daysInYear();
//    QDate date = QDate(2023, 01, 01);
//    QVector<ShadowData> result;
//    for (int j = 0; j < days; j++)
//    {
//        QDate curDate = date.addDays(j);
//        CountDuration.ReducePosSun(i,o,curDate);
//        QVector<ShadowData> dayResult = CountDuration.CountShadowDurationM();
//        result.append(dayResult);
//    }
//    return result;
//}
QMap<QDate, QVector<ShadowData> > CalcShadowDurationM(double i, double o)
{
    OneDayCustomOrbit CountDuration = OneDayCustomOrbit();
    int days = StartingDate.daysInYear();
    QDate date = QDate(2023, 01 , 01);
    QMap<QDate, QVector<ShadowData> > result;
    for(int j = 0; j < days; j++)
    {
        QDate curDate = date.addDays(j);
        CountDuration.ReducePosSun(i,o,curDate);
        QVector<ShadowData> dayResult = CountDuration.CountShadowDurationM();
        result[curDate] = dayResult;
    }
//    QVector<ShadowData> shadow;
//    QFile file("C:/Users/LipantevaIV/Desktop/practics2023/data.txt");
//    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        QTextStream out(&file);

//        for (const auto& shadow : result)
//        {
//            out << "Start: " << shadow.start << "End: " << shadow.end << "\n";
//        }

//        file.close();
//    }
//    else{
//        qWarning("Not open file.");
//    }
    return result;
}

void GraphicYearGSO::DrawGraphic(int degrees, double i, double o)
{
    QDateTime xnum;
    QDate datebegin = QDate(2023, 1, 1);
    QDate dateend = QDate(2023, 12, 31);

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
    ui->widget->yAxis->setTicker(timeTicker);//вот сюда можно добавить
    ui->widget->yAxis->setRange(ybegin,yend);

    QMap<QDate, QVector<ShadowData> > result = CalcShadowDurationM(i, o);

    QCPRange xRange = ui->widget->xAxis->range(); //в качестве адаптации ко времени от 1 до 144, можно в эту неисп ф-ю добавить цикл, который проходит по этим итерациям.
    QCPRange yRange = ui->widget->yAxis->range();

//Сюда можно подставить просчет времени-----------------------------------------
    int graphCount = 0;
    for(auto it = result.begin(); it != result.end(); ++it )
    {
        QVector<ShadowData> dayResult = it.value();
        if(dayResult.size() < 2){
            continue;
        }
        double x = QDateTime(it.key()).toTime_t();

        for(auto &ShadowData : dayResult)
        {
            double yBegin = yRange.lower + ShadowData.start * (yRange.upper - yRange.lower);
            double yEnd = yRange.lower + ShadowData.end * (yRange.upper - yRange.lower);
            ui->widget->addGraph();
            ui->widget->graph(graphCount)->addData(x, yBegin);
            ui->widget->graph(graphCount)->addData(x, yEnd);
        }

    }

//    QVector<ShadowData> result = CalcShadowDurationM(i, o);
//    int daysInYear = StartingDate.daysInYear();

//    QCPRange xRange = ui->widget->xAxis->range();
//    QCPRange yRange = ui->widget->yAxis->range();

//    const int maxGraphs = 360;
//    int graphCount = 0;

//    for (int day = 0; day < daysInYear && graphCount < maxGraphs; day++)
//    {
//        ui->widget->addGraph();
//        double x = xRange.lower + day * (xRange.upper - xRange.lower) / daysInYear;
//        for (int resIdx = 0; resIdx < result.size(); resIdx++)
//        {
//            double yBegin = yRange.lower + result[resIdx].start * (yRange.upper - yRange.lower);
//            double yEnd = yRange.lower + result[resIdx].end * (yRange.upper - yRange.lower);
//            ui->widget->graph(graphCount)->addData(x, yBegin);
//            ui->widget->graph(graphCount)->addData(x, yEnd);
//        }
//        graphCount++;

//    }
}
//здесь все нормально |(up)


//Функция расчета тени с использованием наклонения.
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
////    int daysShadow = 0;

//    QVector<QCPGraphData> ShadowGrowSpring(daysInYear), ShadowWeakSpring(daysInYear);
//    QVector<QCPGraphData> ShadowGrowAutumn(daysInYear), ShadowWeakAutumn(daysInYear);

//    int curtime = (degrees-45)/15;
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
//            ShadowGrowSpring[i].value = qQNaN(); //для обнуления дней с тенью(отображались, как вертикальная, фиолетоая линия на графиках)
//            ShadowWeakSpring[i].value = qQNaN();
//        }
//    }

//    for (int i=daysInYear/2; i<daysInYear;i++)
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


////    //посчитать кол-во дней с тенью
////    for(int i = 0; i < daysInYear; i++)
////    {
////        if (result[i] != -1) daysShadow++;
////    }

////    int daysShadowSpring = 0;
////    for (int i = 0; i< daysInYear/2 ; i++)
////    {
////        if (result[i] != -1) daysShadowSpring++;
////    }

////    QVector<QCPGraphData> ShadowGrowSpring(daysShadow), ShadowWeakSpring(daysShadow);

////    int daysShadowAutumn = 0;
////    for (int i = daysInYear/2 ; i< daysInYear; i++)
////    {
////        if (result[i] != -1) daysShadowAutumn++;
////    }

////    QVector<QCPGraphData> ShadowGrowAutumn(daysShadow), ShadowWeakAutumn(daysShadow);

////    int curtime = (degrees-45)/15; //московское время
////    double time = 3600*curtime;

////    int days = 0; //для счета дней daysShadow

////    for (int i=0; i < daysInYear/2 ;i++)
////    {
////        if (result[i] != -1)
////        {
////            double znachkey;
////            znachkey = ybegin + time + result[i]/2;
////            if (znachkey < ybegin)
////            {
////                ShadowGrowSpring[days].value = yend + time + result[i]/2;
////            }
////            else ShadowGrowSpring[days].value = ybegin + time + result[i]/2;
////            ShadowGrowSpring[days].key = xbegin + 86400*i;

////            znachkey = ybegin + time - result[i]/2;
////            if (znachkey < ybegin)
////            {
////                ShadowWeakSpring[days].value = yend + time - result[i]/2;
////            }
////            else ShadowWeakSpring[days].value = ybegin + time - result[i]/2;
////            ShadowWeakSpring[days].key = xbegin + 86400*i;

////            days++;
////        }
//////        else {
//////            ShadowGrowSpring[i].value = qQNaN();
//////            ShadowWeakSpring[i].value = qQNaN();
//////        }
////    }

////    days = 0;
////    for (int i=daysInYear/2 - 1; i < daysInYear;i++)
////    {

////        if (result[i] != -1)
////        {
////            double znachkey;
////            znachkey = ybegin + time + result[i]/2;
////            if (znachkey < ybegin)
////            {
////                ShadowGrowAutumn[days].value = yend + time + result[i]/2;

////            }
////            else ShadowGrowAutumn[days].value = ybegin + time + result[i]/2;
////            ShadowGrowAutumn[days].key = xbegin + 86400*i;

////            znachkey = ybegin + time - result[i]/2;
////            if (znachkey < ybegin)
////            {
////                ShadowWeakAutumn[days].value = yend + time - result[i]/2;

////            } else ShadowWeakAutumn[days].value = ybegin + time - result[i]/2;

////            ShadowWeakAutumn[days].key = xbegin + 86400*i;
////            days++;
////        }
////        else {
////            ShadowGrowAutumn[i].value = qQNaN();
////            ShadowWeakAutumn[i].value = qQNaN();
////        }

////    ui->widget->rescaleAxes();


////    ui->widget->clearGraphs();

////    ui->widget->addGraph();
////    ui->widget->graph(0)->setPen(QPen(Qt::red));
////    ui->widget->graph(0)->data()->set(ShadowGrowSpring);
////    ui->widget->addGraph();
////    ui->widget->graph(1)->setPen(QPen(Qt::blue));
////    ui->widget->graph(1)->data()->set(ShadowWeakSpring);

////    ui->widget->addGraph();
////    ui->widget->graph(2)->setPen(QPen(Qt::red));
////    ui->widget->graph(2)->data()->set(ShadowGrowAutumn);
////    ui->widget->addGraph();
////    ui->widget->graph(3)->setPen(QPen(Qt::blue));
////    ui->widget->graph(3)->data()->set(ShadowWeakAutumn);

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
