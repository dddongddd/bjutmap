#include "map.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    map w;
    w.show();
    return a.exec();
}
