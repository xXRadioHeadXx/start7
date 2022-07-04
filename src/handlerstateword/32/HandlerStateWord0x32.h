#ifndef HANDLERSTATEWORD0X32_H
#define HANDLERSTATEWORD0X32_H

#include "../src/handlerstateword/HandlerStateWordAbstract.h"

class HandlerStateWord0x32 : public HandlerStateWordAbstract
{
public:
    HandlerStateWord0x32(const DataQueueItem & dataItem);
    virtual ~HandlerStateWord0x32();
    void onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // HANDLERSTATEWORD0X32_H
