#ifndef CHOOSEACTION_H
#define CHOOSEACTION_H

#include <QMainWindow>
#include "shadowdurationoneday.h"
#include "shadowdurationyear.h"
#include "durationperhour.h"
#include "customshadowdurationoneday.h"

namespace Ui {
class ChooseAction;
}

class ChooseAction : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseAction(QWidget *parent = 0);
    ~ChooseAction();

private slots:
    void on_pushButton_First_clicked();

    void on_pushButton_Second_clicked();

    void on_pushButton_Third_clicked();

    void on_fourTask_clicked();

    void on_pushButton_five_clicked();

private:
    Ui::ChooseAction *ui;
    ShadowDurationOneDay *OneDayGSO;
    ShadowDurationYear *YearGSO;
    DurationPerHour *PerHour;
    CustomShadowDurationOneDay *OneDayCustom;
//    CountAbsoluteShadowDuration *Sar;
};

#endif // CHOOSEACTION_H
