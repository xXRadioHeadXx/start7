#ifndef PROCESSINGSTATEWORD0X41BLIPIU_H
#define PROCESSINGSTATEWORD0X41BLIPIU_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x41BLIPIU : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x41BLIPIU(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x41BLIPIU();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X41BLIPIU_H
