#include <JourEntity.h>

#include <Utils.h>

QMap<int, QString> JourEntity::mapTypeObject = {{TypeObject::AllObject,"Все"},
                                                {TypeObject::SD,"СД"},
                                                {TypeObject::IU,"ИУ"},
                                                {TypeObject::RIFRLM,"РИФ-РЛМ(КРЛ), Трасса"},
                                                {TypeObject::SDCollector,"СД концентратора"},
                                                {TypeObject::Toros,"Торос"},
                                                {TypeObject::Nast,"Наст"},
                                                {TypeObject::Radar,"Радар"},
                                                {TypeObject::RazrivBO,"Разрыв БО"},
                                                {TypeObject::TochkaGard,"Точка/Гарда"},
                                                {TypeObject::Adam,"Адам-406x/4168"},
                                                {TypeObject::SDBLIP,"СД БЛ-IP"},
                                                {TypeObject::IUBLIP,"ИУ БЛ-IP"},
                                                {TypeObject::RIFRLMS,"РИФ-РЛМ-С"},
                                                {TypeObject::BODTochkaM,"БОД Точка-М/Гарда-М"},
                                                {TypeObject::DDTochkaM,"ДД Точка-М/Гарда-М"},
                                                {TypeObject::BODSota,"БОД Сота/Сота-М"},
                                                {TypeObject::DDSota,"ДД Сота/Сота-М"}};

QMap<int, QString> JourEntity::mapTypeEvent = {{TypeEvent::AllEvent, "Все"},
                                               {TypeEvent::Alarm, "Тревоги"},
                                               {TypeEvent::Fault, "Неисправности"},
                                               {TypeEvent::Command, "Команды"}};


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
