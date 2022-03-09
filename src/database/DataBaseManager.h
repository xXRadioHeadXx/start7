#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql>
#include "ShedulerNewDuty.h"

#include "JourEntity.h"

class DataBaseManager : public QObject
{
    Q_OBJECT

    static qint64 idStartLastDuty;

    static QSharedPointer<ShedulerNewDuty> shedulerNewDuty;
    static QStringList fields;
    static QMetaType::Type fieldType(QString field);

public:
    explicit DataBaseManager(QObject *parent = nullptr) noexcept;
    ~DataBaseManager() noexcept;

    static QSqlDatabase m_db();

//    static int insertCommandMsg_wS(const MessageEntity &msg);
//    static int insertCommandMsg(const MessageEntity &msg);
    static int insertJourMsg_wS(const JourEntity &msg);
    static int insertJourMsg(const JourEntity &msg);
    static int updateJourMsg_wS(JourEntity &msg);
    static int updateJourMsg(JourEntity &msg);
    static int updateJourMsgFieldById(const QString field, const QVariant value, const QSet<int> setId);
    static void resetAllFlags_wS();
    static void resetAllFlags();
    static QList<JourEntity> getMSGRecordAfter(const int &id = 0);
    static QList<JourEntity> getOneMSGRecord(const int &id = -1);
//    static QList<JourEntity> getMSGRecords();
    static QList<JourEntity> getFltMSGRecordAfter(const QString flt = "", const int &id = 0);
    static QList<JourEntity> getFltOneMSGRecord(const QString flt = "", const int &id = -1);
//    static QList<JourEntity> getFltMSGRecords(const QString flt = "");
    static QList<JourEntity> getQueryMSGRecord(QString sql);
    static QList<JourEntity> getQueryMSGRecord(QSqlQuery query);
    static QList<JourEntity> getJourRecordAfter(const int &id, const int &limit = -1);
    static QList<JourEntity> getJourRecordAfter(const QDateTime &from, const int &limit = -1);

    static int executeQuery(QString sql);
    static int executeQuery(QSqlQuery query);

    static QList<QString> getReasonGroup();
    static QList<QString> getMeasuresGroup();
    static QList<QString> getDirectionGroup();
    static QList<QString> getD1Group();
    static QList<QString> getD2Group();
    static QList<QString> getD3Group();
    static QList<QString> getD4Group();

    void loadSettings(QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    static QString dateFlt(QDate from, QDate to);
    static QString objectFlt(JourEntity::TypeObject oType/*, int d1 = 0, int d2 = 0, int d3 = 0*/);
    static QString eventFlt(JourEntity::TypeEvent eType, JourEntity::TypeObject oType);
    static QString connectObjectFlt(JourEntity::TypeConnectObject coType);
    static QString directionFlt(QString direction);
    static QString num1Flt(const QString &num1);
    static QString num2Flt(const QString &num2);
    static QString num3Flt(const QString &num3);
    static QString outFlt(const int &out);
    static QString adamOff(const int &adamOff);


    static qint64 getIdStartLastDuty();
    static void setIdStartLastDuty(qint64 value);
    static void setIdStartLastDuty();

    static QString getHostName();
    static void setHostName(const QString &value);

    static QString getDatabaseName();
    static void setDatabaseName(const QString &value);

    static QString getUserName();
    static void setUserName(const QString &value);

    static QString getPassword();
    static void setPassword(const QString &value);

    static QString getPort();
    static void setPort(const QString &value);

    static int checkNecessarilyReasonMeasureFill();

private:
    static QString HostName;//("127.0.0.1");
    static QString DatabaseName;//("postgres");
    static QString UserName;//("postgres");
    static QString Password;//("601275");
    static QString Port;//(5432);

signals:

};

#endif // DATABASEMANAGER_H
