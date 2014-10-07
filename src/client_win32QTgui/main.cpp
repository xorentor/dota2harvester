#include "d2h.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    d2h w;
    w.show();

    return a.exec();
}
