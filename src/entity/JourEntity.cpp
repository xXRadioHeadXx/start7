#include <JourEntity.h>

#include <Icons.h>
#include <Utils.h>

QMap<int, QString> JourEntity::mapTypeObject = {{TypeObject::oAllObject, trUtf8("Все")},
                                                {TypeObject::oSD, trUtf8("СД")},
                                                {TypeObject::oIU, trUtf8("ИУ")},
                                                {TypeObject::oRIFRLM, trUtf8("РИФ-РЛМ(КРЛ), Трасса")},
                                                {TypeObject::oSDCollector, trUtf8("СД концентратора")},
                                                {TypeObject::oToros, trUtf8("Торос")},
                                                {TypeObject::oNast, trUtf8("Наст")},
                                                {TypeObject::oRadar, trUtf8("Радар")},
                                                {TypeObject::oRazrivBO, trUtf8("Разрыв БО")},
                                                {TypeObject::oTochkaGard, trUtf8("Точка/Гарда")},
                                                {TypeObject::oAdam, trUtf8("Адам-406x/4168")},
                                                {TypeObject::oSDBLIP, trUtf8("СД БЛ-IP")},
                                                {TypeObject::oIUBLIP, trUtf8("ИУ БЛ-IP")},
                                                {TypeObject::oRIFRLMS, trUtf8("РИФ-РЛМ-С")},
                                                {TypeObject::oBODTochkaM, trUtf8("БОД Точка-М/Гарда-М")},
                                                {TypeObject::oDDTochkaM, trUtf8("ДД Точка-М/Гарда-М")},
                                                {TypeObject::oBODSota, trUtf8("БОД Сота/Сота-М")},
                                                {TypeObject::oDDSota, trUtf8("ДД Сота/Сота-М")}};

QMap<int, QString> JourEntity::mapTypeEvent = {{TypeEvent::eAllEvent, trUtf8("Все")},
                                               {TypeEvent::eAlarm, trUtf8("Тревоги")},
                                               {TypeEvent::eAlarmWorked, trUtf8("Тревога - СРАБОТКА")},
                                               {TypeEvent::eAlarmOpening, trUtf8("Тревога - ВСКРЫТИЕ")},
                                               {TypeEvent::eFault, trUtf8("Неисправности")},
                                               {TypeEvent::eFaultNoConnect, trUtf8("Нет связи")},
                                               {TypeEvent::eFaultDK, trUtf8("Ком. ДК не выполнена")},
                                               {TypeEvent::eFaultCommand, trUtf8("Ком. упр. не выполнена")},
                                               {TypeEvent::eCommand, trUtf8("Команды")},
                                               {TypeEvent::eCommandDK, trUtf8("ДК")},
                                               {TypeEvent::eCommandUZMonolit, trUtf8("УЗ Монолит")},
                                               {TypeEvent::eCommandOperator, trUtf8("Оператор")}};

QMap<int, QString> JourEntity::mapTypeConnectObject = {{TypeConnectObject::coAllConnectObject, trUtf8("не указан")},
                                                       {TypeConnectObject::coRIFRLM, trUtf8("РИФ-РЛМ")},
                                                       {TypeConnectObject::coRIFKRL, trUtf8("РИФ-КРЛ")},
                                                       {TypeConnectObject::coRIFKRLM, trUtf8("РИФ-КРЛМ")},
                                                       {TypeConnectObject::coRIFRLMS, trUtf8("РИФ-РЛМ-С")},
                                                       {TypeConnectObject::coTrassa, trUtf8("Трасса")},
                                                       {TypeConnectObject::coTochkaGard, trUtf8("Точка/Гарда")},
                                                       {TypeConnectObject::coRazryad, trUtf8("Разряд")}};

QMap<int, QString> JourEntity::getMapTypeEvent()
{
    return mapTypeEvent;
}

QMap<int, QString> JourEntity::getMapTypeObject()
{
    return mapTypeObject;
}

int JourEntity::getD1() const
{
    return d1;
}

void JourEntity::setD1(int value)
{
    d1 = value;
}

int JourEntity::getD2() const
{
    return d2;
}

void JourEntity::setD2(int value)
{
    d2 = value;
}

int JourEntity::getD3() const
{
    return d3;
}

