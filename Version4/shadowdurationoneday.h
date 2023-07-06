#ifndef SHADOWDURATIONONEDAY_H
#define SHADOWDURATIONONEDAY_H

#include <QMainWindow>

namespace Ui {
class ShadowDurationOneDay;
}

class ShadowDurationOneDay : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShadowDurationOneDay(QWidget *parent = 0);
    ~ShadowDurationOneDay();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ShadowDurationOneDay *ui;
};

#endif // SHADOWDURATIONONEDAY_H
