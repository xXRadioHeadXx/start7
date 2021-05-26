#include <DataBaseManager.h>
#include <SignalSlotCommutator.h>
#include <Utils.h>
#include <Operator.h>
#include <QTextCodec>
#include <SimpleIni.h>
#include <ServerSettingUtils.h>

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
    "objecttype"};

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

            CSimpleIniA ini;
            QString filePath = QCoreApplication::applicationDirPath() + "/rifx.ini";
            ini.LoadFile(filePath.toStdString().c_str());

            QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

            hostName = codec->toUnicode(ini.GetValue("PostgresSQL", "Host"));
            databaseName = codec->toUnicode(ini.GetValue("PostgresSQL", "DbName"));
            userName = codec->toUnicode(ini.GetValue("PostgresSQL", "Login"));
            port = codec->toUnicode(ini.GetValue("PostgresSQL", "Port"));

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
            //qDebug()<<"Opened database: " << db.connectOptions();
        }
    } else if(db.open(getUserName(), getPassword())) {
        return db;
        //qDebug()<<"Opened database: " << db.connectOptions();
    } else {
        qDebug() << "Cannot open database: Error: " << db.lastError();
    }

    return db;
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
//        //qDebug() << "DataBaseManager::addNewMsg :" << query.lastInsertId().toUInt();
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

int DataBaseManager::updateJourMsg_wS(JourEntity &msg) {
    int lastUpdateId = updateJourMsg(msg);

    if(0 != lastUpdateId)
        SignalSlotCommutator::getInstance()->emitUpdJourMSG(lastUpdateId);
//        emit this->updateMSG(lastUpdateId);
    return lastUpdateId;
}

int DataBaseManager::updateJourMsg(JourEntity &msg)
{
//    int needReason = ServerSettingUtils::getValueSettings("P1", "PostgresSQL").toInt();
//    int needMeasure = ServerSettingUtils::getValueSettings("P2", "PostgresSQL").toInt();

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


    sql = sql.arg(field).arg(sqlId);

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
        return listId.size();
    }

    qDebug() << "DataBaseManager::updateJourMsgFieldById Error :" << query.lastError().text();
    qDebug() << query.lastQuery();
    qDebug() << query.boundValues();
    return 0;
}

int DataBaseManager::checkNecessarilyReasonMeasureFill() {
    int needReason = ServerSettingUtils::getValueSettings("P1", "PostgresSQL").toInt();
    int needMeasure = ServerSettingUtils::getValueSettings("P2", "PostgresSQL").toInt();

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
//        //qDebug() << "DataBaseManager::resetAllFlags ";
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

            result.append(me);
        }
    }

//    //qDebug() << "DataBaseManager::getQueryMSGRecord(" << query.lastQuery() << ")";
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
//        //qDebug() << "DataBaseManager::executeQuery(" << query.lastQuery() << ")";
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
    QList<JourEntity> result;
    QString sql;
    sql = "SELECT * FROM public.jour ";
    if(id > 0 || !flt.isEmpty()) {
        sql += " WHERE ";
        if(id > 0)
            sql += " id > :id ";
        if(-1 != DataBaseManager::getIdStartLastDuty()) {
            if(id > 0)
                sql += " AND ";
            sql += " id >= :idMin ";
        }
        if(!flt.isEmpty()) {
            if(id > 0 || -1 != DataBaseManager::getIdStartLastDuty())
                sql += " AND ";
            sql += " ( " + flt + " ) ";
        }
    }
    sql += " ORDER BY id ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":id", id);
    if(-1 != DataBaseManager::getIdStartLastDuty()) {
        query.bindValue(":idMin", DataBaseManager::getIdStartLastDuty());
    }

    result = DataBaseManager::getQueryMSGRecord(query);
//    //qDebug() << "DataBaseManager::getFltMSGRecordAfter(" << flt << ", " << id << ")";

    return result;
}



QList<JourEntity> DataBaseManager::getFltOneMSGRecord(const QString flt, const int &id) {
    QList<JourEntity> result;
    QString sql;
    sql = "SELECT * FROM public.jour ";
    if(id > 0 || !flt.isEmpty() || -1 != DataBaseManager::getIdStartLastDuty()) {
        sql += " WHERE ";
        if(id > 0)
            sql += " id = :id ";
        if(-1 != DataBaseManager::getIdStartLastDuty()) {
            if(id > 0)
                sql += " AND ";
            sql += " id >= :idMin ";
        }
        if(!flt.isEmpty()) {
            if(id > 0 || -1 != DataBaseManager::getIdStartLastDuty())
                sql += " AND ";
            sql += " ( " + flt + " ) ";
        }
    }
    sql += " ORDER BY id ";

    QSqlQuery query(m_db());
    query.prepare(sql);

    query.bindValue(":id", id);
    if(-1 != DataBaseManager::getIdStartLastDuty()) {
        query.bindValue(":idMin", DataBaseManager::getIdStartLastDuty());
    }

    result = DataBaseManager::getQueryMSGRecord(query);
    qDebug() << "DataBaseManager::getFltOneMSGRecord" << query.lastQuery() << id << DataBaseManager::getIdStartLastDuty();
//    //qDebug() << "DataBaseManager::getFltOneMSGRecord(" << flt << ", " << id << ")";

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
    if(direction.isEmpty())
        return "";
    QString sqlFlt;
    sqlFlt += " (direction='" + direction + "') ";
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
        if(0 < d1)
            sqlFlt += " AND d1=" + QString::number(d1);
        if(0 < d2)
            sqlFlt += " AND d2=" + QString::number(d2);
        if(0 < d3)
            sqlFlt += " AND d3=" + QString::number(d3);
        break;
    }
    case JourEntity::oIU: {
        sqlFlt += " (objecttype=4 OR objecttype=43)";  /* ИУ */
        if(0 < d1)
            sqlFlt += " AND d1=" + QString::number(d1);
        if(0 < d2)
            sqlFlt += " AND d2=" + QString::number(d2);
        if(0 < d3)
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
