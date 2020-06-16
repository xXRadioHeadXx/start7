#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql>

#include <JourEntity.h>
#include <MessageEntity.h>

class DataBaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseManager(QObject *parent = nullptr) noexcept;
    ~DataBaseManager() noexcept;

    static QSqlDatabase& m_db();

    static int insertCommandMsg_wS(const MessageEntity &msg);
    static int insertCommandMsg(const MessageEntity &msg);
    static int insertJourMsg_wS(const JourEntity &msg);
    static int insertJourMsg(const JourEntity &msg);
    static int updateJourMsg_wS(const JourEntity &msg);
    static int updateJourMsg(const JourEntity &msg);
    static QList<JourEntity *> getMSGRecordAfter(const int &id = 0);
    static QList<JourEntity *> getMSGRecord(const int &id = -1);
    static QList<QString> getReasonGroup();
    static QList<QString> getMeasuresGroup();


    void loadSettings(QString fileName = "rifx.ini");

private:
    QString HostName;//("127.0.0.1");
    QString DatabaseName;//("postgres");
    QString UserName;//("postgres");
    QString Password;//("601275");
    QString Port;//(5432);

signals:

};

#endif // DATABASEMANAGER_H
