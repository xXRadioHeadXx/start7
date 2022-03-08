#ifndef PROCESSINGSTATEWORD0X33T4KY4_H
#define PROCESSINGSTATEWORD0X33T4KY4_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x33T4KY4 : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x33T4KY4(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x33T4KY4();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X33T4KY4_H
