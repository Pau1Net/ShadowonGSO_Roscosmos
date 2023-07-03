#ifndef CUSTOMSHADOWDURATIONONEDAY_H
#define CUSTOMSHADOWDURATIONONEDAY_H

#include <QMainWindow>
#include <onedaycustomorbit.h>

namespace Ui {
class CustomShadowDurationOneDay;
}

class CustomShadowDurationOneDay : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomShadowDurationOneDay(QWidget *parent = 0);
    ~CustomShadowDurationOneDay();
        double ReturnDuration();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CustomShadowDurationOneDay *ui;
    OneDayCustomOrbit *OneDay;
};

#endif // CUSTOMSHADOWDURATIONONEDAY_H
