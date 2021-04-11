#include "MainWindowDB.h"

#include <QApplication>

#include <iostream>
#include <QString>
#include <RunGuard.h>

int main(int argc, char *argv[])
{

    RunGuard guardCopyDB( "start7_db" );
    if ( !guardCopyDB.tryToRun() )
        return 0;

    QApplication a(argc, argv);
    // Перебираем каждый аргумент и выводим его порядковый номер и значение
    QString argString;
    for (int count=0; count < argc; ++count) {
        argString += " " + QString::fromLatin1(argv[count]);
    }

    QRegExp regExpSql("-sql\\s*\\\".*\\\"");
    QStringList sl;
    if (-1 != regExpSql.indexIn(argString)) {
        sl = regExpSql.capturedTexts();
    }
    QString sql;
    if(!sl.isEmpty()) {
        sql = sl.first().section('"', 1, 1);
    }
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    sql = codec->toUnicode(sql.toLatin1());

    QMap<QString, QString> argMap;
    QPair<QString, QString> argPair;
    for (int count=0; count < argc; ++count) {
        std::string str = argv[count];
//        std::cout << count << " " << str << std::endl;
        if(count % 2)
            argPair.first = QString::fromLocal8Bit(str.c_str());
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

    if(!sql.isEmpty()) {
        qDebug() << "w.updSqlQueryStr(" << sql << ");";
        w.updSqlQueryStr(sql);
    }

    return a.exec();
}
