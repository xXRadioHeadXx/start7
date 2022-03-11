#ifndef PROCESSINGSTATEWORD0X32SOTADD_H
#define PROCESSINGSTATEWORD0X32SOTADD_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x32SOTADD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32SOTADD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32SOTADD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X32SOTADD_H
