#ifndef PORTFACTORY_H
#define PORTFACTORY_H

#include <QString>

//#include <AbstractPort.h>
#include <AbstractPortFactory.h>
#include <Port.h>

class PortFactory : public AbstractPortFactory
{
public:
    PortFactory(AbstractPort::Protocol protocol);
    virtual ~PortFactory();
    AbstractPort * create(const int index = 0, QObject *parent = nullptr);
    static AbstractPort * create(AbstractPort::Protocol protocol, const int index = 0, QObject *parent = nullptr);
    AbstractPort::Protocol getProtocol();
private:
    AbstractPort::Protocol protocol;
};

#endif // PORTFACTORY_H
