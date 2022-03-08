#ifndef PROCESSINGSTATEWORD0X31TG_H
#define PROCESSINGSTATEWORD0X31TG_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x31TG : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x31TG(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x31TG();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X31TG_H
