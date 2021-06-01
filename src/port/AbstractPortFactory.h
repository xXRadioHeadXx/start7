#ifndef ABSTRACTPORTFACTORY_H
#define ABSTRACTPORTFACTORY_H

#include <QObject>
#include "AbstractPort.h"

class AbstractPortFactory
{
public:
    AbstractPortFactory() {}
    virtual ~AbstractPortFactory() {}
    virtual AbstractPort * create(AbstractPort::Protocol protocol, const int index = 0, QObject *parent = nullptr) const = 0;
//    virtual QString protocol() = 0;
};

#endif // ABSTRACTPORTFACTORY_H
