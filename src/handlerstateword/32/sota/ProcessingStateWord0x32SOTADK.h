#ifndef PROCESSINGSTATEWORD0X32SOTADK_H
#define PROCESSINGSTATEWORD0X32SOTADK_H

#include <ProcessingStateWordAbstract.h>

class AbstractRequester;
class ProcessingStateWord0x32SOTADK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32SOTADK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32SOTADK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
private:
    void finishDKWaiter(QSharedPointer<AbstractRequester> ar) const;
    void procDK(const QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous) const;
};

#endif // PROCESSINGSTATEWORD0X32SOTADK_H
