#ifndef UNITNODEFACTORY_H
#define UNITNODEFACTORY_H

#include <UnitNode.h>

class UnitNodeFactory
{
public:
    UnitNodeFactory();

    static UnitNode * make(TypeUnitNode type, UnitNode * parent = nullptr);
    static UnitNode * make(const UnitNode & parent);

};



#endif // UNITNODEFACTORY_H
