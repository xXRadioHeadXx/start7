#include "MainWindowDB.h"

#include <QApplication>
#include <QSplashScreen>

#include <iostream>
#include <QString>
#include "RunGuard.h"
#include "ContextArgMap.h"


int main(int argc, char *argv[])
{

    RunGuard guardCopyDB( "start7_db" );
    if ( !guardCopyDB.tryToRun() )
        return 0;



    try {
        QApplication app(argc, argv);
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

        QPair<QString, QString> argPair;
        for (int count=0; count < argc; ++count) {
            std::string str = argv[count];
            std::cout << count << " " << str << std::endl;
            if(count % 2)
                argPair.first = QString::fromLocal8Bit(str.c_str());
            else {
                argPair.second = QString::fromLocal8Bit(str.c_str());
                ContextArgMap::argMap().insert(argPair.first, argPair.second);
            }
        }

        qDebug() << ContextArgMap::argMap();

        if(ContextArgMap::argMap().contains("-hostname") &&
                ContextArgMap::argMap().contains("-databasename") &&
                ContextArgMap::argMap().contains("-username") &&
                ContextArgMap::argMap().contains("-password") &&
                ContextArgMap::argMap().contains("-port")) {
            DataBaseManager::setHostName(ContextArgMap::argMap().value("-hostname"));
            DataBaseManager::setDatabaseName(ContextArgMap::argMap().value("-databasename"));
            DataBaseManager::setUserName(ContextArgMap::argMap().value("-username"));
            DataBaseManager::setPassword(ContextArgMap::argMap().value("-password"));
            DataBaseManager::setPort(ContextArgMap::argMap().value("-port"));
        }

        QSplashScreen splashScreen(/*const QPixmap& pixmap*/ QPixmap("://icons/logo.png"));

        splashScreen.show();
        splashScreen.showMessage(
            /*const QString &message*/ QObject::tr("Загрузка данных ..."),
            /*int alignment = Qt::AlignLeft*/ Qt::AlignHCenter | Qt::AlignBottom,
            /*const QColor &color = Qt::black*/ Qt::black);

        app.processEvents();

        MainWindowDB w;
        w.show();

        if(!sql.isEmpty()) {
            qDebug() << "w.updSqlQueryStr(" << sql << ");";
            w.updSqlQueryStr(sql);
        }

        splashScreen.finish(/*QWidget * mainWin*/ &w); //this если ваш класс наследуется от QWidget

        return app.exec();
    }
    catch (std::runtime_error &rte)
    {
        qFatal("catch runtime_error %s [main]", rte.what());
    }
    catch (std::exception &e)
    {
        qFatal("Error %s [main]", e.what());
    }
    catch (...)
    {
        qFatal("Error <unknown> [main]");
    }
}
