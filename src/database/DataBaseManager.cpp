#include <QStringBuilder>

#include <DataBaseManager.h>
#include <SignalSlotCommutator.h>
#include <JourEntity.h>
#include <JourEntity.h>
#include <Utils.h>

DataBaseManager::DataBaseManager(QObject *parent) noexcept :
    QObject(parent)
{
    if(m_db().isValid() || m_db().isOpen())
    {
        m_db().close();
    }

//    loadSettings();
    m_db();
}

QSqlDatabase& DataBaseManager::m_db()
{
    static QSqlDatabase db;
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QPSQL");

        QSettings settings("rifx.ini", QSettings::IniFormat);
        settings.beginGroup("PostgresSQL");

        QString hostName = settings.value( "HostName", -1 ).toString();//("127.0.0.1");
        hostName = Utils::strHostAddress(hostName);
        QString databaseName = settings.value( "DatabaseName", -1 ).toString();//("postgres");
        QString userName = settings.value( "UserName", -1 ).toString();//("postgres");
        QString password = settings.value( "Password", -1 ).toString();//("601275");
        QString port = settings.value( "Port", -1 ).toString();//(5432);
        qDebug() << hostName << " " << databaseName << " " << userName << " " << password << " " << port;

        settings.endGroup();

        db.setHostName(hostName);
        db.setDatabaseName(databaseName);
        db.setUserName(userName);
        db.setPassword(password);
        db.setPort(port.toUInt());
        db.open(userName, password);
        if (!db.isOpen())
        {
            qDebug() << "Cannot open database: Error: " << db.lastError();
        }
        else
        {
            qDebug()<<"Opened database: " << db.connectOptions();
        }
    }

    if (!db.isOpen())
    {
        QSettings settings("rifx.ini", QSettings::IniFormat);
        settings.beginGroup("PostgresSQL");
        QString userName = settings.value( "UserName", -1 ).toString();//("postgres");
        QString password = settings.value( "Password", -1 ).toString();//("601275");
        qDebug() << userName << " " << password;
        settings.endGroup();

        db.open(userName, password);
    }
    return db;
}

DataBaseManager::~DataBaseManager() noexcept
{
    if(m_db().isOpen())
        m_db().close();
}

int DataBaseManager::insertCommandMsg_wS(const MessageEntity &msg) {
    int lastInsertId = insertCommandMsg(msg);
    if(0 != lastInsertId)
        SignalSlotCommutator::getInstance()->emitInsNewCommandMSG(/*lastInsertId*/);
//        emit this->insertNewMSG();
    return lastInsertId;
}


int DataBaseManager::insertCommandMsg(const MessageEntity &msg)
{

    QString sql;
    sql = " INSERT INTO public.message ( ";
    if(msg.getCdate().isValid())
        sql += "cdate, ";
    if(msg.getMdate().isValid())
        sql += "mdate, ";
    sql += " object, operatorid, direction, bytearraydata) VALUES ( ";
    if(msg.getCdate().isValid())
        sql += "to_timestamp(:vCdate, 'YYYY-MM-DD HH24:MI:SS.MS'), ";
    if(msg.getMdate().isValid())
        sql += "to_timestamp(:vMdate, 'YYYY-MM-DD HH24:MI:SS.MS'), ";
    sql += " :vObject, :vOperatorid, :vDirection, :vBytearraydata); ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(msg.getCdate().isValid())
        query.bindValue(":vCdate", msg.getCdate().toString("yyyy-MM-dd hh:mm:ss.z"));
    if(msg.getMdate().isValid())
        query.bindValue(":vMdate", msg.getMdate().toString("yyyy-MM-dd hh:mm:ss.z"));
    query.bindValue(":vObject", msg.getObject());
    query.bindValue(":vOperatorid", msg.getOperatorid());
    query.bindValue(":vDirection", msg.getDirection());
    query.bindValue(":vBytearraydata", msg.getBytearraydata());

    if(query.exec())
    {
        qDebug() << "DataBaseManager::addNewMsg :" << query.lastInsertId().toUInt();
//        emit this->insertNewMSG(query.lastInsertId().toUInt());
        return query.lastInsertId().toUInt();
    }
    else
    {
        qDebug() << "DataBaseManager::addNewMsg Error :" << query.lastError().text();
        qDebug() << query.lastQuery();
        qDebug() << query.boundValues();
        return 0;
    }

    return 0;
}

