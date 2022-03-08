#include "ContextArgMap.h"

QMap<QString, QString> &ContextArgMap::argMap()
{
    return ContextArgMap::instance().map;
}
