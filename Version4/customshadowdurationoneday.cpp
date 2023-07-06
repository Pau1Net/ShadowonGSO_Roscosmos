//Отображение расчета времени затенения
#include "customshadowdurationoneday.h"
#include "ui_customshadowdurationoneday.h"
#include <QMessageBox>
#include <onedaycustomorbit.h>
#include "onedaygso.h"
#include <cmath>
#define _USE_MATH_DEFINES

CustomShadowDurationOneDay::CustomShadowDurationOneDay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomShadowDurationOneDay)
{
    ui->setupUi(this);
}

CustomShadowDurationOneDay::~CustomShadowDurationOneDay()
{
    delete ui;
}
//Функция определения положения Солнца и продолжительности тени.
void CustomShadowDurationOneDay::on_pushButton_clicked()
{
    QString text1 = ui->userI->text(), text2 = ui->UserO->text();
    if (text1 == "" || text2 == "") QMessageBox::information(this,"Внимание","Введите значения");
    else
    {
        OneDay = new OneDayCustomOrbit();
        double i = ui->userI->text().toDouble(), omega = ui->UserO->text().toDouble();
        QDate date = ui->dateEdit->date();
        double sunAngle = OneDay->ReducePosSun(omega,i,date);
        ui->resultSinLabel->setText(QString::number(sunAngle));
        double shadowDuration = OneDay->CountShadowDuration();
        if (shadowDuration < 0) {
            ui->ResultDurLabel->setText("Тень отсутвует");
        } else{
        ui->ResultDurLabel->setText(QString::number(shadowDuration));
        }
        double realAngle = asin(sunAngle);
        realAngle = realAngle * 180.0 / 3.14;
        if (realAngle > 0) {
        ui->resultSunlabel->setText(" северной части(+)");
        }
        else{
            ui->resultSunlabel->setText(" южной части(-)");
        }
    }

}
