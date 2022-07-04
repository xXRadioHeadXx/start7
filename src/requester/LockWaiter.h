#ifndef LOCKWAITER_H
#define LOCKWAITER_H

#include "../src/requester/AbstractRequester.h"

class LockWaiter final : public AbstractRequester
{
private:
    QSharedPointer<UnitNode>  unReciverIuBlIp = nullptr;
    QSharedPointer<UnitNode>  unReciverSdBlIp = nullptr;
    int initVarianrt = 0;

    DataQueueItem getOnMsg();
    DataQueueItem getOffMsg();

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

public:
    explicit LockWaiter(QSharedPointer<UnitNode>  target, RequesterType requesterType = RequesterType::LockRequester);
    virtual ~LockWaiter();

    virtual void init() override;

    QSharedPointer<UnitNode> getUnReciverIuBlIp();
    void setUnReciverIuBlIp(QSharedPointer<UnitNode> value);
    QSharedPointer<UnitNode> getUnReciverSdBlIp();
    void setUnReciverSdBlIp(QSharedPointer<UnitNode> value);
    int getInitVarianrt() const;
    void setInitVarianrt(int value);
};

#endif // LOCKWAITER_H
