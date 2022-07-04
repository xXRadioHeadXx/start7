#ifndef HANDLERSTATEWORD0X33_H
#define HANDLERSTATEWORD0X33_H

#include "../src/handlerstateword/HandlerStateWordAbstract.h"

class HandlerStateWord0x33 : public HandlerStateWordAbstract
{
public:
    HandlerStateWord0x33(const DataQueueItem & dataItem);
    virtual ~HandlerStateWord0x33();
    void onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // HANDLERSTATEWORD0X33_H
