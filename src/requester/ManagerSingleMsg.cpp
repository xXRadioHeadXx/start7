#include "../src/requester/ManagerSingleMsg.h"
#include "../src/port/DataQueueItem.h"
#include "../src/entity/UnitNode.h"

#include "../src/utils/TopologyService.h"


int ManagerSingleMsg::getCountMaker() const
{
    return countMaker;
}

void ManagerSingleMsg::setAccept(const std::function<void ()> &value)
{
    accept = value;
}

void ManagerSingleMsg::callAccept()
{
    if(13 == target->getPublishedState()
    && TypeUnitNodeEnum::DD_SOTA != target->getType()
    && TypeUnitNodeEnum::DD_T4K_M != target->getType()) {
        target->setPublishedState(0);
        target->updDoubl();
    }
    if(accept) {
        const auto tmp = accept;
        tmp();
    }
}

void ManagerSingleMsg::setReject(const std::function<void ()> &value)
{
    reject = value;
}

void ManagerSingleMsg::callReject()
{
    if(0 == countReject && reject){
        countReject++;
        const auto tmp = reject;
        tmp();
    } else {
        countReject++;
    }

}

QTime ManagerSingleMsg::getLastMakeTine() const
{
    return lastMakeTine;
}

QTime ManagerSingleMsg::updLastMakeTine()
{
     return lastMakeTine = QTime::currentTime();
}

ManagerSingleMsg::ManagerSingleMsg(const QSharedPointer<UnitNode> &target,
                                   std::function<QByteArray (const QSharedPointer<UnitNode>)> maker) :
    QObject(nullptr),
    target(target),
    maker(maker)
{

}

ManagerSingleMsg::ManagerSingleMsg(const QSharedPointer<UnitNode> &target,
                                   std::function<QByteArray (const QSharedPointer<UnitNode>)> maker,
                                   std::function<void (const QSharedPointer<UnitNode>)> jour) :
    QObject(nullptr),
    target(target),
    maker(maker),
    jour(jour)
{

}

DataQueueItem ManagerSingleMsg::makeDatagram()
{
    DataQueueItem result;

    auto reciver = TopologyService::findReciver(target);
    if(reciver.isNull()) {
        return result;
    }

    result.setPort(reciver->getUdpPort());
    result.setAddress(Utils::hostAddress(reciver->getUdpAdress()));
    if(maker) {
        result.setData(maker(target));
        ++countMaker;
        updLastMakeTine();
    }

    if(nullptr != target && target->isNeedsPreamble())
        result.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));

    if(jour && 0 >= countJour) {
        jour(target);
        ++countJour;
    }

    return result;
}

bool ManagerSingleMsg::equale(const ManagerSingleMsg &rhs) const
{
    if(!target->equale(*(rhs.target.data())))
        return false;
    else if(maker.target_type() != rhs.maker.target_type())
        return false;

    return true;
}

bool equale(const ManagerSingleMsg &lhs, const ManagerSingleMsg &rhs) {
    if(!lhs.target->equale(*(rhs.target.data())))
        return false;
    else if(lhs.maker.target_type() != rhs.maker.target_type())
        return false;

    return true;
}

bool equale(const QSharedPointer<ManagerSingleMsg> &lhs, const QSharedPointer<ManagerSingleMsg> &rhs) {
    if(!lhs->target->equale(*(rhs->target.data())))
        return false;
    else if(lhs->maker.target_type() != rhs->maker.target_type())
        return false;

    return true;
}

void ManagerSingleMsg::setMaker(const std::function<QByteArray(const QSharedPointer<UnitNode>)> &newMaker) {
    maker = newMaker;
}

void ManagerSingleMsg::setJour(const std::function<void(const QSharedPointer<UnitNode>)> &newJour) {
    jour = newJour;
}

void ManagerSingleMsg::accident(){

}

void ManagerSingleMsg::incident() {

}

void ManagerSingleMsg::planned() {

}

