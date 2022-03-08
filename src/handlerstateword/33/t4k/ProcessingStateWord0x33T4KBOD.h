#ifndef PROCESSINGSTATEWORD0X33T4KBOD_H
#define PROCESSINGSTATEWORD0X33T4KBOD_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x33T4KBOD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x33T4KBOD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x33T4KBOD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X33T4KBOD_H
