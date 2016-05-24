

#include <iostream>
#include <QApplication>
#include <QTime>
#include "dialog.h"
using namespace std;
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Dialog d;
    d.show();
    return app.exec();
}
