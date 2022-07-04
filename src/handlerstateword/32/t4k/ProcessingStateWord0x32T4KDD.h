#ifndef PROCESSINGSTATEWORD0X32T4KDD_H
#define PROCESSINGSTATEWORD0X32T4KDD_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x32T4KDD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32T4KDD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32T4KDD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X32T4KDD_H
