#ifndef PROCESSINGSTATEWORD0X41SSOIBLIPUZO_H
#define PROCESSINGSTATEWORD0X41SSOIBLIPUZO_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x41SSOIBLIPUzo : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x41SSOIBLIPUzo(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x41SSOIBLIPUzo();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X41SSOIBLIPUZO_H
