#include "DataBaseManager.h"
#include "SignalSlotCommutator.h"
#include "Utils.h"
#include "Operator.h"
#include <IniFileService.h>
#include <QTextCodec>
#include "SimpleIni.h"
#include "ServerSettingUtils.h"

qint64 DataBaseManager::idStartLastDuty = -1;

QSqlDatabase DataBaseManager::db = QSqlDatabase();

QSharedPointer<ShedulerNewDuty> DataBaseManager::shedulerNewDuty;

QStringList DataBaseManager::fields = {
//    "id",
    "cdate",
    "mdate",
    "objectid",
    "object",
    "comment",
    "reason",
    "measures",
    "operator",
    "operatorid",
    "status",
    "direction",
    "type",
    "flag",
    "d1",
    "d2",
    "d3",
    "d4",
    "objecttype",
    "params"
};

uint constexpr qConstHash(const char *string)
{
    uint h = 0;

    while (*string != 0)
    {
        h = (h << 4) + *string++;
        h ^= (h & 0xf0000000) >> 23;
        h &= 0x0fffffff;
    }
    return h;
}

QMetaType::Type DataBaseManager::fieldType(QString field) {

    switch (qHash(field)) {
    case qConstHash("id") :
    case qConstHash("objectid") :
    case qConstHash("type") :
    case qConstHash("flag") :
    case qConstHash("d1") :
    case qConstHash("d2") :
    case qConstHash("d3") :
    case qConstHash("d4") :
    case qConstHash("objecttype") : {
        return QMetaType::Int;
    }
    case qConstHash("object") :
    case qConstHash("comment") :
    case qConstHash("reason") :
    case qConstHash("measures") :
    case qConstHash("operator") :
    case qConstHash("operatorid") :
    case qConstHash("status") :
    case qConstHash("direction") : {
        return QMetaType::QString;
    }
    case qConstHash("cdate") :
    case qConstHash("mdate") : {
        return QMetaType::QDateTime;
    }
    case qConstHash("params") : {
        return QMetaType::QJsonDocument;
    }
    default : {
        return QMetaType::UnknownType;
    }
    }
    return QMetaType::UnknownType;

}

QString DataBaseManager::HostName = QString();
QString DataBaseManager::DatabaseName = QString();
QString DataBaseManager::UserName = QString();
QString DataBaseManager::Password = QString();
QString DataBaseManager::Port = QString();
bool DataBaseManager::active;
QString DataBaseManager::BackupPath = QString();

qint64 DataBaseManager::getIdStartLastDuty()
{
    return idStartLastDuty;
}

void DataBaseManager::setIdStartLastDuty(qint64 value)
{
    idStartLastDuty = value;
}

void DataBaseManager::setIdStartLastDuty()
{
    QList<JourEntity> newRecords(DataBaseManager::getQueryMSGRecord("SELECT j1.* FROM public.jour j1 WHERE j1.id in (SELECT max(j2.id) FROM public.jour j2 WHERE j2.type = 902)"));

    if(newRecords.isEmpty())
        setIdStartLastDuty(-1);
    else
        setIdStartLastDuty(newRecords.first().getId());
}

QString DataBaseManager::getHostName()
{
    return HostName;
}

void DataBaseManager::setHostName(const QString &value)
{
    HostName = value;
}

QString DataBaseManager::getDatabaseName()
{
    return DatabaseName;
}

void DataBaseManager::setDatabaseName(const QString &value)
{
    DatabaseName = value;
}

QString DataBaseManager::getUserName()
{
    return UserName;
}

void DataBaseManager::setUserName(const QString &value)
{
    UserName = value;
}

QString DataBaseManager::getPassword()
{
    return Password;
}

void DataBaseManager::setPassword(const QString &value)
{
    Password = value;
}

QString DataBaseManager::getPort()
{
    return Port;
}

void DataBaseManager::setPort(const QString &value)
{
    Port = value;
}


DataBaseManager::DataBaseManager(QObject *parent) noexcept :
    QObject(parent)
{
//    qDebug() << "DataBaseManager::DataBaseManager()";
    if(m_db().isValid() || m_db().isOpen())
    {
        m_db().close();
    }

//    loadSettings();
    m_db();
}

