#ifndef MESSAGEENTITY_H
#define MESSAGEENTITY_H

#include <QObject>
#include <QDateTime>
#include <QVariant>

class MessageEntity : public QObject
{
    Q_OBJECT
private:

    int id = 0;
    QDateTime cdate = QDateTime::currentDateTime();
    QDateTime mdate = QDateTime::currentDateTime();
    QString object;
    QString operatorid;
    QString direction;
    QByteArray bytearraydata;


public:

    explicit MessageEntity(QObject *parent = nullptr);
    MessageEntity(const MessageEntity & parent);
    MessageEntity(MessageEntity *parent);
    MessageEntity & operator=(const MessageEntity& );

    int getId() const;
    void setId(int value);

    QDateTime getCdate() const;
    void setCdate(const QDateTime &value = QDateTime::currentDateTime());

    QDateTime getMdate() const;
    void setMdate(const QDateTime &value = QDateTime::currentDateTime());

    QString getObject() const;
    void setObject(const QString &value);

    QString getOperatorid() const;
    void setOperatorid(const QString &value);

    QString getDirection() const;
    void setDirection(const QString &value);

    QByteArray getBytearraydata() const;
    void setBytearraydata(const QByteArray &value);

private:

signals:

};

#endif // MESSAGEENTITY_H
