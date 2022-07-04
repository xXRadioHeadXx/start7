#include "../src/port/Port.h"
#include "../src/port/PortFactory.h"

PortFactory::PortFactory(int protocol) : AbstractPortFactory()
{
    this->protocol = protocol;
}

PortFactory::~PortFactory()
{

}

AbstractPort * PortFactory::create(int protocol, const int index, QObject *parent) const {
    if(AbstractPort::UDP == protocol)
        return new Port(AbstractPort::UDP, parent, index);
    else if(AbstractPort::TCP == protocol)
        return new Port(AbstractPort::TCP, parent, index);
    else
        return nullptr;
}

int PortFactory::getProtocol() {
    return protocol;
}