QSqlDatabase& DataBaseManager::m_db()
{
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QPSQL");

        if(getHostName().isEmpty() || getDatabaseName().isEmpty() || getUserName().isEmpty() || getPassword().isEmpty() || getPort().isEmpty()) {
            QString hostName;
            QString databaseName;
            QString userName;
            QString password;
            QString port;
            bool active;
            QString BackupPath;


            CSimpleIniA ini;
            QString filePath = QCoreApplication::applicationDirPath() + "/rifx.ini";
            ini.LoadFile(filePath.toStdString().c_str());

            QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

            hostName = codec->toUnicode(ini.GetValue("PostgresSQL", "Host"));
            databaseName = codec->toUnicode(ini.GetValue("PostgresSQL", "DbName"));


            userName = codec->toUnicode(ini.GetValue("PostgresSQL", "Login"));
            port = codec->toUnicode(ini.GetValue("PostgresSQL", "Port"));

            QString value=codec->toUnicode(ini.GetValue("PostgresSQL", "Use"));
            if(value=="1")
                active=true;
            else
                active=false;

            BackupPath=codec->toUnicode(ini.GetValue("BACKUP", "BackupPath"));


            const char * criptPasswordChar = ini.GetValue("PostgresSQL", "Password");
            QString criptPassword = QString::fromLatin1(criptPasswordChar);
            qDebug() << "Crypt -- " << criptPassword;
            QString key = "start7";
            QString decriptPassword = Utils::xorCrypt(criptPassword, key);
            decriptPassword = codec->toUnicode(decriptPassword.toStdString().c_str());
            qDebug() << "DeCrypt -- " << decriptPassword;
            password = decriptPassword;

//            qDebug()<<"==SQL===";
//            qDebug()<<hostName;
//            qDebug()<<databaseName;
//            qDebug()<<userName;
//            qDebug()<<password;
//            qDebug()<<port;
//            qDebug()<<"========";

            setHostName(hostName);
            setDatabaseName(databaseName);
            setUserName(userName);
            setPassword(password);
            setPort(port);
            setActive(active);
            setBackupPath(BackupPath);
            //qDebug() << "DataBaseManager::m_db(first -> " <<getHostName() << " " << getDatabaseName() << " " << getUserName() << " " << getPassword() << " " << getPort() << ")";

            auto autoNewDuty = codec->toUnicode(ini.GetValue("PostgresSQL", "AutoDbStart"));
            auto hour = codec->toUnicode(ini.GetValue("PostgresSQL", "AutoDbStartHour"));
            auto minute = codec->toUnicode(ini.GetValue("PostgresSQL", "AutoDbStartMinute"));

            if(1 == autoNewDuty.toInt()) {
                shedulerNewDuty = QSharedPointer<ShedulerNewDuty>::create(QTime(hour.toInt(), minute.toInt()));
                shedulerNewDuty->start();
            }
        }

        db.setHostName(getHostName());
        db.setDatabaseName(getDatabaseName());
        db.setUserName(getUserName());
        db.setPassword(getPassword());
        db.setPort(getPort().toUInt());
        db.open(getUserName(), getPassword());


        if (!db.isOpen())
        {
            qDebug() << "Cannot open database: Error: " << db.lastError();
        }
        else
        {
            QSqlDriver* driver  = db.driver();
            qDebug() << "QSqlDriver::Transactions " << driver->hasFeature( QSqlDriver::Transactions ) ;
            //qDebug()<<"Opened database: " << db.connectOptions();
        }
    } else if (db.isOpen()) {
        return db;
    } else if(db.open(getUserName(), getPassword())) {
        return db;
        //qDebug()<<"Opened database: " << db.connectOptions();
    } else {
        qDebug() << "Cannot open database: Error: " << db.lastError();
    }

    return db;
}

void DataBaseManager::makeBackup()
{


    qDebug()<<"BackupPath  : "<<DataBaseManager::BackupPath;
    qDebug()<<"DatabaseName: "<<DataBaseManager::DatabaseName;
    qDebug()<<"HostName    : "<<DataBaseManager::HostName;
    qDebug()<<"Password    : "<<DataBaseManager::Password;
    qDebug()<<"Port        : "<<DataBaseManager::Port;
    qDebug()<<"UserName    : "<<DataBaseManager::UserName;



 //   QString cmd="/usr/bin/pg_dump --host 127.0.0.1 --port 5432 --username postgres --no-password --format custom --blobs --verbose --file backup_2 rif_db0 ";

 QString cmd="/usr/bin/pg_dump --host 127.0.0.1 --port "+DataBaseManager::Port+
             " --username "+ DataBaseManager::UserName+
             " --no-password --format custom --blobs --verbose --file backup "+ DataBaseManager::DatabaseName;
    qDebug()<<cmd;
   QProcess::execute(cmd);


    cmd="zip --password MY_SECRET user.zip rifx.ini backup";
    qDebug()<<cmd;
    QProcess::execute(cmd);

    cmd="cp user.zip "+DataBaseManager::BackupPath;
    qDebug()<<cmd;
    QProcess::execute(cmd);

    cmd="rm backup";
    qDebug()<<cmd;
    QProcess::execute(cmd);

    cmd="rm secure.zip";
    qDebug()<<cmd;
    QProcess::execute(cmd);


}

