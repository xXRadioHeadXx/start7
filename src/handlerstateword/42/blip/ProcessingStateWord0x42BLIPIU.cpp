#include "ProcessingStateWord0x42BLIPIU.h"

ProcessingStateWord0x42BLIPIU::ProcessingStateWord0x42BLIPIU(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x42BLIPIU::~ProcessingStateWord0x42BLIPIU()
{

}

bool ProcessingStateWord0x42BLIPIU::processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    return true;
}
