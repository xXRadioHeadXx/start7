#ifndef PROCESSINGSTATEWORD0X42SSOIBLIPDK_H
#define PROCESSINGSTATEWORD0X42SSOIBLIPDK_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x42SSOIBLIPDK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x42SSOIBLIPDK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x42SSOIBLIPDK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X42SSOIBLIPDK_H
