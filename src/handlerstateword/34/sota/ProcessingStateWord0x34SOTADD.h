#ifndef PROCESSINGSTATEWORD0X34SOTADD_H
#define PROCESSINGSTATEWORD0X34SOTADD_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x34SOTADD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x34SOTADD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x34SOTADD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X34SOTADD_H
