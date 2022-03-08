#ifndef PROCESSINGSTATEWORD0X32T4KBOD_H
#define PROCESSINGSTATEWORD0X32T4KBOD_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x32T4KBOD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32T4KBOD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32T4KBOD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X32T4KBOD_H
