#ifndef PORTFACTORY_H
#define PORTFACTORY_H

#include <QString>
#include "AbstractPortFactory.h"

class PortFactory : public AbstractPortFactory
{
public:
    PortFactory(int protocol);
    virtual ~PortFactory();
    AbstractPort * create(int protocol, const int index = 0, QObject *parent = nullptr) const override;
    int getProtocol();
private:
    int protocol;
};

#endif // PORTFACTORY_H
