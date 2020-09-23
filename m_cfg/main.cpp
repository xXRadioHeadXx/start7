#include "MainWindowCFG.h"
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//First change

    MainWindowCFG w;
    w.show();

    return a.exec();
}
