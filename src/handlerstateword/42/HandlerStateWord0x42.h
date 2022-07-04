#ifndef HANDLERSTATEWORD0X42_H
#define HANDLERSTATEWORD0X42_H

#include "../src/handlerstateword/HandlerStateWordAbstract.h"

class HandlerStateWord0x42 : public HandlerStateWordAbstract
{
public:
    HandlerStateWord0x42(const DataQueueItem & dataItem);
    virtual ~HandlerStateWord0x42();
    void onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // HANDLERSTATEWORD0X42_H
