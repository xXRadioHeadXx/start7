#ifndef JOURENTITY_H
#define JOURENTITY_H

#include <QObject>
#include <QDateTime>
#include <QVariant>

class JourEntity : public QObject
{
    Q_OBJECT
private:

    int id = 0;
    QDateTime cdate = QDateTime::currentDateTime();
    QDateTime mdate = QDateTime::currentDateTime();
    QString comment;
    QString object;
    int objectid = 0;
    QString reason;
    QString measures;
//    QString operator;
    QString operatorid;
    QString status;
    QString direction;

public:

    explicit JourEntity(QObject *parent = nullptr);
    JourEntity(const JourEntity & parent);
    JourEntity(JourEntity *parent);
    QVariant data(int column) const noexcept;
    JourEntity & operator=(const JourEntity& );

    int getId() const;
    void setId(int value);

    QDateTime getCdate() const;
    void setCdate(const QDateTime &value = QDateTime::currentDateTime());

    QDateTime getMdate() const;
    void setMdate(const QDateTime &value = QDateTime::currentDateTime());

    QString getComment() const;
    void setComment(const QString &value);

    QString getObject() const;
    void setObject(const QString &value);

    QString getReason() const;
    void setReason(const QString &value);

    QString getMeasures() const;
    void setMeasures(const QString &value);

    QString getOperatorid() const;
    void setOperatorid(const QString &value);

    QString getStatus() const;
    void setStatus(const QString &value);

    QString getDirection() const;
    void setDirection(const QString &value);

    int getObjectid() const;
    void setObjectid(int value);

private:

signals:
};

#endif // JOURENTITY_H