int DataBaseManager::insertJourMsg_wS(const JourEntity &msg) {
    int lastInsertId = insertJourMsg(msg);
    if(0 != lastInsertId)
        SignalSlotCommutator::getInstance()->emitInsNewJourMSG(/*lastInsertId*/);
//        emit this->insertNewMSG();
    return lastInsertId;
}


int DataBaseManager::insertJourMsg(const JourEntity &msg)
{

    QString sql;
    sql = " INSERT INTO public.jour ( ";
    if(msg.getCdate().isValid())
        sql += "cdate, ";
    if(msg.getMdate().isValid())
        sql += "mdate, ";
    sql += "comment, object, reason, measures, operatorid, status, direction) VALUES ( ";
    if(msg.getCdate().isValid())
        sql += "to_timestamp(:vCdate, 'YYYY-MM-DD HH24:MI:SS.MS'), ";
    if(msg.getMdate().isValid())
        sql += "to_timestamp(:vMdate, 'YYYY-MM-DD HH24:MI:SS.MS'), ";
    sql += ":vComment, :vObject, :vReason, :vMeasures, :vOperatorid, :vStatus, :vDirection); ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(msg.getCdate().isValid())
        query.bindValue(":vCdate", msg.getCdate().toString("yyyy-MM-dd hh:mm:ss.z"));
    if(msg.getMdate().isValid())
        query.bindValue(":vMdate", msg.getMdate().toString("yyyy-MM-dd hh:mm:ss.z"));
    query.bindValue(":vComment", msg.getComment());
    query.bindValue(":vObject", msg.getObject());
    query.bindValue(":vReason", msg.getReason());
    query.bindValue(":vMeasures", msg.getMeasures());
    query.bindValue(":vOperatorid", msg.getOperatorid());
    query.bindValue(":vStatus", msg.getStatus());
    query.bindValue(":vDirection", msg.getDirection());

    if(query.exec())
    {
        qDebug() << "DataBaseManager::addNewMsg :" << query.lastInsertId().toUInt();
//        emit this->insertNewMSG(query.lastInsertId().toUInt());
        return query.lastInsertId().toUInt();
    }
    else
    {
        qDebug() << "DataBaseManager::addNewMsg Error :" << query.lastError().text();
        qDebug() << query.lastQuery();
        qDebug() << query.boundValues();
        return 0;
    }

    return 0;
}

int DataBaseManager::updateJourMsg_wS(const JourEntity &msg) {
    int lastUpdateId = updateJourMsg(msg);
    if(0 != lastUpdateId)
        SignalSlotCommutator::getInstance()->emitUpdJourMSG(lastUpdateId);
//        emit this->updateMSG(lastUpdateId);
    return lastUpdateId;
}

