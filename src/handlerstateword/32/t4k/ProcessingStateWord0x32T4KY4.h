#ifndef PROCESSINGSTATEWORD0X32T4KY4_H
#define PROCESSINGSTATEWORD0X32T4KY4_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x32T4KY4 : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32T4KY4(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32T4KY4();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X32T4KY4_H