void JourEntity::setD3(int value)
{
    d3 = value;
}

int JourEntity::getD4() const
{
    return d4;
}

void JourEntity::setD4(int value)
{
    d4 = value;
}

int JourEntity::getType() const
{
    return type;
}

void JourEntity::setType(int value)
{
    type = value;
}

int JourEntity::getObjecttype() const
{
    return objecttype;
}

void JourEntity::setObjecttype(int value)
{
    objecttype = value;
}

int JourEntity::getFlag() const
{
    return flag;
}

void JourEntity::setFlag(int value)
{
    flag = value;
}

QMap<int, QString> JourEntity::getMapTypeConnectObject()
{
    return mapTypeConnectObject;
}

QPixmap JourEntity::getPxm() const
{
    switch( this->getType() )
    {
       case   1:
       case   2:
       case   7:
       case 101:
       case 111:
        return Icons::crcl_grn();
       case   3:
       case   4:
       case 142:
       case 130:
       case 131:
       case 132:
       case 133:
       case 134:
       case 135:
       case 136:
       case 137:
       case 138:
       case 140:
       case 141:
       case 150:
       case 160:
       case 170:
       case 171:
       case 172:
       case 173:
       case 174:
       case 175:
       case 900:
       case 901:
        return Icons::chck_grn();
       case   5:
       case   6:
       case  10:
       case 200:
        return Icons::crcl_ylw();
       case  11:
       case  12:
       case  13:
       case  15:
       case  16:
       case  17:
       case  31:
        return Icons::crcl_blu();
       case  20:
       case  21:
       case  22:
       case  23:
       case  24:
       case  25:
       case  26:
       case  27:
        return Icons::crcl_rd();
       case  30:
       case 100:
       case 110:
        return Icons::crcl_blk();
       default:
        return QPixmap();
    }
}

QColor JourEntity::getColor() const
{
    switch( this->getType() )
    {
       case   1:
       case   2:
       case   7:
       case 101:
       case 111:
        return QColor(0, 0, 0);;
//        return Icons::crcl_grn();
       case   3:
       case   4:
       case 142:
       case 130:
       case 131:
       case 132:
       case 133:
       case 134:
       case 135:
       case 136:
       case 137:
       case 138:
       case 140:
       case 141:
       case 150:
       case 160:
       case 170:
       case 171:
       case 172:
       case 173:
       case 174:
       case 175:
       case 900:
       case 901:
        return QColor(0, 150, 64);
//        return Icons::chck_grn();
       case   5:
       case   6:
       case  10:
       case 200:
        return QColor(255, 221, 14);
//        return Icons::crcl_ylw();
       case  11:
       case  12:
       case  13:
       case  15:
       case  16:
       case  17:
       case  31:
        return QColor(15, 122, 183);
//        return Icons::crcl_blu();
       case  20:
       case  21:
       case  22:
       case  23:
       case  24:
       case  25:
       case  26:
       case  27:
        return QColor(227, 6, 19);
//        return Icons::crcl_rd();
       case  30:
       case 100:
       case 110:
        return QColor(0, 0, 0);
//        return Icons::crcl_blk();
       default:
        return QColor(0, 0, 0);
    }
}

JourEntity::JourEntity(QObject *parent) : QObject(parent)
{
    
}

JourEntity::JourEntity(const JourEntity & parent) :
    QObject(nullptr),
    id(parent.getId()),
    cdate(parent.getCdate()),
    mdate(parent.getMdate()),
    comment(parent.getComment()),
    object(parent.getObject()),
    objectid(parent.getObjectid()),
    reason(parent.getReason()),
    measures(parent.getMeasures()),
    operatorid(parent.getOperatorid()),
    status(parent.getStatus()),
    direction(parent.getDirection()),
    d1(parent.getD1()),
    d2(parent.getD2()),
    d3(parent.getD3()),
    d4(parent.getD4()),
    type(parent.getType()),
    objecttype(parent.getObjecttype()),
    flag(parent.getFlag())
{

}

