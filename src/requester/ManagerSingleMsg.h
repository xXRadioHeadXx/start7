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

    virtual bool equale(const ManagerSingleMsg &rhs) const final;
    friend bool equale(const ManagerSingleMsg &lhs, const ManagerSingleMsg &rhs);
    friend bool equale(const QSharedPointer<ManagerSingleMsg> &lhs, const QSharedPointer<ManagerSingleMsg> &rhs);

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
