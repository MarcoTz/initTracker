#include "inittracker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initTracker w;
    w.show();

    return a.exec();
}
