#ifndef PROCESSINGSTATEWORD0X41SSOIBLIPIU_H
#define PROCESSINGSTATEWORD0X41SSOIBLIPIU_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x41SSOIBLIPIU : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x41SSOIBLIPIU(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x41SSOIBLIPIU();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X41SSOIBLIPIU_H
