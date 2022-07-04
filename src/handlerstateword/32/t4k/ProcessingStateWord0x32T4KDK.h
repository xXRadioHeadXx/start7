#ifndef PROCESSINGSTATEWORD0X32T4KDK_H
#define PROCESSINGSTATEWORD0X32T4KDK_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class AbstractRequester;
class ProcessingStateWord0x32T4KDK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32T4KDK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32T4KDK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
private:
    void finishDKWaiter(QSharedPointer<AbstractRequester> ar) const;
    void procDK(const QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous) const;
};

#endif // PROCESSINGSTATEWORD0X32T4KDK_H
