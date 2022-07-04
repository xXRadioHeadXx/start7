#ifndef PROCESSINGSTATEWORD0X33SOTADK_H
#define PROCESSINGSTATEWORD0X33SOTADK_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class AbstractRequester;
class ProcessingStateWord0x33SOTADK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x33SOTADK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x33SOTADK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
private:
    void procDK(const QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous) const;
    void finishDKWaiter(QSharedPointer<AbstractRequester> ar) const;
};

#endif // PROCESSINGSTATEWORD0X33SOTADK_H
