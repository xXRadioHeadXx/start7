#include "LockWaiter.h"
#include "SignalSlotCommutator.h"

#include "PortManager.h"
#include "UnitNodeFactory.h"
#include "ServerSettingUtils.h"
#include "Utils.h"
#include "global.h"
#include "swpblip/SWPSDBLIPType0x41.h"
#include "swpblip/SWPIUBLIPType0x41.h"
#include "swpssoiblip/SWPSSOISDBLIPType0x41.h"
#include "swpssoiblip/SWPSSOIIUBLIPType0x41.h"

#include "MessageBoxServer.h"

#include "TopologyService.h"

LockWaiter::LockWaiter(QSharedPointer<UnitNode>  target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
    //qDebug() << "LockWaiter::LockWaiter(" << this << ") -->";
}

LockWaiter::~LockWaiter()
{
    //qDebug() << "LockWaiter::~LockWaiter(" << this << ") <--";
}

QSharedPointer<UnitNode> LockWaiter::getUnReciverIuBlIp()
{
    return unReciverIuBlIp;
}

void LockWaiter::setUnReciverIuBlIp(QSharedPointer<UnitNode> value)
{
    unReciverIuBlIp = value;
}

QSharedPointer<UnitNode> LockWaiter::getUnReciverSdBlIp()
{
    return unReciverSdBlIp;
}

void LockWaiter::setUnReciverSdBlIp(QSharedPointer<UnitNode> value)
{
    unReciverSdBlIp = value;
}

int LockWaiter::getInitVarianrt() const
{
    return initVarianrt;
}

void LockWaiter::setInitVarianrt(int value)
{
    initVarianrt = value;
}

DataQueueItem LockWaiter::getOnMsg()
{
    DataQueueItem msgOn;
    msgOn.setData(DataQueueItem::makeOn0x23(getUnReciverIuBlIp()));
    msgOn.setPort(getUnReciver()->getUdpPort());
    msgOn.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    msgOn.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(!getUnReciverIuBlIp().isNull()
    && TypeUnitNodeEnum::RLM_C == getUnReciverIuBlIp()->getType())
        msgOn.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));

    return msgOn;
}

DataQueueItem LockWaiter::getOffMsg()
{
    DataQueueItem msgOff;
    msgOff.setData(DataQueueItem::makeOff0x23(getUnReciverIuBlIp()));
    msgOff.setPort(getUnReciver()->getUdpPort());
    msgOff.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    msgOff.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(!getUnReciverIuBlIp().isNull()
    && TypeUnitNodeEnum::RLM_C == getUnReciverIuBlIp()->getType())
        msgOff.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));

    return msgOff;
}

DataQueueItem LockWaiter::makeFirstMsg() {
    if(TypeUnitNodeEnum::IU_BL_IP == getUnReciverIuBlIp()->getType()
    && TypeUnitNodeEnum::SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        if(1 == getInitVarianrt())
            return getOnMsg();
        else if(2 == getInitVarianrt())
            return getOffMsg();
        else if(3 == getInitVarianrt())
            return getOffMsg();
        else if(4 == getInitVarianrt())
            return getOnMsg();
    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == getUnReciverIuBlIp()->getType()
           && TypeUnitNodeEnum::SSOI_SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        if(1 == getInitVarianrt())
            return getOffMsg();
        else if(2 == getInitVarianrt())
            return getOnMsg();
        else if(3 == getInitVarianrt())
            return getOnMsg();
        else if(4 == getInitVarianrt())
            return getOffMsg();
    }
    return DataQueueItem();
}

DataQueueItem LockWaiter::makeSecondMsg() {
    if(TypeUnitNodeEnum::IU_BL_IP == getUnReciverIuBlIp()->getType()
    && TypeUnitNodeEnum::SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        if(1 == getInitVarianrt())
            return DataQueueItem();
        else if(2 == getInitVarianrt())
            return DataQueueItem();
        else if(3 == getInitVarianrt())
            return getOnMsg();
        else if(4 == getInitVarianrt())
            return getOffMsg();
    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == getUnReciverIuBlIp()->getType()
           && TypeUnitNodeEnum::SSOI_SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        if(1 == getInitVarianrt())
            return DataQueueItem();
        else if(2 == getInitVarianrt())
            return DataQueueItem();
        else if(3 == getInitVarianrt())
            return getOffMsg();
        else if(4 == getInitVarianrt())
            return getOnMsg();
    }
    return DataQueueItem();
}

