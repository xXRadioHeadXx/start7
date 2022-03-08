#include "ProcessingStateWord0x42SSOIBLIPIU.h"

ProcessingStateWord0x42SSOIBLIPIU::ProcessingStateWord0x42SSOIBLIPIU(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x42SSOIBLIPIU::~ProcessingStateWord0x42SSOIBLIPIU()
{

}

bool ProcessingStateWord0x42SSOIBLIPIU::processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    return true;
}
