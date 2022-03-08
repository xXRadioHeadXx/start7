#ifndef PROCESSINGSTATEWORD0X42SSOIBLIPIU_H
#define PROCESSINGSTATEWORD0X42SSOIBLIPIU_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x42SSOIBLIPIU : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x42SSOIBLIPIU(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x42SSOIBLIPIU();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X42SSOIBLIPIU_H
