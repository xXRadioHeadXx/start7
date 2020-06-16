#include <JourEntity.h>

#include <Utils.h>

JourEntity::JourEntity(QObject *parent) : QObject(parent)
{

}

JourEntity::JourEntity(const JourEntity & parent) :
    QObject(nullptr),
    id(parent.id),
    cdate(parent.cdate),
    mdate(parent.mdate),
    comment(parent.comment),
    object(parent.object),
    objectid(parent.objectid),
    reason(parent.reason),
    measures(parent.measures),
    operatorid(parent.operatorid),
    status(parent.status),
    direction(parent.direction)
{

}

JourEntity::JourEntity(JourEntity * parent) :
    QObject(parent),
    id(parent->id),
    cdate(parent->cdate),
    mdate(parent->mdate),
    comment(parent->comment),
    object(parent->object),
    objectid(parent->objectid),
    reason(parent->reason),
    measures(parent->measures),
    operatorid(parent->operatorid),
    status(parent->status),
    direction(parent->direction)
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
    id = c.id;
    cdate = c.cdate;
    mdate = c.mdate;
    comment = c.comment;
    object = c.object;
    objectid = c.objectid;
    reason = c.reason;
    measures = c.measures;
    operatorid = c.operatorid;
    status = c.status;
    direction = c.direction;

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
