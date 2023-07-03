#ifndef SHADOWDURATIONYEAR_H
#define SHADOWDURATIONYEAR_H

#include <QMainWindow>
#include "graphicyeargso.h"
#include "customshadowdurationoneday.h"

namespace Ui {
class ShadowDurationYear;
}

class ShadowDurationYear : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShadowDurationYear(QWidget *parent = 0);
    ~ShadowDurationYear();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ShadowDurationYear *ui;
    GraphicYearGSO *GraphicYear;
};

#endif // SHADOWDURATIONYEAR_H
