#ifndef ABSTRACTPORTFACTORY_H
#define ABSTRACTPORTFACTORY_H

#include <QObject>

class AbstractPort;

class AbstractPortFactory
{
public:
    AbstractPortFactory() {}
    virtual ~AbstractPortFactory() {}
    virtual AbstractPort* create(const int index, QObject *parent) = 0;
    virtual QString protocol() = 0;
};

#endif // ABSTRACTPORTFACTORY_H
