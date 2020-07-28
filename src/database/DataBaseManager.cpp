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
    sql += "comment, object, reason, measures, operatorid, status, direction, d1, d2, d3, d4, type, objecttype, flag) VALUES ( ";
    if(msg.getCdate().isValid())
        sql += "to_timestamp(:vCdate, 'YYYY-MM-DD HH24:MI:SS.MS'), ";
    if(msg.getMdate().isValid())
        sql += "to_timestamp(:vMdate, 'YYYY-MM-DD HH24:MI:SS.MS'), ";
    sql += ":vComment, :vObject, :vReason, :vMeasures, :vOperatorid, :vStatus, :vDirection, :vD1, :vD2, :vD3, :vD4, :vType, :vObjecttype, :vFlag); ";

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
    query.bindValue(":vD1", msg.getD1());
    query.bindValue(":vD2", msg.getD2());
    query.bindValue(":vD3", msg.getD3());
    query.bindValue(":vD4", msg.getD4());
    query.bindValue(":vType", msg.getType());
    query.bindValue(":vObjecttype", msg.getObjecttype());
    query.bindValue(":vFlag", 1);
//    query.bindValue(":vFlag", msg.getFlag());

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
             direction=:vDirection, \
             d1=:vD1, \
             d2=:vD2, \
             d3=:vD3, \
             d4=:vD4, \
             type=:vType, \
             objecttype=:vObjecttype, \
             flag=:vFlag \
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
    query.bindValue(":vD1", msg.getD1());
    query.bindValue(":vD2", msg.getD2());
    query.bindValue(":vD3", msg.getD3());
    query.bindValue(":vD4", msg.getD4());
    query.bindValue(":vType", msg.getType());
    query.bindValue(":vObjecttype", msg.getObjecttype());
    query.bindValue(":vFlag", msg.getFlag());
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

void DataBaseManager::resetAllFlags_wS()
{
    resetAllFlags();
    SignalSlotCommutator::getInstance()->emitUpdAllJourMSG();
}

void DataBaseManager::resetAllFlags()
{
    QString sql;
    sql =  " UPDATE public.jour \
             SET flag = 0 \
             WHERE flag != 0 ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
        qDebug() << "DataBaseManager::resetAllFlags ";
        return;
    }
    else
    {
        qDebug() << "DataBaseManager::resetAllFlags Error :" << query.lastError().text();
        qDebug() << query.lastQuery();
        qDebug() << query.boundValues();
        return;
    }
}

QList<JourEntity *> DataBaseManager::getQueryMSGRecord(QString sql) {
    QList<JourEntity *> result;
    QSqlQuery query(m_db());
    query.prepare(sql);
    result = DataBaseManager::getQueryMSGRecord(query);
    return result;
}

QList<JourEntity *> DataBaseManager::getQueryMSGRecord(QSqlQuery query) {
    QList<JourEntity *> result;

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

            me->setObjectid(rec.value("objectid").toInt());

            me->setD1(rec.value("d1").toInt());
            me->setD2(rec.value("d2").toInt());
            me->setD3(rec.value("d3").toInt());
            me->setD4(rec.value("d4").toInt());
            me->setType(rec.value("type").toInt());
            me->setObjecttype(rec.value("objecttype").toInt());
            me->setFlag(rec.value("flag").toInt());

            result.append(me);
        }
    }

    return result;
}

int DataBaseManager::executeQuery(QString sql)
{
    int result;
    QSqlQuery query(m_db());
    query.prepare(sql);
    result = DataBaseManager::executeQuery(query);
    return result;
}

int DataBaseManager::executeQuery(QSqlQuery query)
{
    if(query.exec()) {
        return 0;
    } else {
        qDebug() << query.lastError().text();
    }

    return -1;
}

QList<JourEntity *> DataBaseManager::getMSGRecordAfter(const int &id) /*const*/ {
    return getFltMSGRecordAfter("", id);
}

QList<JourEntity *> DataBaseManager::getMSGRecord(const int &id) //const
{
    return getFltMSGRecord("", id);
}

