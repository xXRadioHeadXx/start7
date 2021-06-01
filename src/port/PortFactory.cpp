#include "Port.h"
#include "PortFactory.h"

PortFactory::PortFactory(AbstractPort::Protocol protocol) : AbstractPortFactory()
{
    this->protocol = protocol;
}

PortFactory::~PortFactory()
{

}

//AbstractPort * PortFactory::create(const int index, QObject *parent) {
//    if(AbstractPort::UDP == getProtocol())
//        return new Port(AbstractPort::UDP, parent, index);
//    else
//        nullptr;
//}

AbstractPort * PortFactory::create(AbstractPort::Protocol protocol, const int index, QObject *parent) const {
    if(AbstractPort::UDP == protocol)
        return new Port(AbstractPort::UDP, parent, index);
    else if(AbstractPort::TCP == protocol)
        return new Port(AbstractPort::TCP, parent, index);
    else
        return nullptr;
}

AbstractPort::Protocol PortFactory::getProtocol() {
    return protocol;
}