void DataBaseManager::restoreBackup()
{
    qDebug()<<"BackupPath  : "<<DataBaseManager::BackupPath;
    qDebug()<<"DatabaseName: "<<DataBaseManager::DatabaseName;
    qDebug()<<"HostName    : "<<DataBaseManager::HostName;
    qDebug()<<"Password    : "<<DataBaseManager::Password;
    qDebug()<<"Port        : "<<DataBaseManager::Port;
    qDebug()<<"UserName    : "<<DataBaseManager::UserName;



 //   QString cmd="/usr/bin/pg_restore --host 127.0.0.1 --port 5432 --username "postgres" --dbname "rif_db3" --role "postgres" --no-password  --verbose "/home/administrator/Backup/backup"";

    QString cmd="unzip -P MY_SECRET "+DataBaseManager::BackupPath+"/user.zip -d "+DataBaseManager::BackupPath;
    qDebug()<<cmd;
    QProcess::execute(cmd);




cmd="/usr/bin/pg_restore --host 127.0.0.1 --port "+DataBaseManager::Port+
             " --username "+ DataBaseManager::UserName+
             " --dbname "+DataBaseManager::DatabaseName+
             " --role "+DataBaseManager::UserName+
             "  --no-password  --verbose "+DataBaseManager::BackupPath+"/backup";

  qDebug()<<cmd;
  QProcess::execute(cmd);

  cmd="cp "+DataBaseManager::BackupPath+"/rifx.ini rifx.ini ";
  qDebug()<<cmd;
  QProcess::execute(cmd);

  cmd="rm "+DataBaseManager::BackupPath+"/backup";
  qDebug()<<cmd;
  QProcess::execute(cmd);

  cmd="rm "+DataBaseManager::BackupPath+"/rifx.ini";
  qDebug()<<cmd;
  QProcess::execute(cmd);

}

void DataBaseManager::makeAutoBackup()
{
    QString cmd="/usr/bin/pg_dump --host 127.0.0.1 --port "+DataBaseManager::Port+
                " --username "+ DataBaseManager::UserName+
                " --no-password --format custom --blobs --verbose --file backup "+ DataBaseManager::DatabaseName;
       qDebug()<<cmd;
      QProcess::execute(cmd);


       cmd="zip --password MY_SECRET auto.zip rifx.ini backup";
       qDebug()<<cmd;
       QProcess::execute(cmd);

       cmd="cp auto.zip "+DataBaseManager::BackupPath;
       qDebug()<<cmd;
       QProcess::execute(cmd);

       cmd="rm backup";
       qDebug()<<cmd;
       QProcess::execute(cmd);

       cmd="rm secure.zip";
       qDebug()<<cmd;
       QProcess::execute(cmd);
}

void DataBaseManager::restoreAutoBackup()
{
    QString cmd="unzip -P MY_SECRET "+DataBaseManager::BackupPath+"/auto.zip -d "+DataBaseManager::BackupPath;
    qDebug()<<cmd;
    QProcess::execute(cmd);




cmd="/usr/bin/pg_restore --host 127.0.0.1 --port "+DataBaseManager::Port+
             " --username "+ DataBaseManager::UserName+
             " --dbname "+DataBaseManager::DatabaseName+
             " --role "+DataBaseManager::UserName+
             "  --no-password  --verbose "+DataBaseManager::BackupPath+"/backup";

  qDebug()<<cmd;
  QProcess::execute(cmd);

  cmd="cp "+DataBaseManager::BackupPath+"/rifx.ini rifx.ini ";
  qDebug()<<cmd;
  QProcess::execute(cmd);

  cmd="rm "+DataBaseManager::BackupPath+"/backup";
  qDebug()<<cmd;
  QProcess::execute(cmd);

  cmd="rm "+DataBaseManager::BackupPath+"/rifx.ini";
  qDebug()<<cmd;
  QProcess::execute(cmd);
}

DataBaseManager::~DataBaseManager() noexcept
{
    qDebug() << "DataBaseManager::~DataBaseManager()";
    if(m_db().isOpen())
        m_db().close();
}

int DataBaseManager::insertJourMsg_wS(const JourEntity &msg) {
    int lastInsertId = insertJourMsg(msg);
    if(0 != lastInsertId)
        SignalSlotCommutator::emitInsNewJourMSG(/*lastInsertId*/);
//        emit this->insertNewMSG();
    return lastInsertId;
}


