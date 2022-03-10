#ifndef PROCESSINGSTATEWORD0X34T4KDD_H
#define PROCESSINGSTATEWORD0X34T4KDD_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x34T4KDD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x34T4KDD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x34T4KDD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X34T4KDD_H
