#ifndef PROCESSINGSTATEWORD0X42BLIPIU_H
#define PROCESSINGSTATEWORD0X42BLIPIU_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x42BLIPIU : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x42BLIPIU(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x42BLIPIU();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X42BLIPIU_H
