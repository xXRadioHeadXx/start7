#ifndef PROCESSINGSTATEWORD0X33T4KDK_H
#define PROCESSINGSTATEWORD0X33T4KDK_H

#include <ProcessingStateWordAbstract.h>

class AbstractRequester;
class ProcessingStateWord0x33T4KDK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x33T4KDK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x33T4KDK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
private:
    void procDK(const QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous) const;
    void finishDKWaiter(QSharedPointer<AbstractRequester> ar) const;
};

#endif // PROCESSINGSTATEWORD0X33T4KDK_H
