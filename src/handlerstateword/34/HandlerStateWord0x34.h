#ifndef HANDLERSTATEWORD0X34_H
#define HANDLERSTATEWORD0X34_H

#include <HandlerStateWordAbstract.h>

class HandlerStateWord0x34 : public HandlerStateWordAbstract
{
public:
    HandlerStateWord0x34(const DataQueueItem & dataItem);
    virtual ~HandlerStateWord0x34();
    void onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // HANDLERSTATEWORD0X34_H