JourEntity::JourEntity(JourEntity * parent) :
    QObject(parent),
    id(parent->getId()),
    cdate(parent->getCdate()),
    mdate(parent->getMdate()),
    comment(parent->getComment()),
    object(parent->getObject()),
    objectid(parent->getObjectid()),
    reason(parent->getReason()),
    measures(parent->getMeasures()),
    operatorid(parent->getOperatorid()),
    status(parent->getStatus()),
    direction(parent->getDirection()),
    d1(parent->getD1()),
    d2(parent->getD2()),
    d3(parent->getD3()),
    d4(parent->getD4()),
    type(parent->getType()),
    objecttype(parent->getObjecttype()),
    flag(parent->getFlag())
{

}

QVariant JourEntity::data(int column) const noexcept
{
    if(0 != getId() )
    {
        switch(column)
        {
            case 0:
            {
                return QVariant(getId());
            };

            case 1:
            {
                return QVariant(getCdate().toString("dd.MM.yy hh:mm:ss"));
            };

            case 2:
            {

                return QVariant(getComment());

                QString str = Utils::baMsgToStr(QByteArray::fromHex(getComment().toUtf8()));

                return QVariant(str.isEmpty() ? getComment().toUtf8() : str);
            };

            case 3:
            {
                return QVariant(getObject());
            };

            case 4:
            {
                return QVariant(getReason());
            };

            case 5:
            {
                return QVariant(getMeasures());
            };

            case 6:
            {
                return QVariant(getOperatorid());
            };

            default:
                return QVariant();
        };
    } else {
        switch(column)
                {
                    case 0:
                        return "№/#";
                    case 1:
                        return QObject::trUtf8("Дата"); //"Дата";
                    case 2:
                        return QObject::trUtf8("Сообщение"); //"Сообщение";
                    case 3:
                        return QObject::trUtf8("Объект"); //"Объект";
                    case 4:
                        return QObject::trUtf8("Причина"); //"Причина";
                    case 5:
                        return QObject::trUtf8("Принятые меры"); //"Принятые меры"
                    case 6:
                        return QObject::trUtf8("Оператор"); //"Оператор"
                    default:
                        return QVariant();
                }
    }
    return QVariant();
}

JourEntity & JourEntity::operator=(const JourEntity& c) {
    setId(c.getId());
    setCdate(c.getCdate());
    setMdate(c.getMdate());
    setComment(c.getComment());
    setObject(c.getObject());
    setObjectid(c.getObjectid());
    setReason(c.getReason());
    setMeasures(c.getMeasures());
    setOperatorid(c.getOperatorid());
    setStatus(c.getStatus());
    setDirection(c.getDirection());
    setD1(c.getD1());
    setD2(c.getD2());
    setD3(c.getD3());
    setD4(c.getD4());
    setType(c.getType());
    setObjecttype(c.getObjecttype());
    setFlag(c.getFlag());

    return *this;
}

int JourEntity::getId() const
{
    return id;
}

void JourEntity::setId(int value)
{
    id = value;
}

QDateTime JourEntity::getCdate() const
{
    return cdate;
}

void JourEntity::setCdate(const QDateTime &value)
{
    cdate = value;
}

QDateTime JourEntity::getMdate() const
{
    return mdate;
}

void JourEntity::setMdate(const QDateTime &value)
{
    mdate = value;
}

QString JourEntity::getComment() const
{
    return comment;
}

void JourEntity::setComment(const QString &value)
{
    comment = value;
}

QString JourEntity::getObject() const
{
    return object;
}

void JourEntity::setObject(const QString &value)
{
    object = value;
}

QString JourEntity::getReason() const
{
    return reason;
}

void JourEntity::setReason(const QString &value)
{
    reason = value;
}

QString JourEntity::getMeasures() const
{
    return measures;
}

void JourEntity::setMeasures(const QString &value)
{
    measures = value;
}

QString JourEntity::getOperatorid() const
{
    return operatorid;
}

void JourEntity::setOperatorid(const QString &value)
{
    operatorid = value;
}

QString JourEntity::getStatus() const
{
    return status;
}

void JourEntity::setStatus(const QString &value)
{
    status = value;
}

QString JourEntity::getDirection() const
{
    return direction;
}

void JourEntity::setDirection(const QString &value)
{
    direction = value;
}

int JourEntity::getObjectid() const
{
    return objectid;
}

void JourEntity::setObjectid(int value)
{
    objectid = value;
}
