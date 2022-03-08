#include "HandlerStateWordAbstract.h"

#include "DataQueueItem.h"
#include "TopologyService.h"

HandlerStateWordAbstract::HandlerStateWordAbstract(const DataQueueItem &dataItem) :
    dataItem(dataItem)
{

}

HandlerStateWordAbstract::~HandlerStateWordAbstract()
{

}

const DataQueueItem &HandlerStateWordAbstract::getDataItem() const
{
    return dataItem;
}

void HandlerStateWordAbstract::handl(const DataQueueItem &data) const
{
    qDebug() << "Utils::HandlerStateWordAbstract() -->";
    const StateWord &newStateWord(data.data().mid(5, data.data().at(3)));

    const auto& sortedMetaRealUnitNodes = TopologyService::getSortedMetaRealUnitNodes();

    for(const auto &un : sortedMetaRealUnitNodes) {
        if(!data.address().isEqual(QHostAddress(un->getUdpAdress()))
        || data.port() != un->getUdpPort()
        || static_cast<uint8_t>(data.data().at(2)) != static_cast<uint8_t>(un->getNum1()))
            continue;

        auto reciver = TopologyService::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
            reciver->resetTimeStatusConnectRequesterWaitAnswer();
            reciver->setStateWord(static_cast<uint8_t>(data.data().at(4)) ,newStateWord);
        } else {
            qDebug() << "PortManager::HandlerStateWordAbstract --x match";
            continue;
        }

        onHandler(newStateWord, un);
    }

    qDebug() << "Utils::HandlerStateWordAbstract() <--";
}

void HandlerStateWordAbstract::handl()
{
    handl(getDataItem());
}
