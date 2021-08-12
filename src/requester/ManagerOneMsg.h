#ifndef MANAGERONEMSG_H
#define MANAGERONEMSG_H

#include "DataQueueItem.h"
#include <QObject>
#include <QSharedPointer>
#include "UnitNode.h"

class ManagerOneMsg : public QObject
{
    Q_OBJECT

    const QSharedPointer<UnitNode> target;
    QByteArray(*maker)(const QSharedPointer<UnitNode>);

public:
    explicit ManagerOneMsg(const QSharedPointer<UnitNode> &target, QByteArray(*maker)(const QSharedPointer<UnitNode>));

    DataQueueItem makeDatagram() const;

public slots:

    virtual void accident() = 0;
    virtual void incident() = 0;
    virtual void planned() = 0;
    virtual void accept() = 0;
    virtual void reject() = 0;

signals:
    virtual void acceptended();
    virtual void rejected();

};

#endif // MANAGERONEMSG_H