int DataBaseManager::insertJourMsg(const JourEntity &msg)
{
    if(DataBaseManager::getActive()){
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    QString json = codec->toUnicode(msg.getParams().toJson(QJsonDocument::Compact));
//    json = json.replace("\"", "\\\"");
    if(json.isEmpty())
        json = "{}";
    json = "'" + json + "'";


    QString sql;
    sql = " INSERT INTO public.jour ( ";
    if(msg.getCdate().isValid())
        sql += "cdate, ";
    if(msg.getMdate().isValid())
        sql += "mdate, ";
    sql += "comment, object, reason, measures, operatorid, status, direction, d1, d2, d3, d4, type, objecttype, flag, params) VALUES ( ";
    if(msg.getCdate().isValid())
        sql += "to_timestamp(:vCdate, 'YYYY-MM-DD HH24:MI:SS.MS'), ";
    if(msg.getMdate().isValid())
        sql += "to_timestamp(:vMdate, 'YYYY-MM-DD HH24:MI:SS.MS'), ";
    sql += ":vComment, :vObject, :vReason, :vMeasures, :vOperatorid, :vStatus, :vDirection, :vD1, :vD2, :vD3, :vD4, :vType, :vObjecttype, :vFlag, " + json + " ); ";

    m_db().transaction();
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
//    query.bindValue(":vOperatorid", msg.getOperatorid());
    query.bindValue(":vOperatorid", Operator::getApprovedOperator().getOperatorLableText());
    query.bindValue(":vStatus", msg.getStatus());
    query.bindValue(":vDirection", msg.getDirection());
    query.bindValue(":vD1", msg.getD1());
    query.bindValue(":vD2", msg.getD2());
    query.bindValue(":vD3", msg.getD3());
    query.bindValue(":vD4", msg.getD4());
    query.bindValue(":vType", msg.getType());
    query.bindValue(":vObjecttype", msg.getObjecttype());
//    query.bindValue(":vFlag", 1);
    query.bindValue(":vFlag", msg.getFlag());



    if(query.exec())
    {
        m_db().commit();
//        //qDebug() << "DataBaseManager::addNewMsg :" << query.lastInsertId().toUInt();
        return query.lastInsertId().toUInt();
    }
    else
    {
        qDebug() << "DataBaseManager::addNewMsg Error :" << query.lastError().text();
        qDebug() << query.lastQuery();
        qDebug() << query.boundValues();
        m_db().rollback();
        return 0;
    }

    m_db().rollback();

    return 0;
     }else{

         return 0;
     }

}

int DataBaseManager::updateJourMsg_wS(JourEntity &msg) {
    int lastUpdateId = updateJourMsg(msg);

    if(0 != lastUpdateId)
        SignalSlotCommutator::emitUpdJourMSG(lastUpdateId);
//        emit this->updateMSG(lastUpdateId);
    return lastUpdateId;
}

int DataBaseManager::updateJourMsg(JourEntity &msg)
{
//    int needReason = IniFileService::getValueBySectionKey("P1", "PostgresSQL").toInt();
//    int needMeasure = IniFileService::getValueBySectionKey("P2", "PostgresSQL").toInt();

//    if(1 == msg.getFlag()) {
//        if(0 != needReason && 0 != needMeasure && !msg.getReason().isEmpty() && !msg.getMeasures().isEmpty()) {
//            msg.setFlag(0);
//        } else if(0 != needReason && 0 == needMeasure && !msg.getReason().isEmpty()) {
//            msg.setFlag(0);
//        } else if(0 == needReason && 0 != needMeasure && !msg.getMeasures().isEmpty()) {
//            msg.setFlag(0);
//        } else if(0 == needReason && 0 == needMeasure && (!msg.getReason().isEmpty() || !msg.getMeasures().isEmpty())) {
//            msg.setFlag(0);
//        }
//    }

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


    m_db().transaction();
    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":vComment", msg.getComment());
    query.bindValue(":vObject", msg.getObject());
    query.bindValue(":vReason", msg.getReason());
    query.bindValue(":vMeasures", msg.getMeasures());
    query.bindValue(":vOperatorid", msg.getOperatorid());
//    query.bindValue(":vOperatorid", Operator::getApprovedOperator().getOperatorLable());
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
//        //qDebug() << "DataBaseManager::updMsg :" << msg.getId();
//        emit this->updateMSG(msg.getId());
        m_db().commit();
        return msg.getId();
    }
    else
    {
        qDebug() << "DataBaseManager::updMsg Error :" << query.lastError().text();
        qDebug() << query.lastQuery();
        qDebug() << query.boundValues();
        m_db().rollback();
        return 0;
    }
    m_db().rollback();
    return 0;
}

