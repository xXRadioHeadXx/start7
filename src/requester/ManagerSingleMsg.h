#ifndef MANAGERSINGLEMSG_H
#define MANAGERSINGLEMSG_H

#include <QObject>
#include <QSharedPointer>

class UnitNode;
class DataQueueItem;
class ManagerSingleMsg : public QObject
{
    Q_OBJECT

protected:
    QSharedPointer<UnitNode> target;
    QByteArray(*maker)(const QSharedPointer<UnitNode>);

public:
    ManagerSingleMsg(const QSharedPointer<UnitNode> &target, QByteArray(*maker)(const QSharedPointer<UnitNode>));

    virtual DataQueueItem makeDatagram() const;

public slots:

    virtual void accident();
    virtual void incident();
    virtual void planned();
    virtual void accept();
    virtual void reject();

signals:
    virtual void acceptended();
    virtual void rejected();

};

#endif // MANAGERSINGLEMSG_H
