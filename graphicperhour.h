#ifndef GRAPHICPERHOUR_H
#define GRAPHICPERHOUR_H

#include <QMainWindow>

namespace Ui {
class GraphicPerHour;
}

class GraphicPerHour : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicPerHour(QWidget *parent = 0);
    ~GraphicPerHour();
    void SetxAxis(int);
    void AddGraphic(double);
    void UpdateGraphics();

private:
    Ui::GraphicPerHour *ui;
    void SetyAxis();
    double xbegin, xend;
    int hours;
    double duration = 0;
};

#endif // GRAPHICPERHOUR_H