QList<JourEntity *> DataBaseManager::getFltMSGRecordAfter(const QString flt, const int &id) {
    QList<JourEntity *> result;
    QString sql;
    sql = "SELECT * FROM jour ";
    if(id > 0 || !flt.isEmpty()) {
        sql += " WHERE ";
        if(id > 0)
            sql += " id > :id ";
        if(!flt.isEmpty()) {
            if(id > 0)
                sql += " AND ";
            sql += " ( " + flt + " ) ";
        }
    }
    sql += " ORDER BY id ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":id", id);

    return DataBaseManager::getQueryMSGRecord(query);
}



QList<JourEntity *> DataBaseManager::getFltMSGRecord(const QString flt, const int &id) {
    QList<JourEntity *> result;
    QString sql;
    sql = "SELECT * FROM jour ";
    if(id > 0 || !flt.isEmpty()) {
        sql += " WHERE ";
        if(id > 0)
            sql += " id = :id ";
        if(!flt.isEmpty()) {
            if(id > 0)
                sql += " AND ";
            sql += " ( " + flt + " ) ";
        }
    }
    sql += " ORDER BY id ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":id", id);

    return DataBaseManager::getQueryMSGRecord(query);
}

QList<QString> DataBaseManager::getReasonGroup() {
    QList<QString> result;

    QString sql;
    sql = " SELECT reason \
            FROM public.jour \
            WHERE reason is not null and reason != '' \
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
            WHERE measures is not null and measures != '' \
            group by measures, mdate \
            order by mdate DESC, measures ASC ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            result.append(rec.value("measures").toString());
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


QString DataBaseManager::eventFlt(JourEntity::TypeEvent eType, JourEntity::TypeObject oType) {
    QString sqlFlt;

    switch( (JourEntity::TypeEvent)eType ) {
//    case JourEntity::eAllEvent: {
//        break;
//    }
    case JourEntity::eAlarm: {
        sqlFlt += "(type >= 20 AND type < 30)";
        break;
    }
    case JourEntity::eAlarmWorked: {
        sqlFlt += "type=20";
        break;
    }
    case JourEntity::eAlarmOpening: {
        sqlFlt += "(type=21 OR type=25)";
        break;
    }
    case JourEntity::eFault: {
        if(JourEntity::oIU == (JourEntity::TypeObject)oType)
            sqlFlt += "(type=10 OR type=11 OR type=200)";
        else
            sqlFlt += "((type >= 10 AND type < 20) OR type=200)";
        break;
    }
    case JourEntity::eFaultNoConnect: {
        sqlFlt += "(type=10 OR type=200)";
        break;
    }
    case JourEntity::eFaultDK: {
        sqlFlt += "(type=11 OR type=133 OR type=1002 OR type=3)";
        break;
    }
    case JourEntity::eFaultCommand: {
        sqlFlt += "type=13";
        break;
    }
    case JourEntity::eCommand: {
        if(JourEntity::oSD == (JourEntity::TypeObject)oType)
            sqlFlt += "((type >= 2 AND type < 5) OR type=15 OR type=30 OR type=31\
                                       OR (type >= 100 AND type < 200) OR type >= 900)";
        else if(JourEntity::oIU == (JourEntity::TypeObject)oType)
            sqlFlt += "type=13 OR type=100 OR type=111\
                                               OR type=112 OR type=113 OR type=130\
                                               OR type=131 OR type=140 OR type=141\
                                               OR type=1000 OR type=1001";
        else
            sqlFlt += "((type >= 2 AND type < 5) OR type=15 OR type=30 OR type=31\
                                               OR (type >= 100 AND type < 200) OR type >= 900)";
        break;
    }
    case JourEntity::eCommandDK: {
        sqlFlt += "(type=11 OR type=133 OR type=1002 OR type=3)";
        break;
    }
    case JourEntity::eCommandUZMonolit: {
        sqlFlt += "((type >= 110 AND type < 114) OR type=150 OR type=151 OR type=1003 OR type=1004 OR type=13)";
        break;
    }
    case JourEntity::eCommandOperator: {
        sqlFlt += "(type >= 900 OR type=135 OR type=136 OR type=137)";
        break;
    }
    default:
        break;
    }

    if(!sqlFlt.isEmpty())
        sqlFlt = "(" + sqlFlt + ")";
    return sqlFlt;
}

QString DataBaseManager::connectObjectFlt(JourEntity::TypeConnectObject coType) {
    QString sqlFlt;

    switch( (JourEntity::TypeConnectObject)coType ) {
    case JourEntity::coAllConnectObject: {
        break;
    }
    case JourEntity::coRIFRLM: {
        break;
    }
    case JourEntity::coRIFKRL: {
        break;
    }
    case JourEntity::coRIFKRLM: {
        break;
    }
    case JourEntity::coRIFRLMS: {
        break;
    }
    case JourEntity::coTrassa: {
        break;
    }
    case JourEntity::coTochkaGard: {
        break;
    }
    case JourEntity::coRazryad: {
        break;
    }
    default: {
        sqlFlt += " (out_dev_type =" + QString::number(coType) +")";
        break;
    }
    }

    if(!sqlFlt.isEmpty())
        sqlFlt = "(" + sqlFlt + ")";
    return sqlFlt;

}


QString DataBaseManager::objectFlt(JourEntity::TypeObject oType, int d1, int d2, int d3) {
    QString sqlFlt;

    switch( (JourEntity::TypeObject)oType ) {
//    case JourEntity::oAllObject: {
//        break;
//    }
    case JourEntity::oSD: {
        sqlFlt += " (objecttype=3 OR objecttype=33)";  /* СД */
        if(0 != d1)
            sqlFlt += " AND d1=" + QString::number(d1);
        if(0 != d2)
            sqlFlt += " AND d2=" + QString::number(d2);
        if(0 != d3)
            sqlFlt += " AND d3=" + QString::number(d3);
        break;
    }
    case JourEntity::oIU: {
        sqlFlt += " (objecttype=4 OR objecttype=43)";  /* ИУ */
        if(0 != d1)
            sqlFlt += " AND d1=" + QString::number(d1);
        if(0 != d2)
            sqlFlt += " AND d2=" + QString::number(d2);
        if(0 != d3)
            sqlFlt += " AND d3=" + QString::number(d3);
        break;
    }
    case JourEntity::oRIFRLM: {
        sqlFlt += "objecttype=1";
        break;
    }
    case JourEntity::oSDCollector: {
        sqlFlt += "objecttype=2";
        break;
    }
    case JourEntity::oToros: {
        sqlFlt += "objecttype=8";
        break;
    }
    case JourEntity::oNast: {
        sqlFlt += "objecttype=9";
        break;
    }
    case JourEntity::oRadar: {
        sqlFlt += "objecttype=91";
        break;
    }
    case JourEntity::oRazrivBO: {
        sqlFlt += "objecttype=21";
        break;
    }
    case JourEntity::oTochkaGard: {
        sqlFlt += "objecttype=10";
        break;
    }
    case JourEntity::oAdam: {
        sqlFlt += "objecttype=7";
        break;
    }
    case JourEntity::oSDBLIP: {
        sqlFlt += "objecttype=11";
        break;
    }
    case JourEntity::oIUBLIP: {
        sqlFlt += "objecttype=12";
        break;
    }
//            case 13: sqlFlt += " AND objecttype=14"; break;
//            case 14: sqlFlt += " AND objecttype=17"; break;
    case JourEntity::oRIFRLMS: {
        sqlFlt += "objecttype=111";
        break;
    }
    case JourEntity::oBODTochkaM: {
        sqlFlt += "objecttype=26";
        break;
    }
    case JourEntity::oDDTochkaM: {
        sqlFlt += "objecttype=28";
        break;
    }
    case JourEntity::oBODSota: {
        sqlFlt += "objecttype=29";
        break;
    }
    case JourEntity::oDDSota: {
        sqlFlt += "objecttype=31";
        break;
    }
    default:
        break;
    }
    if(!sqlFlt.isEmpty())
        sqlFlt = "(" + sqlFlt + ")";
    return sqlFlt;
}

QString DataBaseManager::dateFlt(QDate from, QDate to) {
    QString sqlFlt = "cdate >= to_timestamp('" + from.toString("yyyy-MM-dd 00:00:00.00") + "', 'YYYY-MM-DD HH24:MI:SS.MS') AND cdate <= to_timestamp('" + to.toString("yyyy-MM-dd 23:59:59.99") + "', 'YYYY-MM-DD HH24:MI:SS.MS')";
    if(!sqlFlt.isEmpty())
        sqlFlt = "(" + sqlFlt + ")";
    return sqlFlt;
}
