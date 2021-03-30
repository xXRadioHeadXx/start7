#ifndef CONFIRMATIONADMISSIONWAITER_H
#define CONFIRMATIONADMISSIONWAITER_H

#include "AbstractRequester.h"

class ConfirmationAdmissionWaiter final : public AbstractRequester
{
public:
    explicit ConfirmationAdmissionWaiter(QSharedPointer<UnitNode>  target, RequesterType requesterType = RequesterType::ConfirmWaiter);
    virtual ~ConfirmationAdmissionWaiter();
    virtual void init() override;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

};

#endif // CONFIRMATIONADMISSIONWAITER_H