int DataBaseManager::updateJourMsg(const JourEntity &msg)
{

    QString sql;
    sql =  " UPDATE public.jour \
             SET comment=:vComment, \
             object=:vObject, \
             reason=:vReason, \
             measures=:vMeasures, \
             operatorid=:vOperatorid, \
             status=:vStatus, \
             mdate=to_timestamp(:vMdate, 'YYYY-MM-DD HH24:MI:SS.MS'), \
             direction=:vDirection \
             WHERE id = :vId ";

    QSqlQuery query(m_db());
    query.prepare(sql);




    query.bindValue(":vComment", msg.getComment());
    query.bindValue(":vObject", msg.getObject());
    query.bindValue(":vReason", msg.getReason());
    query.bindValue(":vMeasures", msg.getMeasures());
    query.bindValue(":vOperatorid", msg.getOperatorid());
    query.bindValue(":vStatus", msg.getStatus());
    query.bindValue(":vMdate", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.z"));
    query.bindValue(":vDirection", msg.getDirection());
    query.bindValue(":vId", msg.getId());

    if(query.exec())
    {
        qDebug() << "DataBaseManager::updMsg :" << msg.getId();
//        emit this->updateMSG(msg.getId());
        return msg.getId();
    }
    else
    {
        qDebug() << "DataBaseManager::updMsg Error :" << query.lastError().text();
        qDebug() << query.lastQuery();
        qDebug() << query.boundValues();
        return 0;
    }
}

QList<JourEntity *> DataBaseManager::getMSGRecordAfter(const int &id) /*const*/ {
    QList<JourEntity *> result;
    QString sql;
    sql = "SELECT * FROM jour ";
    if(id > 0)
        sql += " WHERE id > :id ";
    sql += " ORDER BY id ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":id", id);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            JourEntity * me = new JourEntity;
            me->setId(rec.value("id").toInt());
            me->setCdate(rec.value("cdate").toDateTime());

            me->setComment(rec.value("comment").toString());
            me->setObject(rec.value("object").toString());
            me->setReason(rec.value("reason").toString());
            me->setMeasures(rec.value("measures").toString());
            me->setOperatorid(rec.value("operatorid").toString());
            me->setStatus(rec.value("status").toString());
            me->setDirection(rec.value("direction").toString());

            me->setMdate(rec.value("mdate").toDateTime());

            result.append(me);
        }
    }

    return result;
}

QList<JourEntity *> DataBaseManager::getMSGRecord(const int &id) //const
{
    QList<JourEntity *> result;
    QString sql;
    sql = "SELECT * FROM jour ";
    if(id > 0)
        sql += " WHERE id = :id ";
    sql += " ORDER BY id ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":id", id);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            JourEntity * me = new JourEntity;
            me->setId(rec.value("id").toInt());
            me->setCdate(rec.value("cdate").toDateTime());

            me->setComment(rec.value("comment").toString());
            me->setObject(rec.value("object").toString());
            me->setReason(rec.value("reason").toString());
            me->setMeasures(rec.value("measures").toString());
            me->setOperatorid(rec.value("operatorid").toString());
            me->setStatus(rec.value("status").toString());
            me->setDirection(rec.value("direction").toString());

            me->setMdate(rec.value("mdate").toDateTime());

            result.append(me);
        }
    }

    return result;
}

QList<QString> DataBaseManager::getReasonGroup() {
    QList<QString> result;

    QString sql;
    sql = " SELECT reason \
            FROM public.jour \
            WHERE reason is not null \
            group by reason, mdate \
            order by mdate DESC, reason ASC ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            result.append(rec.value("reason").toString());
        }
    }
    return result;
}

QList<QString> DataBaseManager::getMeasuresGroup() {
    QList<QString> result;

    QString sql;
    sql = " SELECT measures \
            FROM public.jour \
            WHERE measures is not null \
            group by measures, mdate \
            order by mdate DESC, measures ASC ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            result.append(rec.value("reason").toString());
        }
    }
    return result;
}

void DataBaseManager::loadSettings(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginGroup("PostgresSQL");

    HostName = settings.value( "HostName", -1 ).toString();//("127.0.0.1");
    HostName = Utils::strHostAddress(HostName);
    DatabaseName = settings.value( "DatabaseName", -1 ).toString();//("postgres");
    UserName = settings.value( "UserName", -1 ).toString();//("postgres");
    Password = settings.value( "Password", -1 ).toString();//("601275");
    Port = settings.value( "Port", -1 ).toString();//(5432);
    qDebug() << HostName << " " << DatabaseName << " " << UserName << " " << Password << " " << Port;

    settings.endGroup();
}
