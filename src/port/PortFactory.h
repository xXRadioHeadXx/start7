#ifndef PORTFACTORY_H
#define PORTFACTORY_H

#include <QString>
#include "AbstractPortFactory.h"
#include "Port.h"

class PortFactory : public AbstractPortFactory
{
public:
    PortFactory(AbstractPort::Protocol protocol);
    virtual ~PortFactory();
//    AbstractPort * create(const int index = 0, QObject *parent = nullptr);
    AbstractPort * create(AbstractPort::Protocol protocol, const int index = 0, QObject *parent = nullptr) const override;
    AbstractPort::Protocol getProtocol();
private:
    AbstractPort::Protocol protocol;
};

#endif // PORTFACTORY_H
