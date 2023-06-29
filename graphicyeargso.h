#ifndef GRAPHICYEARGSO_H
#define GRAPHICYEARGSO_H

#include <QMainWindow>

namespace Ui {
class GraphicYearGSO;
}

class GraphicYearGSO : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicYearGSO(QWidget *parent = 0);
    ~GraphicYearGSO();
    void DrawGraphic(int);

private:
    Ui::GraphicYearGSO *ui;
};

#endif // GRAPHICYEARGSO_H
