#ifndef PROCESSINGSTATEWORD0X32TG_H
#define PROCESSINGSTATEWORD0X32TG_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x32TG : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32TG(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32TG();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X32TG_H
