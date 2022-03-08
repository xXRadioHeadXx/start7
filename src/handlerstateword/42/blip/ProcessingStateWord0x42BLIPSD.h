#ifndef PROCESSINGSTATEWORD0X42BLIPSD_H
#define PROCESSINGSTATEWORD0X42BLIPSD_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x42BLIPSD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x42BLIPSD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x42BLIPSD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;

};

#endif // PROCESSINGSTATEWORD0X42BLIPSD_H
