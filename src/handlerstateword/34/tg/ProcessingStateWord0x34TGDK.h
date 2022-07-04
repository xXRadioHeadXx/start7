#ifndef PROCESSINGSTATEWORD0X34TGDK_H
#define PROCESSINGSTATEWORD0X34TGDK_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x34TGDK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x34TGDK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x34TGDK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X34TGDK_H
