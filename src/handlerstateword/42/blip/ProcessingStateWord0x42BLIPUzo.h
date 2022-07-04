#ifndef PROCESSINGSTATEWORD0X42BLIPUZO_H
#define PROCESSINGSTATEWORD0X42BLIPUZO_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x42BLIPUzo : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x42BLIPUzo(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x42BLIPUzo();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X42BLIPUZO_H
