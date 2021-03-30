#ifndef UNITNODEFACTORY_H
#define UNITNODEFACTORY_H

#include <UnitNode.h>

class UnitNodeFactory
{
public:
    UnitNodeFactory();

    static QSharedPointer<UnitNode> make(TypeUnitNode type, QSharedPointer<UnitNode> parent = QSharedPointer<UnitNode>(nullptr));
    static QSharedPointer<UnitNode> make(const UnitNode & parent);

};



#endif // UNITNODEFACTORY_H
