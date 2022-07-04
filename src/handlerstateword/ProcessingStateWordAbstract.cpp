#include "ProcessingStateWordAbstract.h"

#include "../src/statewordparsers/SWP.h"
#include "../src/entity/UnitNode.h"

const StateWord &ProcessingStateWordAbstract::getData() const
{
    return data;
}

const QSharedPointer<UnitNode> &ProcessingStateWordAbstract::getUn() const
{
    return un;
}

bool ProcessingStateWordAbstract::processing()
{
    return processing(getData(), getUn());
}

ProcessingStateWordAbstract::ProcessingStateWordAbstract(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    data(data)
  , un(un)
{

}

ProcessingStateWordAbstract::~ProcessingStateWordAbstract()
{

}