int DataBaseManager::updateJourMsgFieldById(const QString field, const QVariant value, const QSet<int> setId)
{
    if(!fields.contains(field) || value.isNull() || setId.isEmpty())
        return 0;

    QString sql;

    switch(fieldType(field)) {
    case QMetaType::QDateTime: {
        sql =  " UPDATE public.jour \
                 SET %1=to_timestamp(:value, 'YYYY-MM-DD HH24:MI:SS.MS'), \
                     mdate = to_timestamp(:vMdate, 'YYYY-MM-DD HH24:MI:SS.MS') \
                 WHERE id in %2";

        break;
    }
    case QMetaType::QJsonDocument: {
        break;
        sql =  " UPDATE public.jour \
                 SET %1=to_timestamp(:value, 'YYYY-MM-DD HH24:MI:SS.MS'), \
                     mdate = to_timestamp(:vMdate, 'YYYY-MM-DD HH24:MI:SS.MS') \
                 WHERE id in %2";

        break;
    }
    default : {
        sql =  " UPDATE public.jour \
                 SET %1=:value, \
                     mdate = to_timestamp(:vMdate, 'YYYY-MM-DD HH24:MI:SS.MS') \
                 WHERE id in %2 ";
        break;
    }
    }


    QString sqlId;
    const QList<int> listId = setId.values();
    sqlId.append(":vId0");
    for(int i = 1, n = listId.size(); i < n; i++) {
        sqlId.append(", :vId" + QString::number(i));
    }
    sqlId = "(" + sqlId + ")";


    sql = sql.arg(field, sqlId);

    m_db().transaction();
    QSqlQuery query(m_db());
    query.prepare(sql);

    switch(fieldType(field)) {
    case QMetaType::QDateTime: {
        query.bindValue(":value", value.toDateTime().toString("yyyy-MM-dd hh:mm:ss.z"));
        break;
    }
    default : {
        query.bindValue(":value", value);
        break;
    }
    }

    query.bindValue(":vMdate", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.z"));

    for(int i = 0, n = listId.size(); i < n; i++) {
        query.bindValue(":vId" + QString::number(i), listId.at(i));
    }

    if(query.exec())
    {
//        //qDebug() << "DataBaseManager::updateJourMsgFieldById ";
        m_db().commit();
        return listId.size();
    }

    qDebug() << "DataBaseManager::updateJourMsgFieldById Error :" << query.lastError().text();
    qDebug() << query.lastQuery();
    qDebug() << query.boundValues();
    m_db().rollback();
    return 0;
}

int DataBaseManager::checkNecessarilyReasonMeasureFill() {
    int needReason = IniFileService::getValueBySectionKey("PostgresSQL", "P1", "0").toInt();
    int needMeasure = IniFileService::getValueBySectionKey("PostgresSQL", "P2", "0").toInt();

    if(0 == needReason && 0 == needMeasure)
        return 0;

    QString sql;
    sql = "SELECT COUNT(*) as COUNTNECESSARILY FROM public.jour  WHERE ";

    QString flt;
    if(-1 != DataBaseManager::getIdStartLastDuty()) {
        flt += " id >= :vIdMin ";
    }

    const QList<int> listType = ServerSettingUtils::getPriorityJoutTyper().values();
    if(!listType.isEmpty()) {
        QString sqlType;
        sqlType.append(":vType0");
        for(int i = 1, n = listType.size(); i < n; i++) {
            sqlType.append(", :vType" + QString::number(i));
        }
        sqlType = "type in (" + sqlType + ")";

        flt += QString(flt.isEmpty() ? "" : " AND ") + sqlType;
    }

    QString sqlReasonMeasure;
    if(0 != needReason) {
        QString sqlReason("(reason is null OR reason = '')");
        sqlReasonMeasure += sqlReason;
    }

    if(0 != needMeasure) {
        QString sqlMeasure("(measures is null OR measures = '')");
        sqlReasonMeasure += (sqlReasonMeasure.isEmpty() ? "" : " OR ") + sqlMeasure;
    }

    if(!sqlReasonMeasure.isEmpty())
        flt += QString(flt.isEmpty() ? "" : " AND ") + QString("(") + sqlReasonMeasure + QString(")");
    \
    if(flt.isEmpty())
        return 0;

    sql += flt;

    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":vIdMin", DataBaseManager::getIdStartLastDuty());
    if(!listType.isEmpty()) {
        for(int i = 0, n = listType.size(); i < n; i++) {
            query.bindValue(":vType" + QString::number(i), listType.at(i));
        }
    }

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
//            qDebug() << "DataBaseManager::checkNecessarilyReasonMeasureFill";
            return rec.value("COUNTNECESSARILY").toInt();
        }
    }

    qDebug() << "DataBaseManager::checkNecessarilyReasonMeasureFill Error :" << query.lastError().text();
    qDebug() << query.lastQuery();
    qDebug() << query.boundValues();
    return 0;
}