DataQueueItem LockWaiter::makeEndMsg() {
    return DataQueueItem();
}

void LockWaiter::init() {

    if(getUnTarget().isNull()) {
        return;
    } else if(!getUnTarget().isNull()) {
        setUnReciver(TopologyService::findReciver(getUnTarget()));
    }

    if(getUnTarget().isNull() || getUnReciver().isNull())
        return;

    setUnReciverSdBlIp(getUnTarget());

    for(const auto& un : as_const(TopologyService::getSortedMetaRealUnitNodes())) {
        if((TypeUnitNodeEnum::IU_BL_IP == un->getType()
         || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType())
        && getUnReciverSdBlIp()->getNum1() == un->getNum1()
        && getUnReciverSdBlIp()->getNum2() == un->getNum2()
        && getUnReciverSdBlIp()->getUdpPort() == un->getUdpPort()
        && getUnReciverSdBlIp()->getUdpAdress() == un->getUdpAdress()) {
            setUnReciverIuBlIp(un);
            break;
        }
    }

    if(getUnReciverSdBlIp() == getUnReciver()
    || getUnReciver().isNull()
    || getUnReciverIuBlIp().isNull())
        return;

    setIpPort(QPair<QString, QString>(getUnReciver()->getUdpAdress(), QVariant(getUnReciver()->getUdpPort()).toString()));

    for(AbstractPort * pt : as_const(PortManager::getUdpPortsVector())) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }

    std::function<void()> updateStateConditionReactorNeedOpen;
    if(TypeUnitNodeEnum::IU_BL_IP == getUnReciverIuBlIp()->getType()
    && TypeUnitNodeEnum::SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        updateStateConditionReactorNeedOpen = ([iu = getUnReciverIuBlIp(), sd = getUnReciverSdBlIp()](){
                                                const auto& swpSD = sd->swpSDBLIPType0x41();
                                                const auto& swpIU = iu->swpIUBLIPType0x41();
                                                if((1 == swpSD.isAlarm()
                                                 && 1 == swpIU.isOff())  //Открыто
                                                || (1 == swpSD.isAlarm()
                                                 && 1 == swpIU.isOn())) //Открыто ключом
                                                {
                                                    return;
                                                }
                                                if(!sd->getName().isEmpty() && 1 != sd->getMetaEntity()) {
                                                    JourEntity msg;
                                                    msg.setObject(sd->getName());
                                                    msg.setObjecttype(sd->getType());
                                                    msg.setD1(sd->getNum1());
                                                    msg.setD2(sd->getNum2());
                                                    msg.setD3(sd->getNum3());
                                                    msg.setD4(sd->getOutType());
                                                    msg.setDirection(sd->getDirection());
                                                    msg.setType(13);
                                                    msg.setComment(tr("Ком. упр. не выполнена"));
                                                    msg.setParams(sd->makeJson());
                                                    DataBaseManager::insertJourMsg_wS(msg);
                                                    GraphTerminal::sendAbonentEventsAndStates(sd, msg);
                                                }
                                                if(10 != sd->getPublishedState()) {
                                                    sd->setPublishedState(13);
                                                    sd->updDoubl();
                                                }
    //                                            MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor();
    //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                            });

    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == getUnReciverIuBlIp()->getType()
           && TypeUnitNodeEnum::SSOI_SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        updateStateConditionReactorNeedOpen = ([iu = getUnReciverIuBlIp(), sd = getUnReciverSdBlIp()](){
                                                const auto& swpSD = sd->swpSSOISDBLIPType0x41();
                                                const auto& swpIU = iu->swpSSOIIUBLIPType0x41();
                                                if((1 == swpSD.isInAlarm()
                                                 && 1 == swpIU.isOff())  //Открыто
                                                || (1 == swpSD.isInAlarm()
                                                 && 1 == swpIU.isOn())) //Открыто ключом
                                                {
                                                    return;
                                                }
                                                if(!sd->getName().isEmpty()
                                                && 1 != sd->getMetaEntity()) {
                                                    JourEntity msg;
                                                    msg.setObject(sd->getName());
                                                    msg.setObjecttype(sd->getType());
                                                    msg.setD1(sd->getNum1());
                                                    msg.setD2(sd->getNum2());
                                                    msg.setD3(sd->getNum3());
                                                    msg.setD4(sd->getOutType());
                                                    msg.setDirection(sd->getDirection());
                                                    msg.setType(13);
                                                    msg.setComment(tr("Ком. упр. не выполнена"));
                                                    msg.setParams(sd->makeJson());
                                                    DataBaseManager::insertJourMsg_wS(msg);
                                                    GraphTerminal::sendAbonentEventsAndStates(sd, msg);
                                                }
                                                if(10 != sd->getPublishedState()) {
                                                    sd->setPublishedState(13);
                                                    sd->updDoubl();
                                                }
    //                                            MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor();
    //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                            });

    }

    std::function<void()> updateStateConditionReactorNeedClose;
    if(TypeUnitNodeEnum::IU_BL_IP == getUnReciverIuBlIp()->getType()
    && TypeUnitNodeEnum::SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        updateStateConditionReactorNeedClose = ([iu = getUnReciverIuBlIp(), sd = getUnReciverSdBlIp()](){
                                                    const auto& swpSD = sd->swpSDBLIPType0x41();
                                                    const auto& swpIU = iu->swpIUBLIPType0x41();
                                                    if((1 == swpSD.isNorm()
                                                     && 1 == swpIU.isOn())  //Закрыто
                                                    || (1 == swpSD.isNorm()
                                                     && 1 == swpIU.isOff())) //Закрыто ключом
                                                    {
                                                        return;
                                                    }
                                                    if(!sd->getName().isEmpty()
                                                    && 1 != sd->getMetaEntity()) {
                                                        JourEntity msg;
                                                        msg.setObject(sd->getName());
                                                        msg.setObjecttype(sd->getType());
                                                        msg.setD1(sd->getNum1());
                                                        msg.setD2(sd->getNum2());
                                                        msg.setD3(sd->getNum3());
                                                        msg.setD4(sd->getOutType());
                                                        msg.setDirection(sd->getDirection());
                                                        msg.setType(13);
                                                        msg.setComment(tr("Ком. упр. не выполнена"));
                                                        msg.setParams(sd->makeJson());
                                                        DataBaseManager::insertJourMsg_wS(msg);
                                                        GraphTerminal::sendAbonentEventsAndStates(sd, msg);
                                                    }
                                                    if(10 != sd->getPublishedState()) {
                                                        sd->setPublishedState(13);
                                                        sd->updDoubl();
                                                    }
        //                                            MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor();
        //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                                });
    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == getUnReciverIuBlIp()->getType()
           && TypeUnitNodeEnum::SSOI_SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        updateStateConditionReactorNeedClose = ([iu = getUnReciverIuBlIp(), sd = getUnReciverSdBlIp()](){
                                                    const auto& swpSD = sd->swpSSOISDBLIPType0x41();
                                                    const auto& swpIU = iu->swpSSOIIUBLIPType0x41();
                                                    if((1 == swpSD.isInNorm()
                                                     && 1 == swpIU.isOn())  //Закрыто
                                                    || (1 == swpSD.isInNorm()
                                                     && 1 == swpIU.isOff())) //Закрыто ключом
                                                    {
                                                        return;
                                                    }
                                                    if(!sd->getName().isEmpty()
                                                    && 1 != sd->getMetaEntity()) {
                                                        JourEntity msg;
                                                        msg.setObject(sd->getName());
                                                        msg.setObjecttype(sd->getType());
                                                        msg.setD1(sd->getNum1());
                                                        msg.setD2(sd->getNum2());
                                                        msg.setD3(sd->getNum3());
                                                        msg.setD4(sd->getOutType());
                                                        msg.setDirection(sd->getDirection());
                                                        msg.setType(13);
                                                        msg.setComment(tr("Ком. упр. не выполнена"));
                                                        msg.setParams(sd->makeJson());
                                                        DataBaseManager::insertJourMsg_wS(msg);
                                                        GraphTerminal::sendAbonentEventsAndStates(sd, msg);
                                                    }
                                                    if(10 != sd->getPublishedState()) {
                                                        sd->setPublishedState(13);
                                                        sd->updDoubl();
                                                    }
        //                                            MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor();
        //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                                });
    }

    std::function<void()> rejectOpen([un = getUnReciverSdBlIp()](){
//                                            if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
//                                                JourEntity msg;
//                                                msg.setObject(un->getName());
//                                                msg.setObjecttype(un->getType());
//                                                msg.setD1(un->getNum1());
//                                                msg.setD2(un->getNum2());
//                                                msg.setD3(un->getNum3());
//                                                msg.setD4(un->getOutType());
//                                                msg.setDirection(un->getDirection());
//                                                msg.setType(13);
//                                                msg.setComment(tr("Ком. упр. не выполнена"));
//                                                DataBaseManager::insertJourMsg_wS(msg);
//                                                GraphTerminal::sendAbonentEventsAndStates(un, msg);
//                                            }
//                                            un->setPublishedState(13);
//                                            un->updDoubl();
//                                            MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor();
////                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                        });

    std::function<void()> rejectLock([un = getUnReciverSdBlIp()](){
//                                            if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
//                                                JourEntity msg;
//                                                msg.setObject(un->getName());
//                                                msg.setObjecttype(un->getType());
//                                                msg.setD1(un->getNum1());
//                                                msg.setD2(un->getNum2());
//                                                msg.setD3(un->getNum3());
//                                                msg.setD4(un->getOutType());
//                                                msg.setDirection(un->getDirection());
//                                                msg.setType(13);
//                                                msg.setComment(tr("Ком. упр. не выполнена"));
//                                                DataBaseManager::insertJourMsg_wS(msg);
//                                                GraphTerminal::sendAbonentEventsAndStates(un, msg);
//                                            }
//                                            un->setPublishedState(13);
//                                            un->updDoubl();
//                                            MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor();
////                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                        });


    int sdIsAlarm = -1;
    int iuIsOff = -1;
    int sdIsNorm = -1;
    int iuIsOn = -1;

    if(TypeUnitNodeEnum::IU_BL_IP == getUnReciverIuBlIp()->getType()
    && TypeUnitNodeEnum::SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        sdIsAlarm = getUnReciverSdBlIp()->swpSDBLIPType0x41().isAlarm();
        iuIsOff = getUnReciverIuBlIp()->swpIUBLIPType0x41().isOff();
        sdIsNorm = getUnReciverSdBlIp()->swpSDBLIPType0x41().isNorm();
        iuIsOn = getUnReciverIuBlIp()->swpIUBLIPType0x41().isOn();
    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == getUnReciverIuBlIp()->getType()
           && TypeUnitNodeEnum::SSOI_SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        sdIsAlarm = getUnReciverSdBlIp()->swpSSOISDBLIPType0x41().isInAlarm();
        iuIsOff = getUnReciverIuBlIp()->swpSSOIIUBLIPType0x41().isOff();
        sdIsNorm = getUnReciverSdBlIp()->swpSSOISDBLIPType0x41().isInNorm();
        iuIsOn = getUnReciverIuBlIp()->swpSSOIIUBLIPType0x41().isOn();
    }

    if(TypeUnitNodeEnum::IU_BL_IP == getUnReciverIuBlIp()->getType()
    && TypeUnitNodeEnum::SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        if(1 == sdIsAlarm
        && 1 == iuIsOff) { //Открыто
//            qDebug() << "LockRequester::init 1";
            //Открыто
            setInitVarianrt(1);
            setTimeIntervalWaiteFirst(30'000);
            setTimeIntervalWaiteSecond(0);
            setTimeIntervalRequest(500);
            setManagerFirstMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOn0x23));
            getManagerFirstMsg()->setReject(rejectLock);

            setUpdateStateConditionReactor(updateStateConditionReactorNeedClose);
        } else if(1 == sdIsNorm
               && 1 == iuIsOn) { //Закрыто
//            qDebug() << "LockRequester::init 2";
            //Закрыто
            setInitVarianrt(2);
            setTimeIntervalWaiteFirst(30'000);
            setTimeIntervalWaiteSecond(0);
            setTimeIntervalRequest(500);
            setManagerFirstMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOff0x23));
            getManagerFirstMsg()->setReject(rejectOpen);

            setUpdateStateConditionReactor(updateStateConditionReactorNeedOpen);
        } else if(1 == sdIsAlarm
               && 1 == iuIsOn) { //Открыто ключом
//            qDebug() << "LockRequester::init 3";
            //Открыто ключом
            setInitVarianrt(3);
            setTimeIntervalWaiteFirst(30'000);
            setTimeIntervalWaiteSecond(30'000);
            setTimeIntervalRequest(500);
            setTimeIntervalPauseFromFirstToSecond(30'000);
//            setTimeIntervalPauseFromSecondToEnd(30'000);
            setManagerFirstMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOff0x23));
            getManagerFirstMsg()->setReject(rejectLock);
            setManagerSecondMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOn0x23));
            getManagerSecondMsg()->setReject(rejectLock);

            setUpdateStateConditionReactor(updateStateConditionReactorNeedClose);
        } else if(1 == sdIsNorm
               && 1 == iuIsOff) { //Закрыто ключом
//            qDebug() << "LockRequester::init 4";
            //Закрыто ключом
            setInitVarianrt(4);
            setTimeIntervalWaiteFirst(30'000);
            setTimeIntervalWaiteSecond(30'000);
            setTimeIntervalRequest(500);
            setTimeIntervalPauseFromFirstToSecond(30'000);
//            setTimeIntervalPauseFromSecondToEnd(30'000);
            setManagerFirstMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOn0x23));
            getManagerFirstMsg()->setReject(rejectOpen);
            setManagerSecondMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOff0x23));
            getManagerSecondMsg()->setReject(rejectOpen);

            setUpdateStateConditionReactor(updateStateConditionReactorNeedOpen);
        }
    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == getUnReciverIuBlIp()->getType()
           && TypeUnitNodeEnum::SSOI_SD_BL_IP == getUnReciverSdBlIp()->getType()) {
        if(1 == sdIsAlarm
        && 1 == iuIsOn) { //Открыто
//            qDebug() << "LockRequester::init 1";
            //Открыто
            setInitVarianrt(1);
            setTimeIntervalWaiteFirst(50'000);
            setTimeIntervalWaiteSecond(0);
            setTimeIntervalRequest(500);
            setManagerFirstMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOff0x23));
            getManagerFirstMsg()->setReject(rejectLock);

            setUpdateStateConditionReactor(updateStateConditionReactorNeedClose);
        } else if(1 == sdIsNorm
               && 1 == iuIsOff) { //Закрыто
//            qDebug() << "LockRequester::init 2";
            //Закрыто
            setInitVarianrt(2);
            setTimeIntervalWaiteFirst(50'000);
            setTimeIntervalWaiteSecond(0);
            setTimeIntervalRequest(500);
            setManagerFirstMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOn0x23));
            getManagerFirstMsg()->setReject(rejectOpen);

            setUpdateStateConditionReactor(updateStateConditionReactorNeedOpen);
        } else if(1 == sdIsAlarm
               && 1 == iuIsOff) { //Открыто ключом
//            qDebug() << "LockRequester::init 3";
            //Открыто ключом
            setInitVarianrt(3);
            setTimeIntervalWaiteFirst(50'000);
            setTimeIntervalWaiteSecond(50'000);
            setTimeIntervalRequest(500);
            setTimeIntervalPauseFromFirstToSecond(50'000);
//            setTimeIntervalPauseFromSecondToEnd(30'000);
            setManagerFirstMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOn0x23));
            getManagerFirstMsg()->setReject(rejectLock);
            setManagerSecondMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOff0x23));
            getManagerSecondMsg()->setReject(rejectLock);

            setUpdateStateConditionReactor(updateStateConditionReactorNeedClose);
        } else if(1 == sdIsNorm
               && 1 == iuIsOn) { //Закрыто ключом
//            qDebug() << "LockRequester::init 4";
            //Закрыто ключом
            setInitVarianrt(4);
            setTimeIntervalWaiteFirst(50'000);
            setTimeIntervalWaiteSecond(50'000);
            setTimeIntervalRequest(500);
            setTimeIntervalPauseFromFirstToSecond(50'000);
//            setTimeIntervalPauseFromSecondToEnd(30'000);
            setManagerFirstMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOff0x23));
            getManagerFirstMsg()->setReject(rejectOpen);
            setManagerSecondMsg(QSharedPointer<ManagerSingleMsg>::create(getUnReciverIuBlIp(), DataQueueItem::makeOn0x23));
            getManagerSecondMsg()->setReject(rejectOpen);

            setUpdateStateConditionReactor(updateStateConditionReactorNeedOpen);
        }
    }



    setMaxBeatCount(5);

    connect(this, SIGNAL(importantBeatStatus()), &SignalSlotCommutator::instance(), SLOT(emitEndLockWait()));
}
