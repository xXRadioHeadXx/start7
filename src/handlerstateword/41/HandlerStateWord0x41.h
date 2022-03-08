#ifndef HANDLERSTATEWORD0X41_H
#define HANDLERSTATEWORD0X41_H

#include "../HandlerStateWordAbstract.h"

class HandlerStateWord0x41 : public HandlerStateWordAbstract
{
public:
    HandlerStateWord0x41(const DataQueueItem & dataItem);
    virtual ~HandlerStateWord0x41();
    void onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;

};

#endif // HANDLERSTATEWORD0X41_H
