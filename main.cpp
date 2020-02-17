#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;

    w.setFixedSize(220,250);
    w.show();
    return a.exec();
}
