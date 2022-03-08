#ifndef PROCESSINGSTATEWORD0X41SSOIBLIPDK_H
#define PROCESSINGSTATEWORD0X41SSOIBLIPDK_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x41SSOIBLIPDK : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x41SSOIBLIPDK(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x41SSOIBLIPDK();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X41SSOIBLIPDK_H