bool DataBaseManager::getActive()
{
    return active;
}

void DataBaseManager::setActive(bool value)
{
    active = value;
}

const QString &DataBaseManager::getBackupPath()
{
    return BackupPath;
}

void DataBaseManager::setBackupPath(const QString &newBackupPath)
{
    BackupPath = newBackupPath;
}




void DataBaseManager::resetAllFlags_wS()
{
    resetAllFlags();
    SignalSlotCommutator::emitUpdAllJourMSG();
}

void DataBaseManager::resetAllFlags()
{
    QString sql;
    sql =  " UPDATE public.jour \
             SET flag = 0 \
             WHERE flag != 0 ";

    m_db().transaction();
    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
//        //qDebug() << "DataBaseManager::resetAllFlags ";
        m_db().commit();
        return;
    }
    else
    {
        qDebug() << "DataBaseManager::resetAllFlags Error :" << query.lastError().text();
        qDebug() << query.lastQuery();
        qDebug() << query.boundValues();
        m_db().rollback();
        return;
    }
}

QList<JourEntity> DataBaseManager::getQueryMSGRecord(QString sql) {
    QList<JourEntity> result;
    QSqlQuery query(m_db());
    query.prepare(sql);
    result = DataBaseManager::getQueryMSGRecord(query);
    return result;
}

QList<JourEntity> DataBaseManager::getQueryMSGRecord(QSqlQuery query) {
    QList<JourEntity> result;

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            JourEntity me;
            me.setId(rec.value("id").toInt());
            me.setCdate(rec.value("cdate").toDateTime());

            me.setComment(rec.value("comment").toString());
            me.setObject(rec.value("object").toString());
            me.setReason(rec.value("reason").toString());
            me.setMeasures(rec.value("measures").toString());
            me.setOperatorid(rec.value("operatorid").toString());
            me.setStatus(rec.value("status").toString());
            me.setDirection(rec.value("direction").toString());

            me.setMdate(rec.value("mdate").toDateTime());

            me.setObjectid(rec.value("objectid").toInt());

            me.setD1(rec.value("d1").toInt());
            me.setD2(rec.value("d2").toInt());
            me.setD3(rec.value("d3").toInt());
            me.setD4(rec.value("d4").toInt());
            me.setType(rec.value("type").toInt());
            me.setObjecttype(rec.value("objecttype").toInt());
            me.setFlag(rec.value("flag").toInt());
            me.setParams(QJsonDocument::fromJson(rec.value("params").toByteArray()));

            result.append(me);
        }
    }

//    qDebug() << "DataBaseManager::getQueryMSGRecord(" << query.lastQuery() << ")";
    return result;
}

QList<JourEntity> DataBaseManager::getJourRecordAfter(const int &id, const int &limit)
{
    QList<JourEntity> result;
    QString sql;
    sql = "SELECT * FROM public.jour ";
    QString sqlFlt = "id >= " + QString::number(id);
    if(!sqlFlt.isEmpty())
        sql += " WHERE (" + sqlFlt + ") ORDER BY id ";
    if(-1 != limit)
        sql += " LIMIT " + QString::number(limit);

    QSqlQuery query(m_db());
    query.prepare(sql);

    result = DataBaseManager::getQueryMSGRecord(query);

    return result;
}

QList<JourEntity> DataBaseManager::getJourRecordAfter(const QDateTime &from, const int &limit)
{
    QList<JourEntity> result;
    QString sql;
    sql = "SELECT * FROM public.jour ";
    QString sqlFlt = "cdate >= to_timestamp('" + from.toString("yyyy-MM-dd hh:mm:ss.00") + "', 'YYYY-MM-DD HH24:MI:SS.MS')";
    if(!sqlFlt.isEmpty())
        sql += " WHERE (" + sqlFlt + ") ORDER BY id ";
    if(-1 != limit)
        sql += " LIMIT " + QString::number(limit);

    QSqlQuery query(m_db());
    query.prepare(sql);

    result = DataBaseManager::getQueryMSGRecord(query);

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
        qDebug() << "DataBaseManager::executeQuery(" << query.lastQuery() << ")";
        return 0;
    } else {
        qDebug() << query.lastError().text();
    }

    return -1;
}

QList<JourEntity> DataBaseManager::getMSGRecordAfter(const int &id) /*const*/ {
    return getFltMSGRecordAfter("", id);
}

QList<JourEntity> DataBaseManager::getOneMSGRecord(const int &id) //const
{
    return getFltOneMSGRecord("", id);
}

