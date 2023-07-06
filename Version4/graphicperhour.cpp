//График для дня по часам
#include "graphicperhour.h"
#include "ui_graphicperhour.h"
#include <QDateTime>

GraphicPerHour::GraphicPerHour(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicPerHour)
{
    ui->setupUi(this);
    ui->widget->setInteraction(QCP::iRangeZoom);
    ui->widget->setInteraction(QCP::iRangeDrag);
//    ui->widget->axisRect()->setRangeDrag(Qt::Horizontal);
//    ui->widget->axisRect()->setRangeZoom(Qt::Horizontal);
}

GraphicPerHour::~GraphicPerHour()
{
    delete ui;
}

void GraphicPerHour::SetxAxis(int degrees)
{
    QDateTime xnum;
    QTime timebegin = QTime(0,0,0);
    QDate datebegin = QDate(23,1,1);

    xnum.setDate(datebegin);
    xnum.setTime(timebegin);
    xbegin = xnum.toTime_t() - 13.5*3600; //14 для начала от 00:00
    xend = xbegin+86400;
    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
    timeTicker->setDateTimeFormat("hh:mm");
    timeTicker->setTickCount(24);
    ui->widget->xAxis->setTicker(timeTicker);
    ui->widget->xAxis->setRange(xbegin,xend);
    hours = (degrees-45)/15;
}

void GraphicPerHour::SetyAxis()
{
     ui->widget->yAxis->setRange(0,duration);
}

void GraphicPerHour::AddGraphic(double shadowLength)
{
    if (duration < shadowLength) duration = shadowLength;
    SetyAxis();
    QVector<QCPGraphData> Shadow2(4);
    QVector<QCPGraphData> Shadow(4);
    double time = hours * 3600;
    double znach = xbegin + time;
     if (znach < xbegin)
     {
             Shadow2[0].key = xend + time - shadowLength/2;
             Shadow2[0].value = 0;
             Shadow2[1].key = xend + time - shadowLength/2;
             Shadow2[1].value = shadowLength;
             Shadow2[2].value = shadowLength;
             Shadow2[2].key = xend + time + shadowLength/2;
             Shadow2[3].value = 0;
             Shadow2[3].key = xend + time + shadowLength/2;
             ui->widget->addGraph();
             ui->widget->graph()->data()->set(Shadow2);
     } else
     {
         Shadow[0].key = xbegin + time - shadowLength/2;
         Shadow[0].value = 0;
         Shadow[1].key = xbegin + time - shadowLength/2;
         Shadow[1].value = shadowLength;
         Shadow[2].value = shadowLength;
         Shadow[2].key = xbegin + time + shadowLength/2;
         Shadow[3].value = 0;
         Shadow[3].key = xbegin + time + shadowLength/2;
         ui->widget->addGraph();
         ui->widget->graph()->data()->set(Shadow);
     }
}

void GraphicPerHour::UpdateGraphics()
{
    ui->widget->replot();
}
