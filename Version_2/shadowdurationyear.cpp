#include "shadowdurationyear.h"
#include "ui_shadowdurationyear.h"
#include "graphicyeargso.h"
#include "onedaygso.h"
#include <QMessageBox>

ShadowDurationYear::ShadowDurationYear(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShadowDurationYear)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(-180,180));
    GraphicYear = new GraphicYearGSO();
}

ShadowDurationYear::~ShadowDurationYear()
{
    delete ui;
}

void ShadowDurationYear::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty())
    {
        QMessageBox::information(this,"Внимание","Введите все параметры!");
    }
    else
    {
        if(ui->lineEdit->text().toInt() > 180 || ui->lineEdit->text().toInt() < -180 ); // QMessageBox::information(this,"Внимание","Введено неправильное значение долготы");
        else
        {
            int degrees = ui->lineEdit->text().toInt();
            double i = ui->lineEdit_3->text().toDouble();
            double o = ui->lineEdit_4->text().toDouble();
//            GraphicYear = new GraphicYearGSO();
            GraphicYear->DrawGraphic(degrees, i, o);
            GraphicYear->show();
        }
    }
}

void ShadowDurationYear::on_pushButton_2_clicked()
{
    OneDayGSO oneDay;
    oneDay.setSunAngle(1); //i = 100; Omega = 100;  cos

    double apoapsis = 36000;
    double periapsis = 2000;

    double shadowDuration = oneDay.CountShadowDurationByOrbitHeight(apoapsis, periapsis);
    QString text = QString("%1 секунд").arg(shadowDuration);
    ui->lineEdit_2->setText(text);
}
//setSunAngle - подставляет в косинус. Для перевода в синус, нужна 1 строчка кода.
/*
 * TODO
 */
// p - 400; a - 36000 = 4674
//p - 400; a - 37000 = 4442
//p - 400; a - 39000 = 3983
//p - 400; a - 35000 = 4910
//p - 400; a - 33000 = 5393
// p - 500; a - 36000 = 4651
//p - 1000; a - 36000 = 4534
//p - 2000; a - 36000 = 4300