QList<JourEntity> DataBaseManager::getFltMSGRecordAfter(const QString flt, const int &id) {
    qDebug() << QTime::currentTime() << "DataBaseManager::getFltMSGRecordAfter("<< flt << ", " << id << ") -->";
    QList<JourEntity> result;
    QString sql;
    sql = "SELECT * FROM public.jour ";
    if(id > 0 || !flt.isEmpty()) {
        sql += " WHERE true ";
        if(id > 0)
            sql += " AND id > :id ";
        if(-1 != DataBaseManager::getIdStartLastDuty()) {
            sql += " AND id >= :idMin ";
        }
        if(!flt.isEmpty()) {
            if(id > 0 || -1 != DataBaseManager::getIdStartLastDuty())
                sql += " AND ";
            sql += " AND ( " + flt + " ) ";
        }
    }
    sql += " ORDER BY id ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":id", id);
    if(-1 != DataBaseManager::getIdStartLastDuty()) {
        query.bindValue(":idMin", DataBaseManager::getIdStartLastDuty());
        sql.replace(":idMin", QString::number(DataBaseManager::getIdStartLastDuty()));
    }
    sql.replace(":id", QString::number(id));

    qDebug() << QTime::currentTime() << "DataBaseManager::getFltMSGRecordAfter("<< flt << ", " << id << ") -- sql " << sql;

    result = DataBaseManager::getQueryMSGRecord(query);
//    //qDebug() << "DataBaseManager::getFltMSGRecordAfter(" << flt << ", " << id << ")";
    qDebug() << QTime::currentTime() << "DataBaseManager::getFltMSGRecordAfter("<< flt << ", " << id << ") <--";
    return result;
}



QList<JourEntity> DataBaseManager::getFltOneMSGRecord(const QString flt, const int &id) {
    qDebug() << QTime::currentTime() << "DataBaseManager::getFltOneMSGRecord("<< flt << ", " << id << ") -->";

    QList<JourEntity> result;
    QString sql;
    sql = "SELECT * FROM public.jour ";
    if(id > 0 || !flt.isEmpty() || -1 != DataBaseManager::getIdStartLastDuty()) {
        sql += " WHERE true ";
        if(id > 0)
            sql += " AND id = :id ";
        else if(id < 0) {
            sql += " AND id >= COALESCE((SELECT max(j2.id) FROM public.jour j2 WHERE j2.type in (902,1902)), 0) ";
        }
        sql.replace(":id", QString::number(id));
        if(!flt.isEmpty()) {
            sql += " AND ( " + flt + " ) ";
        }
    }

    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":id", id);
    sql.replace(":id", QString::number(id));

    qDebug() << QTime::currentTime() << "DataBaseManager::getFltOneMSGRecord("<< flt << ", " << id << ") -- sql " << sql;

    result = DataBaseManager::getQueryMSGRecord(query);
//    qDebug() << "DataBaseManager::getFltOneMSGRecord" << query.lastQuery() << id << DataBaseManager::getIdStartLastDuty();
//    //qDebug() << "DataBaseManager::getFltOneMSGRecord(" << flt << ", " << id << ")";
    qDebug() << QTime::currentTime() << "DataBaseManager::getFltOneMSGRecord("<< flt << ", " << id << ") <--";

    return result;
}

QList<QString> DataBaseManager::getReasonGroup() {
    QList<QString> result;

    QString sql;
    sql = " SELECT reason \
            FROM public.jour \
            WHERE reason is not null and reason != '' \
            group by reason \
            order by reason ASC ";

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
//    //qDebug() << "DataBaseManager::getReasonGroup(" << query.lastQuery() << ")";
    return result;
}

QList<QString> DataBaseManager::getMeasuresGroup() {
    QList<QString> result;

    QString sql;
    sql = " SELECT measures \
            FROM public.jour \
            WHERE measures is not null and measures != '' \
            group by measures \
            order by measures ASC ";

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
//    //qDebug() << "DataBaseManager::getMeasuresGroup(" << query.lastQuery() << ")";
    return result;
}

QList<QString> DataBaseManager::getDirectionGroup() {
    QList<QString> result;

    QString sql;
    sql = " SELECT direction \
            FROM public.jour \
            WHERE direction is not null and direction != '' \
            group by direction \
            order by direction ASC ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            result.append(rec.value("direction").toString());
        }
    }
//    //qDebug() << "DataBaseManager::getMeasuresGroup(" << query.lastQuery() << ")";
    return result;
}

QList<QString> DataBaseManager::getD1Group() {
    QList<QString> result;

    QString sql;
    sql = " SELECT d1 \
            FROM public.jour \
            WHERE d1 is not null \
            group by d1 \
            order by d1 ASC ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            result.append(QString::number(rec.value("d1").toInt()));
        }
    }
