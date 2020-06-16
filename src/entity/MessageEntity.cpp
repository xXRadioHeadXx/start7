#include <MessageEntity.h>

#include <Utils.h>


MessageEntity::MessageEntity(QObject *parent) : QObject(parent)
{

}

MessageEntity::MessageEntity(const MessageEntity & parent) :
    QObject(nullptr),
    id(parent.id),
    cdate(parent.cdate),
    mdate(parent.mdate),
    object(parent.object),
    operatorid(parent.operatorid),
    direction(parent.direction),
    bytearraydata(parent.bytearraydata)
{

}

MessageEntity::MessageEntity(MessageEntity * parent) :
    QObject(parent),
    id(parent->id),
    cdate(parent->cdate),
    mdate(parent->mdate),
    object(parent->object),
    operatorid(parent->operatorid),
    direction(parent->direction),
    bytearraydata(parent->bytearraydata)

{

}

MessageEntity & MessageEntity::operator=(const MessageEntity& c) {
    id = c.id;
    cdate = c.cdate;
    mdate = c.mdate;
    object = c.object;
    operatorid = c.operatorid;
    direction = c.direction;
    bytearraydata = c.bytearraydata;


    return *this;
}

int MessageEntity::getId() const
{
    return id;
}

void MessageEntity::setId(int value)
{
    id = value;
}

QDateTime MessageEntity::getCdate() const
{
    return cdate;
}

void MessageEntity::setCdate(const QDateTime &value)
{
    cdate = value;
}

QDateTime MessageEntity::getMdate() const
{
    return mdate;
}

void MessageEntity::setMdate(const QDateTime &value)
{
    mdate = value;
}

QString MessageEntity::getObject() const
{
    return object;
}

void MessageEntity::setObject(const QString &value)
{
    object = value;
}

QString MessageEntity::getOperatorid() const
{
    return operatorid;
}

void MessageEntity::setOperatorid(const QString &value)
{
    operatorid = value;
}

QString MessageEntity::getDirection() const
{
    return direction;
}

void MessageEntity::setDirection(const QString &value)
{
    direction = value;
}

QByteArray MessageEntity::getBytearraydata() const
{
    return bytearraydata;
}

void MessageEntity::setBytearraydata(const QByteArray &value)
{
    bytearraydata = value;
}
