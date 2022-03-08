#ifndef PROCESSINGSTATEWORD0X41SSOIBLIPSD_H
#define PROCESSINGSTATEWORD0X41SSOIBLIPSD_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x41SSOIBLIPSD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x41SSOIBLIPSD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x41SSOIBLIPSD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X41SSOIBLIPSD_H
