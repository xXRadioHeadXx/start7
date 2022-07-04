#ifndef PROCESSINGSTATEWORD0X41BLIPUZO_H
#define PROCESSINGSTATEWORD0X41BLIPUZO_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x41BLIPUzo : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x41BLIPUzo(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x41BLIPUzo();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X41BLIPUZO_H
