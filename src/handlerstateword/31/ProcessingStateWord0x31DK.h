#ifndef PROCESSINGSTATEWORD0X31DK_H
#define PROCESSINGSTATEWORD0X31DK_H

#include <ProcessingStateWordAbstract.h>

class AbstractRequester;
class ProcessingStateWord0x31DK : public ProcessingStateWordAbstract
{
    void finishDKWaiter(QSharedPointer<AbstractRequester> ar) const;
    void procDK(const QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous) const;

public:
    ProcessingStateWord0x31DK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x31DK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X31DK_H
