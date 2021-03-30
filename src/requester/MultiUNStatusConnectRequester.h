#ifndef MULTIUNSTATUSCONNECTREQUESTER_H
#define MULTIUNSTATUSCONNECTREQUESTER_H

#include <AbstractRequester.h>

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

private slots:
    virtual void specialReserveSlot() const override;

};

#endif // MULTIUNSTATUSCONNECTREQUESTER_H
