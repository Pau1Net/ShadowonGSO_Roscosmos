#include "shadowdurationyear.h"
#include "ui_shadowdurationyear.h"
#include "graphicyeargso.h"
#include <QMessageBox>

ShadowDurationYear::ShadowDurationYear(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShadowDurationYear)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(-180,180));
}

ShadowDurationYear::~ShadowDurationYear()
{
    delete ui;
}

void ShadowDurationYear::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"Внимание","Введите долготу");
    }
    else
    {
        if(ui->lineEdit->text().toInt() > 180 || ui->lineEdit->text().toInt() < -180 );//  QMessageBox::information(this,"Внимание","Введено неправильное значение долготы");
        else
        {
            int degrees = ui->lineEdit->text().toInt();
            GraphicYear = new GraphicYearGSO();
            GraphicYear->DrawGraphic(degrees);
            GraphicYear->show();
        }
    }
}

void ShadowDurationYear::on_pushButton_2_clicked()
{
    OneDayGSO oneDay;
    oneDay.setSunAngle(0.0133); // Заменить

    // Значения для апоцентра и перицентра
    double apoapsis = 36000;
    double periapsis = 400;

    // Вызов функции и вывод результата
    double shadowDuration = oneDay.CountShadowDurationByOrbitHeight(apoapsis, periapsis);
    QString text = QString("%1 секунд").arg(shadowDuration);
        ui->lineEdit_2->setText(text);
//    qDebug() << "Shadow duration for orbit height " << (apoapsis + periapsis) / 2 << ": " << shadowDuration;
//    ui->lineEdit_2->setText(QString::number(shadowDuration));
}

/*
 *
 * TODO
 * Сделать автоматическую систему расчета времени пуска, с построением графиков(окна старта)
 */

