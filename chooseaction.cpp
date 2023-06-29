//Главное окно сигналов(первое)
#include "chooseaction.h"
#include "ui_chooseaction.h"
#include "shadowdurationoneday.h"
#include "shadowdurationyear.h"
#include "shadowdurationoneday.cpp"
#include <QDebug>

ChooseAction::ChooseAction(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseAction)
{
    ui->setupUi(this);
}

ChooseAction::~ChooseAction()
{
    delete ui;
}

void ChooseAction::on_pushButton_First_clicked()
{
    OneDayGSO = new ShadowDurationOneDay();
    OneDayGSO->show();
}

void ChooseAction::on_pushButton_Second_clicked()
{
        YearGSO = new  ShadowDurationYear();
        YearGSO->show();
}

void ChooseAction::on_pushButton_Third_clicked()
{
    PerHour = new DurationPerHour();
    PerHour->show();
}

void ChooseAction::on_fourTask_clicked()
{
    OneDayCustom = new CustomShadowDurationOneDay();
    OneDayCustom->show();
}
//TODO Система автоматического расчета. Дописать блок.
void ChooseAction::on_pushButton_five_clicked()
{
//    try {
//        Sar = new CountAbsoluteShadowDuration();
//        Sar->show();
//    }
//    catch (const MyException& e) {
//        qDebug() << "В блоке №five_clicked ошибка. Проверьте этот блок" << e.what();
//    }
//    Sar = new CountAbsoluteShadowDuration();
//    Sar->show();
}
