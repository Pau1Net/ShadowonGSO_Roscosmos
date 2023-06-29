//Один день по часам
#include "durationperhour.h"
#include "ui_durationperhour.h"
#include "onedaygso.h"
#include "graphicperhour.h"
#include <QMessageBox>

DurationPerHour::DurationPerHour(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DurationPerHour)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(-180,180));
    PerHour = new GraphicPerHour();
}

DurationPerHour::~DurationPerHour()
{
    delete ui;
}

void DurationPerHour::on_pushButton_clicked()
{
    int degrees;
    OneDayGSO OneDay = OneDayGSO();
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
    {
        //Из расчетных вариантов(1)
        degrees = 45;
        if (OneDay.CountShadowDuration(ui->dateEdit->date()) != -1)
        {
            degrees = ui->lineEdit->text().toInt();
            PerHour->SetxAxis(degrees);
            PerHour->AddGraphic(OneDay.CountShadowDuration(ui->dateEdit->date()));
            PerHour->UpdateGraphics();
            PerHour->show();
        } else QMessageBox::information(this,"Внимание","В этот день тени нет");
    } else
    {
        if (OneDay.CountShadowDuration(ui->dateEdit->date()) != -1)
        {
            degrees = ui->lineEdit->text().toInt();
            PerHour->SetxAxis(degrees);
            PerHour->AddGraphic(OneDay.CountShadowDuration(ui->dateEdit->date()));
            PerHour->UpdateGraphics();
            PerHour->show();
        } else QMessageBox::information(this,"Внимание","В этот день тени нет");

        double i = ui->userI->text().toDouble();
        double omega = ui->UserO->text().toDouble();
        CustomDay = new OneDayCustomOrbit();
        CustomDay->ReducePosSun(omega,i,ui->dateEdit->date());
        CustomDay->CountShadowDuration();
        if (CustomDay->CountShadowDuration() != -1)
        {
            PerHour->AddGraphic(CustomDay->CountShadowDuration());
            PerHour->UpdateGraphics();
            PerHour->show();
        }

    }
}

void DurationPerHour::on_pushButton_2_clicked()
{
}
