#ifndef PROCESSINGSTATEWORD0X31RLMC_H
#define PROCESSINGSTATEWORD0X31RLMC_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x31RLMC : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x31RLMC(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x31RLMC();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X31RLMC_H
