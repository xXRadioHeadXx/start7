#ifndef PROCESSINGSTATEWORD0X33SOTADD_H
#define PROCESSINGSTATEWORD0X33SOTADD_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x33SOTADD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x33SOTADD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x33SOTADD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X33SOTADD_H
