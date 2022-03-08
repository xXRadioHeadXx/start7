#ifndef PROCESSINGSTATEWORD0X32TGDK_H
#define PROCESSINGSTATEWORD0X32TGDK_H

#include <ProcessingStateWordAbstract.h>

class AbstractRequester;
class ProcessingStateWord0x32TGDK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32TGDK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32TGDK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
private:
    void procDK(const QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous) const;
    void finishDKWaiter(QSharedPointer<AbstractRequester> ar) const;
};

#endif // PROCESSINGSTATEWORD0X32TGDK_H
