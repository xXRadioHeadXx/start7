#ifndef PROCESSINGSTATEWORD0X33TG_H
#define PROCESSINGSTATEWORD0X33TG_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x33TG : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x33TG(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x33TG();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X33TG_H