//    //qDebug() << "DataBaseManager::getD1Group(" << query.lastQuery() << ")";
    return result;
}

QList<QString> DataBaseManager::getD2Group() {
    QList<QString> result;

    QString sql;
    sql = " SELECT d2 \
            FROM public.jour \
            WHERE d2 is not null \
            group by d2 \
            order by d2 ASC ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            result.append(QString::number(rec.value("d2").toInt()));
        }
    }
//    //qDebug() << "DataBaseManager::getD2Group(" << query.lastQuery() << ")";
    return result;
}

QList<QString> DataBaseManager::getD3Group() {
    QList<QString> result;

    QString sql;
    sql = " SELECT d3 \
            FROM public.jour \
            WHERE d3 is not null \
            group by d3 \
            order by d3 ASC ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            result.append(QString::number(rec.value("d3").toInt()));
        }
    }
//    //qDebug() << "DataBaseManager::getD3Group(" << query.lastQuery() << ")";
    return result;
}

QList<QString> DataBaseManager::getD4Group() {
    QList<QString> result;

    QString sql;
    sql = " SELECT d4 \
            FROM public.jour \
            WHERE d4 is not null \
            group by d4 \
            order by d4 ASC ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    if(query.exec())
    {
        while(query.next())
        {
            QSqlRecord rec = query.record();
            result.append(QString::number(rec.value("d4").toInt()));
        }
    }
//    //qDebug() << "DataBaseManager::getD4Group(" << query.lastQuery() << ")";
    return result;
}

void DataBaseManager::loadSettings(QString fileName)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginGroup("PostgresSQL");

    setHostName(settings.value( "Host", "127.0.0.1" ).toString());//("127.0.0.1");
    setHostName(Utils::strHostAddress(getHostName()));
    setDatabaseName(settings.value( "DbName", "rif_db0" ).toString());//("postgres");
    setUserName(settings.value( "Login", "postgres" ).toString());//("postgres");
    setPassword(settings.value( "Password", "" ).toString());//("601275");
    setPort(settings.value( "Port", "5432" ).toString());//(5432);
    //qDebug() << "DataBaseManager::loadSettings(" << fileName << " -> " << getHostName() << " " << getDatabaseName() << " " << getUserName() << " " << getPassword() << " " << getPort() << ")";

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

QString DataBaseManager::directionFlt(QString direction)
{
    if(direction.isEmpty() || "-1" == direction)
        return "";
    QString sqlFlt;
    sqlFlt += " (direction like ('" + direction + "%')) ";
    return sqlFlt;
}

QString DataBaseManager::num1Flt(const QString &num1)
{
    if(num1.isEmpty() || "-1" == num1)
        return "";
    QString sqlFlt(" (d1=" + num1 + ") ");
    return sqlFlt;
}

QString DataBaseManager::num2Flt(const QString &num2)
{
    if(num2.isEmpty() || "-1" == num2)
        return "";
    QString sqlFlt(" (d2=" + num2 + ") ");
    return sqlFlt;
}

QString DataBaseManager::num3Flt(const QString &num3)
{
    if(num3.isEmpty() || "-1" == num3)
        return "";
    QString sqlFlt(" (d3=" + num3 + ") ");
    return sqlFlt;
}

QString DataBaseManager::outFlt(const int &out)
{
    if(0 > out)
        return "";
    QString sqlFlt(" (d4=" + QString::number(out) + ") ");
    return sqlFlt;
}

QString DataBaseManager::adamOff(const int &adamOff)
{
    if(0 > adamOff)
        return "";
    QString sqlFlt("(params ->> 'AdamOff' = 1)::integer = " + QString::number(adamOff) + ") ");
    return sqlFlt;
}

QString DataBaseManager::objectFlt(JourEntity::TypeObject oType/*, int d1, int d2, int d3*/) {
    QString sqlFlt;

    switch( (JourEntity::TypeObject)oType ) {
    //    case JourEntity::oAllObject: {
//        break;
//    }
    case JourEntity::oSD: {
        sqlFlt += " (objecttype=3 OR objecttype=33)";  /* СД */
        break;
    }
    case JourEntity::oIU: {
        sqlFlt += " (objecttype=4 OR objecttype=43)";  /* ИУ */
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
        sqlFlt += " (1=1)";
        break;
    }

//    if(0 < d1)
//        sqlFlt += " AND d1=" + QString::number(d1);
//    if(0 < d2)
//        sqlFlt += " AND d2=" + QString::number(d2);
//    if(0 < d3)
//        sqlFlt += " AND d3=" + QString::number(d3);

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
