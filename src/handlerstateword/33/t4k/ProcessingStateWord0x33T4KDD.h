#ifndef PROCESSINGSTATEWORD0X33T4KDD_H
#define PROCESSINGSTATEWORD0X33T4KDD_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x33T4KDD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x33T4KDD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x33T4KDD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X33T4KDD_H
