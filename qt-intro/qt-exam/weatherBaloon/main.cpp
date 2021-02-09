#include <QApplication>
#include "weatherballoon.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    weatherBalloon w;
    w.show();
    return a.exec();
}
