#ifndef PROCESSINGSTATEWORD0X42SSOIBLIPSD_H
#define PROCESSINGSTATEWORD0X42SSOIBLIPSD_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x42SSOIBLIPSD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x42SSOIBLIPSD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x42SSOIBLIPSD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X42SSOIBLIPSD_H
