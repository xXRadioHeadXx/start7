#ifndef PROCESSINGSTATEWORD0X42BLIPDK_H
#define PROCESSINGSTATEWORD0X42BLIPDK_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x42BLIPDK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x42BLIPDK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x42BLIPDK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X42BLIPDK_H
