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
        std::cout << count << " " << str << &endl;
        if(count % 2)
            argPair.first = QString::fromLocal8Bit(str.c_str()).toLower();
        else {
            argPair.second = QString::fromLocal8Bit(str.c_str());
            argMap.insert(argPair.first, argPair.second);
        }
    }

    if(argMap.contains("-hostname") &&
            argMap.contains("-databasename") &&
            argMap.contains("-username") &&
            argMap.contains("-password") &&
            argMap.contains("-port")) {
        DataBaseManager::setHostName(argMap.value("-hostname"));
        DataBaseManager::setDatabaseName(argMap.value("-databasename"));
        DataBaseManager::setUserName(argMap.value("-username"));
        DataBaseManager::setPassword(argMap.value("-password"));
        DataBaseManager::setPort(argMap.value("-port"));
    }

    MainWindowDB w;
    w.show();

    if(argMap.contains("-sql"))
        w.updSqlQueryStr(argMap.value("-sql"));

    return a.exec();
}
