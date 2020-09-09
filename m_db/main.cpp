#include "MainWindowDB.h"

#include <QApplication>

#include <iostream>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Перебираем каждый аргумент и выводим его порядковый номер и значение
    QMap<QString, QString> argMap;
    QPair<QString, QString> argPair;
    for (int count=0; count < argc; ++count) {
        std::string str = argv[count];
        std::cout << count << " " << str << endl;
        if(count % 2)
            argPair.first = QString::fromLocal8Bit(str.c_str());
        else {
            argPair.second = QString::fromLocal8Bit(str.c_str());
            argMap.insert(argPair.first, argPair.second);
        }
    }


    MainWindowDB w;
    w.show();

    if(argMap.contains("-sql"))
        w.updSqlQueryStr(argMap.value("-sql"));

    return a.exec();
}
