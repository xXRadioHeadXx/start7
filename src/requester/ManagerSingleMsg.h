#ifndef MANAGERSINGLEMSG_H
#define MANAGERSINGLEMSG_H

#include <QObject>
#include <QSharedPointer>
#include <QTime>
#include <functional>

class UnitNode;
class DataQueueItem;
class QTime;
class ManagerSingleMsg : public QObject
{
    Q_OBJECT

    int countJour = 0;
    int countMaker = 0;
    int countReject = 0;
    QTime lastMakeTine;
protected:
    QSharedPointer<UnitNode> target;
    std::function<QByteArray(const QSharedPointer<UnitNode>)> maker;
    std::function<void(const QSharedPointer<UnitNode>)> jour;
    std::function<void()> accept;
    std::function<void()> reject;

public:
    ManagerSingleMsg(const QSharedPointer<UnitNode> &target, std::function<QByteArray(const QSharedPointer<UnitNode>)> maker);
    ManagerSingleMsg(const QSharedPointer<UnitNode> &target, std::function<QByteArray(const QSharedPointer<UnitNode>)> maker, std::function<void(const QSharedPointer<UnitNode>)> jour);


    virtual DataQueueItem makeDatagram();

    virtual bool equale(const ManagerSingleMsg &rhs) const final;
    friend bool equale(const ManagerSingleMsg &lhs, const ManagerSingleMsg &rhs);
    friend bool equale(const QSharedPointer<ManagerSingleMsg> &lhs, const QSharedPointer<ManagerSingleMsg> &rhs);

    void setMaker(const std::function<QByteArray(const QSharedPointer<UnitNode>)> &newMaker);

    void setJour(const std::function<void(const QSharedPointer<UnitNode>)> &newJour);

    int getCountMaker() const;

    void setAccept(const std::function<void ()> &value);
    void callAccept();


    void setReject(const std::function<void ()> &value);
    void callReject();

    QTime getLastMakeTine() const;
    QTime updLastMakeTine();

public slots:

    virtual void accident();
    virtual void incident();
    virtual void planned();


signals:
    void acceptended();
    void rejected();

};

#endif // MANAGERSINGLEMSG_H
