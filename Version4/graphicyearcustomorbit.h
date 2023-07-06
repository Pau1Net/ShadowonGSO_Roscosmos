#ifndef GRAPHICYEARCUSTOMORBIT_H
#define GRAPHICYEARCUSTOMORBIT_H

#include <QWidget>

namespace Ui {
class graphicyearcustomorbit;
}

class graphicyearcustomorbit : public QWidget
{
    Q_OBJECT

public:
    explicit graphicyearcustomorbit(QWidget *parent = 0);
    ~graphicyearcustomorbit();

private:
    Ui::graphicyearcustomorbit *ui;
};

#endif // GRAPHICYEARCUSTOMORBIT_H
