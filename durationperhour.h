#ifndef DURATIONPERHOUR_H
#define DURATIONPERHOUR_H

#include <QMainWindow>
#include "graphicperhour.h"
#include "onedaycustomorbit.h"

namespace Ui {
class DurationPerHour;
}

class DurationPerHour : public QMainWindow
{
    Q_OBJECT

public:
    explicit DurationPerHour(QWidget *parent = 0);
    ~DurationPerHour();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DurationPerHour *ui;
    GraphicPerHour *PerHour;
    OneDayCustomOrbit *CustomDay;
};

#endif // DURATIONPERHOUR_H
