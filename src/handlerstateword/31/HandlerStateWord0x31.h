#ifndef HANDLERSTATEWORD0X31_H
#define HANDLERSTATEWORD0X31_H

#include "HandlerStateWordAbstract.h"

class HandlerStateWord0x31 : public HandlerStateWordAbstract
{
public:
    HandlerStateWord0x31(const DataQueueItem & dataItem);
    virtual ~HandlerStateWord0x31();
    void onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // HANDLERSTATEWORD0X31_H
