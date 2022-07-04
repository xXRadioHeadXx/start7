#ifndef PROCESSINGSTATEWORD0X34TG_H
#define PROCESSINGSTATEWORD0X34TG_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x34TG : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x34TG(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x34TG();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X34TG_H
