#include "MainWindowCFG.h"
#include <QDebug>
#include "Icons.h"
#include <QIcon>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//First change

    MainWindowCFG w;
    w.setWindowIcon(QIcon::fromTheme(":icons/exec.png"));
    w.show();

    return a.exec();
}
