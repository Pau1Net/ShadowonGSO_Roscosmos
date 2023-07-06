#include "chooseaction.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChooseAction w;
    w.show();

    return a.exec();
}
