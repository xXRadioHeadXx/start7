#ifndef MULTIUNSTATUSCONNECTREQUESTER_H
#define MULTIUNSTATUSCONNECTREQUESTER_H

#include "AbstractRequester.h"

class MultiUNStatusConnectRequester final : public AbstractRequester
{
private:
    QList<QSharedPointer<UnitNode>> lsTrackedUN;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

public:
    explicit MultiUNStatusConnectRequester(QSharedPointer<UnitNode>  target, RequesterType requesterType = RequesterType::ConnectRequester);
    virtual ~MultiUNStatusConnectRequester();

    virtual void init() override;

    QList<QSharedPointer<UnitNode>> getLsTrackedUN() const;
    void setLsTrackedUN(const QList<QSharedPointer<UnitNode>> &value);
    void addLsTrackedUN(QSharedPointer<UnitNode> value);

    QSharedPointer<UnitNode> previousTrackedUN() const;
    QSharedPointer<UnitNode> currentTrackedUN() const;
    QSharedPointer<UnitNode> nextTrackedUN() const;

    int optimalTimeIntervalRequest(QSharedPointer<UnitNode> un) const;

private slots:
    virtual void specialReserveSlot() const override;
public slots:
    virtual void aspectAfterFirstRequest() override;
};

#endif // MULTIUNSTATUSCONNECTREQUESTER_H
