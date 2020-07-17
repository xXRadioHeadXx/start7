#include "MainWindowDB.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowDB w;
    w.show();
    return a.exec();
}
