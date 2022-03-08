#ifndef UNITNODEFACTORY_H
#define UNITNODEFACTORY_H

#include "UnitNode.h"

class UnitNodeFactory
{
public:
    UnitNodeFactory();

    static QSharedPointer<UnitNode> makeShare(TypeUnitNodeEnum type, const QSharedPointer<UnitNode> parent = nullptr);
    static QSharedPointer<UnitNode> makeShare(const UnitNode & parent);

};



#endif // UNITNODEFACTORY_H
