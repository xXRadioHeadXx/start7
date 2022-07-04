#ifndef PROCESSINGSTATEWORD0X31RLM_H
#define PROCESSINGSTATEWORD0X31RLM_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x31RLM : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x31RLM(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x31RLM();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X31RLM_H
