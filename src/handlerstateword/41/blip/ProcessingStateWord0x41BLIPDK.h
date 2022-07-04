#ifndef PROCESSINGSTATEWORD0X41BLIPDK_H
#define PROCESSINGSTATEWORD0X41BLIPDK_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x41BLIPDK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x41BLIPDK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x41BLIPDK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;

};

#endif // PROCESSINGSTATEWORD0X41BLIPDK_H
