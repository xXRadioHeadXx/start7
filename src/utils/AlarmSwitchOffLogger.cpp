#include "AlarmSwitchOffLogger.h"

#include <QCoreApplication>
#include <QFile>
#include <QDateTime>
#include "DataBaseManager.h"

bool AlarmSwitchOffLogger::isRuning() const
{
    return runing;
}

void AlarmSwitchOffLogger::setRuning(bool value)
{
    runing = value;
}

AlarmSwitchOffLogger::AlarmSwitchOffLogger(QObject * parent) :
    QThread(parent)
{
    try {
        QFile file( QCoreApplication::applicationDirPath() + "/AlarmSwitchOffLog.txt" );
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QString str = file.readLine();

        JourEntity msg;
        msg.setObject(tr("Оператор"));
        msg.setType(904);
        msg.setComment(tr("Аварийное завершение работы программы"));
        msg.setCdate(QDateTime::fromString(str, "dd.MM.yyyy hh:mm:ss"));
        DataBaseManager::insertJourMsg(msg);
    }  catch (...) {

    }

}

AlarmSwitchOffLogger::~AlarmSwitchOffLogger()
{
    setRuning(false);
    wait();

    QFile file ( QCoreApplication::applicationDirPath() + "/AlarmSwitchOffLog.txt" );
    file.remove();
}

void AlarmSwitchOffLogger::run()
{
    setRuning(true);
    while(isRuning()) {
        try {
            QFile file( QCoreApplication::applicationDirPath() + "/AlarmSwitchOffLog.txt" );
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;

            file.write(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss").toLocal8Bit());
            file.close();

            msleep(1000);
        }  catch (...) {

        }
    }
}
