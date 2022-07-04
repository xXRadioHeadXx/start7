#ifndef PROCESSINGSTATEWORD0X41BLIPSD_H
#define PROCESSINGSTATEWORD0X41BLIPSD_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x41BLIPSD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x41BLIPSD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x41BLIPSD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X41BLIPSD_H
