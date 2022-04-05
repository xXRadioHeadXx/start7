
//Немного о коде в этом классе:
//    Если в некоторый момент времени энтропия замкнутой системы отлична от максимальной,
//    то в последующие моменты энтропия не убывает — увеличивfается
//    или в предельном случае остается постоянной.
//    Закон не имеет физической подоплёки, а исключительно математическую,
//    то есть теоретически он может быть нарушен, но вероятность этого события настолько мала,
//    что я плачу и пишу это дальше.

#include "PortManager.h"

#include <QVector>
#include "ShedulerDK.h"
//#include <QDebug>
#include "SignalSlotCommutator.h"

#include "PortFactory.h"
#include "Port.h"
#include "DataQueueItem.h"
#include "Utils.h"
#include "ServerSettingUtils.h"
#include "StatusConnectRequester.h"
#include "LockWaiter.h"
#include "global.h"
#include "MultiUNStatusConnectRequester.h"
#include "IniFileService.h"
#include "ManagerSingleMsg.h"
#include "MessageBoxServer.h"
#include <QQueue>
#include <QTextCodec>
#include "TopologyService.h"
#include "TypeUnitNode.h"
#include "SoundAdjuster.h"
#include "ProcessDKWaiter.h"
//#include "UnitNodeFactory.h"

#include "DataBaseManager.h"
#include "UnitNode.h"
#include "Port.h"
#include "DataQueueItem.h"
#include "ConfirmationAdmissionWaiter.h"
#include "OnOffIUWaiter.h"
#include "GraphTerminal.h"
#include "SimpleIni.h"

#include "../handlerstateword/31/HandlerStateWord0x31.h"
#include "../handlerstateword/32/HandlerStateWord0x32.h"
#include "../handlerstateword/33/HandlerStateWord0x33.h"
#include "../handlerstateword/34/HandlerStateWord0x34.h"
#include "../handlerstateword/41/HandlerStateWord0x41.h"
#include "../handlerstateword/42/HandlerStateWord0x42.h"
#include "../handlerstateword/HandlerStateWordAbstract.h"
//#include "swpblip/SWPBLIPType0x41.h"
#include "swprlm/SWPRLMType0x31.h"
#include "swprlmc/SWPRLMCType0x31.h"
//#include "swpblip/SWPSDBLIPType0x42.h"
#include "swpblip/SWPSDBLIPType0x41.h"
#include "swpblip/SWPIUBLIPType0x41.h"
#include "swptg/SWPTGType0x31.h"
//#include "swptg/SWPTGType0x34.h"
#include "swptg/SWPTGType0x33.h"
#include "swptg/SWPTGSubType0x33.h"
#include "swptg/SWPTGType0x32.h"
#include "swptg/SWPTGSubType0x32.h"
//#include "swpssoiblip/SWPSSOIBLIPType0x41.h"
#include "swpssoiblip/SWPSSOISDBLIPType0x41.h"
#include "swpssoiblip/SWPSSOIIUBLIPType0x41.h"
//#include "swpssoiblip/SWPSSOISDBLIPType0x42.h"
//#include "swpt4k/SWPT4KBODType0x32.h"
//#include "swpt4k/SWPT4KY4Type0x32.h"
//#include "swpt4k/SWPT4KDDType0x32.h"
//#include "swpt4k/SWPT4KDDCType0x32.h"
//#include "swpt4k/SWPT4KBODType0x33.h"
//#include "swpt4k/SWPT4KY4Type0x33.h"
//#include "swpt4k/SWPT4KDDType0x33.h"
//#include "swpt4k/SWPT4KDDCType0x33.h"
//#include "swpt4k/SWPT4KDDCFType0x33.h"
#include "ManagerSingleMsg.h"
#include "ContainerRequesters.h"

QSharedPointer<ShedulerDK> PortManager::shedulerDK;

PortManager::PortManager(QSharedPointer<DataBaseManager> dbm, QObject *parent) : QObject(parent), MAX_COUNT_PORTS(1), m_dbm(dbm)
{
//    m_portFactorys.reserve(1);
//    m_portFactorys.insert(Protocol::UDP, new PortFactory());

    m_udpPortsVector.reserve(MAX_COUNT_PORTS);

//    SignalSlotCommutator::setBlockInsNewJourMSG(true);
//    SignalSlotCommutator::setBlockUpdAllJourMSG(true);
//    SignalSlotCommutator::setBlockUpdJourMSG(true);

    connect(&SignalSlotCommutator::instance(), SIGNAL(requestOnOffCommand(bool,bool,QSharedPointer<UnitNode>,bool)), this, SLOT(requestOnOffCommand(bool,bool,QSharedPointer<UnitNode>,bool)));
    connect(&SignalSlotCommutator::instance(), SIGNAL(lockOpenCloseCommand(bool,QSharedPointer<UnitNode>,bool)), this, SLOT(lockOpenCloseCommand(bool,QSharedPointer<UnitNode>,bool)));
    connect(&SignalSlotCommutator::instance(), SIGNAL(autoOnOffIU(bool,bool,QSharedPointer<UnitNode>)),this, SLOT(requestAutoOnOffIUCommand(bool,bool,QSharedPointer<UnitNode>)));
    connect(&SignalSlotCommutator::instance(), SIGNAL(requestDK(bool,bool,QSharedPointer<UnitNode>)),this, SLOT(requestDK(bool,bool,QSharedPointer<UnitNode>)));
    connect(&SignalSlotCommutator::instance(), SIGNAL(resetFlags(QSharedPointer<UnitNode>)), this, SLOT(requestResetFlags(QSharedPointer<UnitNode>)));
    connect(&this->controlTimer, SIGNAL(timeout()), this, SLOT(controlSlot()));

    {
        CSimpleIniA ini;
        QString filePath = QCoreApplication::applicationDirPath() + "/rifx.ini";
        ini.LoadFile(filePath.toStdString().c_str());

        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

        auto autoDK = codec->toUnicode(ini.GetValue("RIF", "AutoDK"));

        if(0 != autoDK.toInt()) {
            shedulerDK = QSharedPointer<ShedulerDK>::create(QTime(autoDK.toInt(), 0), 300'000L);
            connect(shedulerDK.data(), &ShedulerDK::activated, this, [this](){requestDK(true, false);});
            shedulerDK->start();
        }
    }

    timerBlockJourMSG.singleShot(10'000, nullptr, [](){
        SignalSlotCommutator::setBlockInsNewJourMSG(false);
        SignalSlotCommutator::setBlockUpdAllJourMSG(false);
        SignalSlotCommutator::setBlockUpdJourMSG(false);
    });

    timerFirstWakeUp.singleShot(20'000, nullptr, [](){
        const auto& list = TopologyService::getSortedMetaRealUnitNodes();

        for(const auto& un : list) {
            if(10 != un->getPublishedState()
            || TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
            || TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
            || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType())
                continue;

            QSharedPointer<UnitNode> target;

            if(1 == un->getMetaEntity()) {
                for(const auto& dbl : as_const(un->getDoubles())) {
                    if(1 != dbl->getMetaEntity()) {
                        target = dbl;
                        break;
                    }
                }
            } else {
                target = un;
            }

            if(target.isNull())
                continue;

            if((target->getControl()
             || TypeUnitNodeEnum::IU_BL_IP == target->getType())
            && TypeUnitNodeEnum::Y4_T4K_M != target->getType()
            && TypeUnitNodeEnum::DD_T4K_M != target->getType()
            && TypeUnitNodeEnum::Y4_SOTA != target->getType()
            && TypeUnitNodeEnum::DD_SOTA != target->getType()) {
                JourEntity msg;
                msg.setObject(target->getName());
                msg.setType(10);
                msg.setObjecttype(target->getType());
                msg.setD1(target->getNum1());
                msg.setD2(target->getNum2());
                msg.setD3(target->getNum3());
                msg.setD4(target->getOutType());
                msg.setDirection(target->getDirection());
                msg.setComment(tr("Нет связи (начальное состояние)"));
                msg.setParams(target->makeJson());
                SignalSlotCommutator::emitInsNewJourMSG(msg);SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                GraphTerminal::sendAbonentEventsAndStates(target, msg);

                SoundAdjuster::playAlarm2();

                if(1 == un->getAlarmMsgOn() && 10 == msg.getType()) {
                    MessageBoxServer::showAttentionJourMsg(msg);
                }
            }

//            for(const auto& uncld : as_const(un->getListChilde())) {
//                unLostedConnect(uncld);
//            }

            for(auto scr : as_const(ContainerRequesters::getLsSCR())) {
                if(scr->getUnReciver() == un && BeatStatus::Unsuccessful == scr->getBeatStatus()) {
                    scr->startFirstRequest();
                    break;
                }
            }

            SignalSlotCommutator::emitUpdUN();

        }
    });
}

QList<AbstractPort *> PortManager::m_udpPortsVector = QList<AbstractPort *>();

GraphTerminal * PortManager::graphTerminal = nullptr;




PortManager::~PortManager()
{
//    for (PortFactory *factory : m_portFactorys) {
//        delete factory;
//    }

    for (const auto& port : as_const(m_udpPortsVector)) {
        delete port;
    }
    m_udpPortsVector.clear();
}

void PortManager::loadSettings() {
    m_udpPortsVector.clear();
    m_udpPortsVector = loadPortsUdpObj();

    for(auto& port : as_const(m_udpPortsVector)) {
        switch(port->getProtocol()) {
            case AbstractPort::UDP:
                Port::typeDefPort(port)->open();
                Port::typeDefPort(port)->setDbm(m_dbm);
                setupPort(port);
                break;
            case AbstractPort::TCP:
                break;                
            default:
                break;
        }
    }

    graphTerminal = loadPortsTcpGraphTerminal();
}

bool PortManager::open(const int index) {
    return m_udpPortsVector.at(index)->open();
}

void PortManager::close(const int index) {
    return m_udpPortsVector.at(index)->close();
}

QList<DataQueueItem> PortManager::readAll(const int index) {
    switch (m_udpPortsVector.at(index)->getProtocol()) {
        case AbstractPort::UDP:
            pushOverallReadQueue(Port::typeDefPort(m_udpPortsVector.at(index))->popLocalReadQueue());
            manageOverallReadQueue();
            break;
        default:
            break;
    }

    return getOverallReadQueue();
}

void PortManager::write() {
    write(popOverallWriteQueue());
}

void PortManager::write(const QList<DataQueueItem> &data) {
    for(const auto& itm : data) {
        write(itm);
    }
}

void PortManager::write(const DataQueueItem &data) {
    switch (m_udpPortsVector.at(data.portIndex())->getProtocol()) {
        case AbstractPort::UDP:
            Port::typeDefPort(m_udpPortsVector.at(data.portIndex()))->pushLocalWriteQueue(data);
            Port::typeDefPort(m_udpPortsVector.at(data.portIndex()))->write();
            break;
        default:
            break;
    }
}

bool PortManager::isOpen(const int index) {
    return m_udpPortsVector.at(index)->isOpen();
}

QList<AbstractPort *> PortManager::getUdpPortsVector()
{
    return m_udpPortsVector;
}






















void PortManager::setupPort(const int index) {
    setupPort(m_udpPortsVector.at(index));
}

void PortManager::setupPort(AbstractPort *port) {
    connect(port, SIGNAL(readyRead(int)), this, SLOT(readAll(int)), Qt::QueuedConnection);
    connect(port, SIGNAL(readyRead(int)), this, SIGNAL(readyRead(int)), Qt::QueuedConnection);
    connect(port, SIGNAL(portError(int)),   this, SIGNAL(portError(int)));
    connect(port, SIGNAL(portChanged(int)), this, SIGNAL(portChanged(int)));
}


bool PortManager::preparePort(QString ip, QString port, int index) {
    if(index + 1 < MAX_COUNT_PORTS)
        return false;

    Port::typeDefPort(m_udpPortsVector.at(index))->prepareUdpScoket(ip, port);
    return true;
}

QList<DataQueueItem> PortManager::getOverallReadQueue() const
{
    return overallReadQueue;
}

void PortManager::setOverallReadQueue(const QList<DataQueueItem> &value)
{
    overallReadQueue = value;
}

QList<DataQueueItem> PortManager::popOverallReadQueue() {
    const auto& result(getOverallReadQueue());
    for(const auto& itm : result) {
        overallReadQueue.removeOne(itm);
    }
    return result;
}
void PortManager::pushOverallReadQueue(const QList<DataQueueItem> &value) {
    overallReadQueue.append(value);
//    //qDebug() << "pushOverallReadQueue size(" << overallReadQueue.size() << ")";
}

void PortManager::pushOverallReadQueue(const DataQueueItem &value){
    overallReadQueue.append(value);
//    //qDebug() << "pushOverallReadQueue size(" << overallReadQueue.size() << ")";
}

QList<DataQueueItem> PortManager::getOverallWriteQueue() const
{
    return overallWriteQueue;
}

void PortManager::setOverallWriteQueue(const QList<DataQueueItem> &value)
{
    overallWriteQueue = value;
}

QList<DataQueueItem> PortManager::popOverallWriteQueue() {
    const auto& result(getOverallWriteQueue());
    for(const auto& itm : result) {
        overallWriteQueue.removeOne(itm);
    }
    return result;
}
void PortManager::pushOverallWriteQueue(const QList<DataQueueItem> &value) {
    overallWriteQueue.append(value);
}

void PortManager::pushOverallWriteQueue(const DataQueueItem &value){
    overallWriteQueue.append(value);
}

void PortManager::startStatusRequest(){
//    qDebug() << "PortManager::startStatusRequest() -->";
//    controlTimer.start(100);
    disconnect(&SignalSlotCommutator::instance(), SIGNAL(lostConnect(QSharedPointer<UnitNode> )), this, SLOT(unLostedConnect(QSharedPointer<UnitNode> )));

    ContainerRequesters::clearLsSCR();

    QSet<QSharedPointer<UnitNode> > tmpSet;
    for(const auto& un : as_const(TopologyService::getListTreeUnitNodes())) {
        if(TopologyService::getSetMetaRealUnitNodes().contains(un) &&
          (TypeUnitNodeEnum::BL_IP == un->getType()
        || TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
        || TypeUnitNodeEnum::RLM_C == un->getType()
        || TypeUnitNodeEnum::RLM_KRL == un->getType()
        || TypeUnitNodeEnum::TG_Base == un->getType()
        || TypeUnitNodeEnum::BOD_T4K_M == un->getType()
        || TypeUnitNodeEnum::BOD_SOTA == un->getType())) {
            tmpSet.insert(un);
        } else {
            auto rcvr = TopologyService::findReciver(un);
            if(TopologyService::getSetMetaRealUnitNodes().contains(un) &&
              (TypeUnitNodeEnum::BL_IP == rcvr->getType()
            || TypeUnitNodeEnum::SSOI_BL_IP == rcvr->getType()
            || TypeUnitNodeEnum::RLM_C == rcvr->getType()
            || TypeUnitNodeEnum::RLM_KRL == rcvr->getType()
            || TypeUnitNodeEnum::TG_Base == rcvr->getType()
            || TypeUnitNodeEnum::BOD_T4K_M == rcvr->getType()
            || TypeUnitNodeEnum::BOD_SOTA == un->getType())) {
                tmpSet.insert(rcvr);
            }
        }
    }

//    for(const QSharedPointer<UnitNode> &un : as_const(tmpSet)) {
//        qDebug() << "tmpSet -- " << un->toString();
//    }

    for(const auto& un : as_const(tmpSet)) {
        if(TypeUnitNodeEnum::BL_IP == un->getType()
        || TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
        || TypeUnitNodeEnum::RLM_C == un->getType()
        || TypeUnitNodeEnum::RLM_KRL == un->getType()
        || TypeUnitNodeEnum::TG_Base == un->getType()
        || TypeUnitNodeEnum::BOD_T4K_M == un->getType()
        || TypeUnitNodeEnum::BOD_SOTA == un->getType()) {
//            qDebug() << "PortManager::startStatusRequest() -- un" << un->toString();
            AbstractPort * ptrPort = nullptr;
            QPair<QString, QString> unIpPort(un->getUdpAdress(), QString::number(un->getUdpPort()));
            for(const auto& p : as_const(getUdpPortsVector())) {
                if(Port::typeDefPort(p)->getStIpPort().contains(unIpPort)) {
                    ptrPort = p;
//                    qDebug() << "PortManager::startStatusRequest() -- ptrPort " << ptrPort << ":" << unIpPort;
                    break;
                }
            }
            bool needMakeNew = true;
            for(const auto& scr : as_const(ContainerRequesters::getLsSCR())) {
                if(scr->getIpPort() == unIpPort) {
//                    qDebug() << "PortManager::startStatusRequest() -- match scr->getPtrPort("<<scr->getPtrPort()<<")";
                    const auto& requester = dynamic_cast<MultiUNStatusConnectRequester*>(scr.data());
                    if(nullptr != requester)
                        requester->addLsTrackedUN(un);
//                    qDebug() << "PortManager::startStatusRequest() -- match scr->getLsTrackedUN("<<scr->getLsTrackedUN()<<")";
                    needMakeNew = false;
                    break;
                }
            }
            if(needMakeNew) {
                auto tmpSCR = QSharedPointer<MultiUNStatusConnectRequester>::create(un);
                tmpSCR->init();
                tmpSCR->setPtrPort(ptrPort);
                ContainerRequesters::appLsSCR(tmpSCR);
                tmpSCR->addLsTrackedUN(un);
//                qDebug() << "PortManager::startStatusRequest() -- new scr->getPtrPort("<<tmpSCR->getPtrPort()<<")";
//                qDebug() << "PortManager::startStatusRequest() -- new scr->getLsTrackedUN("<<tmpSCR->getLsTrackedUN()<<")";
//                qDebug() << "PortManager::startStatusRequest() -- new lsSCR.size("<<lsSCR.size()<<")";
            }
        }
    }

    for(auto& scr : as_const(ContainerRequesters::getLsSCR())) {
        scr->startFirstRequest();
    }

    connect(&SignalSlotCommutator::instance(), SIGNAL(lostConnect(QSharedPointer<UnitNode>)), this, SLOT(unLostedConnect(QSharedPointer<UnitNode>)));
//    qDebug() << "PortManager::startStatusRequest() <--";
}

void PortManager::requestResetFlags(QSharedPointer<UnitNode>  target) {
    QSet<QSharedPointer<UnitNode> > lsTmp = TopologyService::getSetMetaRealUnitNodes();
    if(target.isNull()) {
        for(const auto& un : as_const(TopologyService::getSortedMetaRealUnitNodes())) {
            if(TypeUnitNodeEnum::BL_IP == un->getType()
            || TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
            || TypeUnitNodeEnum::RLM_C == un->getType()
            || TypeUnitNodeEnum::RLM_KRL == un->getType()
            || TypeUnitNodeEnum::TG_Base == un->getType()
            || TypeUnitNodeEnum::BOD_T4K_M == un->getType()
            || TypeUnitNodeEnum::BOD_SOTA == un->getType())
                lsTmp.insert(un);
        }
    } else if(!target.isNull()) {
        const auto& reciver = TopologyService::findReciver(target);
        lsTmp.insert(reciver);
    }

    for(const auto& un : lsTmp) {
        const auto& reciver = TopologyService::findReciver(un);
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(un,
                                                              DataQueueItem::makeResetFlags0x24);
        reciver->pushBackUniqManagerSingleMsg(msMsg);
    }
}


void PortManager::requestDK(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) {
    //
    QList<QSharedPointer<UnitNode>> lsTrgtUN;
    if(unTarget.isNull()) {
        QSet<QSharedPointer<UnitNode> > lsTmp = TopologyService::getSetMetaRealUnitNodes();
        for(const auto& un : lsTmp) {
            if(TypeUnitNodeEnum::BL_IP == un->getType()
            || TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
            || TypeUnitNodeEnum::RLM_C == un->getType()
            || TypeUnitNodeEnum::RLM_KRL == un->getType()
            || TypeUnitNodeEnum::TG_Base == un->getType()
            || TypeUnitNodeEnum::BOD_T4K_M == un->getType()
            || TypeUnitNodeEnum::BOD_SOTA == un->getType()
                    /* или датчик */) {
                if(isAuto && !fromAbonent && 10 == un->getPublishedState())
                    continue;
                lsTrgtUN.append(un);
                qDebug() << lsTrgtUN.constLast()->toString();
            }
        }
    } else if(!unTarget.isNull()) {
        QSharedPointer<UnitNode>  un = unTarget;
        lsTrgtUN.append(TopologyService::findReciver(un));
    }

    if(lsTrgtUN.isEmpty())
        return;

    if(unTarget.isNull()) {
        JourEntity msg;
        msg.setObject(tr("РИФ Общий"));
        QString comment;
        if(fromAbonent) {
            comment += tr("Удал. ком. ДК Послана ком. ДК");
            msg.setType(1133);
        } else {
            comment += tr("Послана ком. ДК");
            msg.setType(133);
        }
        if(isAuto)
            comment += tr(" (Авто)");
        msg.setComment(comment);
        if(!isAuto) {
            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(msg);
        }
    }

    for(QSharedPointer<UnitNode>  un : lsTrgtUN) {
        QPair<QString, QString> tmpPair(un->getUdpAdress(), QVariant(un->getUdpPort()).toString());
        for(const auto& pt : as_const(m_udpPortsVector)) {
            if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {

                auto tmpPDKW = QSharedPointer<ProcessDKWaiter>::create(isAuto, fromAbonent, un);
                tmpPDKW->init();
                ContainerRequesters::appLsWaiter(tmpPDKW);
//                tmpPDKW->startFirstRequest();
                break;
            }
        }
        if(unTarget.isNull() && !un->getName().isEmpty()/* && un->getControl()*/) {
            auto tmpUN = un;
            if(1 == tmpUN->getMetaEntity()) {
                for(const auto& chld : as_const(tmpUN->getListChilde())) {
                    if(1 != chld->getMetaEntity()) {
                        tmpUN = chld;
                        break;
                    }
                }

            }
            if(!tmpUN->getName().isEmpty() && 1 != tmpUN->getMetaEntity() && !unTarget.isNull()) {
                JourEntity msg;
                QString comment;
                if(fromAbonent) {
                    comment += tr("Удал. ком. ДК Послана ком. ДК");
                    msg.setType(1133);
                } else {
                    comment += tr("Послана ком. ДК");
                    msg.setType(133);
                }
                if(isAuto)
                    comment += tr(" (Авто)");
                msg.setComment(comment);
                msg.setObject(tmpUN->getName());
                msg.setObjecttype(tmpUN->getType());
                msg.setD1(tmpUN->getNum1());
                msg.setD2(tmpUN->getNum2());
                msg.setD3(tmpUN->getNum3());
                msg.setD4(tmpUN->getOutType());
                msg.setDirection(tmpUN->getDirection());
                msg.setParams(tmpUN->makeJson());

                if(!isAuto) {
                    SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                    GraphTerminal::sendAbonentEventsAndStates(msg);
                }
            }
        }
    }
    if(!unTarget.isNull()/* && selUN->getControl()*/) {
        JourEntity msg;
        msg.setObjecttype(unTarget->getType());
        msg.setD1(unTarget->getNum1());
        msg.setD2(unTarget->getNum2());
        msg.setD3(unTarget->getNum3());
        msg.setD4(unTarget->getOutType());
        msg.setDirection(unTarget->getDirection());

        QString comment;
        if(fromAbonent) {
            comment += tr("Удал. ком. ДК Послана ком. ДК");
            msg.setType(1133);
        } else {
            comment += tr("Послана ком. ДК");
            msg.setType(133);
        }
        if(isAuto)
            comment += tr(" (Авто)");
        msg.setComment(comment);
        msg.setObject(unTarget->getName());
        msg.setParams(unTarget->makeJson());
        if(!isAuto && !unTarget->getName().isEmpty() && 1 != unTarget->getMetaEntity()) {
            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(unTarget, msg);
        }
    }
}


void PortManager::requestAutoOnOffIUCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) {
    if(unTarget.isNull())
        return;

    if(TypeUnitNodeEnum::IU_BL_IP != unTarget->getType()
    && TypeUnitNodeEnum::SSOI_IU_BL_IP != unTarget->getType())
        return;

    QPair<QString, QString> tmpPair(unTarget->getUdpAdress(), QVariant(unTarget->getUdpPort()).toString());
    for(const auto& pt : as_const(m_udpPortsVector)) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {
            bool needJour = true;
            for(auto ar : as_const(ContainerRequesters::getLsWaiter())) {
                if((RequesterType::AutoOnOffWaiter == ar->getRequesterType())
                && (ar->getUnTarget() == unTarget
                 || ar->getUnTarget()->getDoubles().contains(unTarget))) {
                    ar->timerTripleStop();
                    ar->setBeatStatus(BeatStatus::Unsuccessful);

                    needJour = false;
//                        return;
                }
            }

            auto tmpOOIUW = QSharedPointer<OnOffIUWaiter>::create(isAuto, fromAbonent, unTarget);
            tmpOOIUW->init();
            unTarget->setWaitAutoCommand(isAuto);

            ContainerRequesters::appLsWaiter(tmpOOIUW);

            if(needJour) {
                JourEntity msg;
                msg.setObject(unTarget->getName());
                msg.setObjecttype(unTarget->getType());
                msg.setD1(unTarget->getNum1());
                msg.setD2(unTarget->getNum2());
                msg.setD3(unTarget->getNum3());
                msg.setD4(unTarget->getOutType());
                msg.setType(130);
                msg.setDirection(unTarget->getDirection());
                msg.setParams(unTarget->makeJson());
                QString comment;
                if(fromAbonent)
                    comment = tr("Удал. ком. Вкл");
                else
                    comment = tr("Послана ком. Вкл");
                if(isAuto)
                    comment += tr(" (Авто)");

                msg.setComment(comment);

                if(!unTarget->getName().isEmpty()
                && 1 != unTarget->getMetaEntity()) {
                    SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                    GraphTerminal::sendAbonentEventsAndStates(unTarget, msg);
                }
            }

            break;
        }
    }
}

void PortManager::lockOpenCloseCommand(QSharedPointer<UnitNode> selUN, bool value)
{
    lockOpenCloseCommand(false, selUN, value);
}

void PortManager::requestModeSensor(QSharedPointer<UnitNode> target) {

    std::function<void(const QSharedPointer<UnitNode>)> jour = std::function<void(const QSharedPointer<UnitNode>)>([](const QSharedPointer<UnitNode> target) {
        JourEntity msg;
        msg.setObject(target->getName());
        msg.setObjecttype(target->getType());
        msg.setD1(target->getNum1());
        msg.setD2(target->getNum2());
        msg.setD3(target->getNum3());
        msg.setD4(target->getOutType());
        msg.setDirection(target->getDirection());
        msg.setComment(QObject::tr("Запись настройки"));
        msg.setType(134);
        msg.setParams(target->makeJson());
        if((target->getControl() || TypeUnitNodeEnum::IU_BL_IP == target->getType()) && !target->getName().isEmpty() && 1 != target->getMetaEntity()) {
                            target->done=true;
            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg(msg);
            GraphTerminal::sendAbonentEventsAndStates(target, msg);
        }
    });



    auto reciver = TopologyService::findReciver(target);

    auto msMsg = QSharedPointer<ManagerSingleMsg>::create(target, DataQueueItem::makeMode0x20, jour);
    msMsg->setAccept([](){
                            MessageBoxServer::infoSensorParametersRecordedSuccessfully();
                         });
    auto reject = [un = target](){
        if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
            JourEntity msg;
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setD4(un->getOutType());
            msg.setDirection(un->getDirection());
            msg.setType(13);
            msg.setComment(tr("Ком. упр. не выполнена"));
            msg.setParams(un->makeJson());
            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(un, msg);
        }
        if(10 != un->getPublishedState()) {
            un->setPublishedState(13);
            un->updDoubl();
        }
        MessageBoxServer::infoErrorRecordingSensorParameters();
     };
    msMsg->setReject(reject);
    reciver->pushBackUniqManagerSingleMsg(msMsg);
    return;
}

void PortManager::controlSlot()
{
    bool res=true;
    for(const auto& un : as_const(TopologyService::getListTreeUnitNodes())) {

        if(un->getType()==TypeUnitNodeEnum::SD_BL_IP){
//        qDebug()<<"PortManager::controlSlot()" << un->getName() << un->done;

        if(un->done==false)
            res=false;
        }
    }

    qDebug()<<" ";
    if(res==true){
        qDebug()<<" ";
        qDebug()<<"Первичный опрос закончен !!!";
        qDebug()<<" ";
        controlTimer.stop();
        SignalSlotCommutator::emit_enable_updateListRecords();
        // enable_updateListRecords
    }else
    controlTimer.start(3000);
}

void PortManager::lockOpenCloseCommand(bool out, QSharedPointer<UnitNode> selUN, bool value)
{

    auto lw = QSharedPointer<LockWaiter>::create(selUN);

    lw->init();

    if(0 == lw->getInitVarianrt() || lw->getUnReciverIuBlIp().isNull() || lw->getUnReciverSdBlIp().isNull()) {
        return;
    }

    ContainerRequesters::appLsWaiter(lw);

    JourEntity msg;
    msg.setObject(selUN->getName());
    msg.setObjecttype(selUN->getType());
    msg.setD1(selUN->getNum1());
    msg.setD2(selUN->getNum2());
    msg.setD3(selUN->getNum3());
    msg.setD4(selUN->getOutType());
    msg.setDirection(selUN->getDirection());
    msg.setParams(selUN->makeJson());

    if(out) {
        msg.setComment(tr("Удал. ком. ") + (value ? tr("Открыть") : tr("Закрыть")));
        msg.setType((value ? 1004 : 1003));
    } else {
        msg.setType((value ? 150 : 151));
        msg.setComment(tr("Послана ком. ") + (value ? tr("Открыть") : tr("Закрыть")));
    }
    if(!selUN->getName().isEmpty() && 1 != selUN->getMetaEntity()) {
        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
        GraphTerminal::sendAbonentEventsAndStates(selUN, msg);
    }

    SignalSlotCommutator::emitStartLockWait(lw->getTimeIntervalWaiteFirst() + lw->getTimeIntervalWaiteSecond(), 0);
    lw->startFirstRequest();

}

void PortManager::requestOnOffCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget, const bool onOffValue) {
    QSharedPointer<UnitNode>  target = unTarget;

    if(TypeUnitNodeEnum::SSOI_SD_BL_IP != target->getType() &&
       TypeUnitNodeEnum::SSOI_IU_BL_IP != target->getType() &&
       TypeUnitNodeEnum::SD_BL_IP != target->getType() &&
       TypeUnitNodeEnum::IU_BL_IP != target->getType() &&
       TypeUnitNodeEnum::RLM_C != target->getType() &&
       TypeUnitNodeEnum::RLM_KRL != target->getType())
        return; // с этим типом устройств не работаем

    // ищем устройство в списке мета и реальных устройств -->
    target = TopologyService::getMetaRealUnitNodes(target);
    // ищем устройство в списке мета и реальных устройств <--

    // value true - Вкл. Оставляем работать шедулер (реквестер) автовыключения/автовыключения -->
    if(!onOffValue) {
        if(TypeUnitNodeEnum::IU_BL_IP == target->getType() || TypeUnitNodeEnum::SSOI_IU_BL_IP == target->getType()) { // Прерываем работу если это было ИУ
//            auto reciverIU = TopologyService::findReciver(selUN);
            for(auto ar : as_const(ContainerRequesters::getLsWaiter())) {
                if((RequesterType::AutoOnOffWaiter == ar->getRequesterType()) &&
//                   (ar->getUnReciver() == reciverIU) &&
                   (ar->getUnTarget() == target || ar->getUnTarget()->getDoubles().contains(target))) {
                    ar->timerTripleStop();
                    ar->setBeatStatus(BeatStatus::Unsuccessful);
                }
            }
        }
    }
    // value true - Вкл. Оставляем работать шедулер (реквестер) автовыключения/автовыключения <--

    std::function<QByteArray(const QSharedPointer<UnitNode>)> maker;

    if(TypeUnitNodeEnum::SD_BL_IP == target->getType() && onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOn0x20);
    } else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == target->getType() && onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOn0x20);
    } else if(TypeUnitNodeEnum::IU_BL_IP == target->getType() && onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOn0x23);
    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == target->getType() && onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOn0x23);
    } else if((TypeUnitNodeEnum::RLM_C == target->getType() || TypeUnitNodeEnum::RLM_KRL == target->getType()) && onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOn0x26);
    } else if(TypeUnitNodeEnum::SD_BL_IP == target->getType() && !onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOff0x20);
    } else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == target->getType() && !onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOff0x20);
    } else if(TypeUnitNodeEnum::IU_BL_IP == target->getType() && !onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOff0x23);
    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == target->getType() && !onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOff0x23);
    } else if((TypeUnitNodeEnum::RLM_C == target->getType() || TypeUnitNodeEnum::RLM_KRL == target->getType()) && !onOffValue) {
        maker = std::function<QByteArray(const QSharedPointer<UnitNode>)>(DataQueueItem::makeOff0x25);
    }

    std::function<void(const QSharedPointer<UnitNode>)> jour = std::function<void(const QSharedPointer<UnitNode>)>([isAuto = isAuto, fromAbonent = fromAbonent, onOffValue = onOffValue](const QSharedPointer<UnitNode> target) {
            JourEntity msg;
            msg.setObject(target->getName());
            msg.setObjecttype(target->getType());
            msg.setD1(target->getNum1());
            msg.setD2(target->getNum2());
            msg.setD3(target->getNum3());
            msg.setD4(target->getOutType());
            msg.setDirection(target->getDirection());
            msg.setParams(target->makeJson());

            QString comment;
            if(fromAbonent) {
                comment = tr("Удал. ком. ") + (onOffValue ? tr("Вкл") : tr("Выкл"));
                msg.setType((onOffValue ? 1'000 : 1'001));
            } else {
                comment = tr("Послана ком. ") + (onOffValue ? tr("Вкл") : tr("Выкл"));
                msg.setType((onOffValue ? 130 : 131));
            }
            if(isAuto)
                comment += tr(" (Авто)");

            msg.setComment(comment);

            if(!target->getName().isEmpty() && 1 != target->getMetaEntity()) {
                SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                GraphTerminal::sendAbonentEventsAndStates(target, msg);
            }
    });

    auto reject = [un = target, isAuto = isAuto, fromAbonent = fromAbonent](){
        if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
            JourEntity msg;
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setD4(un->getOutType());
            msg.setDirection(un->getDirection());
            msg.setType(13);
            msg.setComment(tr("Ком. упр. не выполнена"));
            msg.setParams(un->makeJson());
            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(un, msg);
        }
        if(10 != un->getPublishedState()) {
            un->setPublishedState(13);
            un->updDoubl();
        }
        if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
            MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
        }
    };

    std::function<void()> updateStateConditionReactor;
    if (TypeUnitNodeEnum::SSOI_SD_BL_IP == target->getType()) {
        updateStateConditionReactor = [un = target, isAuto = isAuto, fromAbonent = fromAbonent, onOff = onOffValue](){
                                                    const auto& swpSD = un->swpSSOISDBLIPType0x41();
                                                    if(1 == swpSD.isOff() && !onOff) // выкл
                                                    {
                                                        return;
                                                    } else if(1 == swpSD.isOn() && onOff) // вкл
                                                    {
                                                        return;
                                                    }
                                                    if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                                                        JourEntity msg;
                                                        msg.setObject(un->getName());
                                                        msg.setObjecttype(un->getType());
                                                        msg.setD1(un->getNum1());
                                                        msg.setD2(un->getNum2());
                                                        msg.setD3(un->getNum3());
                                                        msg.setD4(un->getOutType());
                                                        msg.setDirection(un->getDirection());
                                                        msg.setType(13);
                                                        msg.setComment(tr("Ком. упр. не выполнена"));
                                                        msg.setParams(un->makeJson());
                                                        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                                                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                                                    }
                                                    if(10 != un->getPublishedState()) {
                                                        un->setPublishedState(13);
                                                        un->updDoubl();
                                                    }
                                                    if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                        MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                                    }
        //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                                };
    } else if (TypeUnitNodeEnum::SSOI_IU_BL_IP == target->getType()) {
        updateStateConditionReactor = [un = target, isAuto = isAuto, fromAbonent = fromAbonent, onOff = onOffValue](){
                                                    const auto& swpIU = un->swpSSOIIUBLIPType0x41();
                                                    if(1 == swpIU.isOff() && !onOff) // выкл
                                                    {
                                                        return;
                                                    } else if(1 == swpIU.isOn() && onOff) // вкл
                                                    {
                                                        return;
                                                    }
                                                    if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                                                        JourEntity msg;
                                                        msg.setObject(un->getName());
                                                        msg.setObjecttype(un->getType());
                                                        msg.setD1(un->getNum1());
                                                        msg.setD2(un->getNum2());
                                                        msg.setD3(un->getNum3());
                                                        msg.setD4(un->getOutType());
                                                        msg.setDirection(un->getDirection());
                                                        msg.setType(13);
                                                        msg.setComment(tr("Ком. упр. не выполнена"));
                                                        msg.setParams(un->makeJson());
                                                        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                                                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                                                    }
                                                    if(10 != un->getPublishedState()) {
                                                        un->setPublishedState(13);
                                                        un->updDoubl();
                                                    }
                                                    if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                        MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                                    }
        //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                                };
    } else if (TypeUnitNodeEnum::SD_BL_IP == target->getType()) {
        updateStateConditionReactor = [un = target, isAuto = isAuto, fromAbonent = fromAbonent, onOff = onOffValue](){
                                                    const auto& swpSD = un->swpSDBLIPType0x41();
                                                    if(1 == swpSD.isOff() && !onOff) // выкл
                                                    {
                                                        return;
                                                    } else if(1 == swpSD.isOn() && onOff) // вкл
                                                    {
                                                        return;
                                                    }
                                                    if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                                                        JourEntity msg;
                                                        msg.setObject(un->getName());
                                                        msg.setObjecttype(un->getType());
                                                        msg.setD1(un->getNum1());
                                                        msg.setD2(un->getNum2());
                                                        msg.setD3(un->getNum3());
                                                        msg.setD4(un->getOutType());
                                                        msg.setDirection(un->getDirection());
                                                        msg.setType(13);
                                                        msg.setComment(tr("Ком. упр. не выполнена"));
                                                        msg.setParams(un->makeJson());
                                                        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                                                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                                                    }
                                                    if(10 != un->getPublishedState()) {
                                                        un->setPublishedState(13);
                                                        un->updDoubl();
                                                    }
                                                    if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                        MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                                    }
        //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                                };
    } else if (TypeUnitNodeEnum::IU_BL_IP == target->getType()) {
        updateStateConditionReactor = [un = target, isAuto = isAuto, fromAbonent = fromAbonent, onOff = onOffValue](){
                                                    const auto& swpIU = un->swpIUBLIPType0x41();
                                                    if(1 == swpIU.isOff() && !onOff) // выкл
                                                    {
                                                        return;
                                                    } else if(1 == swpIU.isOn() && onOff) // вкл
                                                    {
                                                        return;
                                                    }
                                                    if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                                                        JourEntity msg;
                                                        msg.setObject(un->getName());
                                                        msg.setObjecttype(un->getType());
                                                        msg.setD1(un->getNum1());
                                                        msg.setD2(un->getNum2());
                                                        msg.setD3(un->getNum3());
                                                        msg.setD4(un->getOutType());
                                                        msg.setDirection(un->getDirection());
                                                        msg.setType(13);
                                                        msg.setComment(tr("Ком. упр. не выполнена"));
                                                        msg.setParams(un->makeJson());
                                                        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                                                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                                                    }
                                                    if(10 != un->getPublishedState()) {
                                                        un->setPublishedState(13);
                                                        un->updDoubl();
                                                    }
                                                    if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                        MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                                    }
        //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                                };
    } else if (TypeUnitNodeEnum::RLM_C == target->getType()) {
        updateStateConditionReactor = [un = target, isAuto = isAuto, fromAbonent = fromAbonent, onOff = onOffValue](){
                                                    const auto& swpRLMC = un->swpRLMCType0x31();
                                                    if(1 == swpRLMC.isOff() && !onOff) // выкл
                                                    {
                                                        return;
                                                    } else if(1 == swpRLMC.isOn() && onOff) // вкл
                                                    {
                                                        return;
                                                    }
                                                    if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                                                        JourEntity msg;
                                                        msg.setObject(un->getName());
                                                        msg.setObjecttype(un->getType());
                                                        msg.setD1(un->getNum1());
                                                        msg.setD2(un->getNum2());
                                                        msg.setD3(un->getNum3());
                                                        msg.setD4(un->getOutType());
                                                        msg.setDirection(un->getDirection());
                                                        msg.setType(13);
                                                        msg.setComment(tr("Ком. упр. не выполнена"));
                                                        msg.setParams(un->makeJson());
                                                        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                                                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                                                    }
                                                    if(10 != un->getPublishedState()) {
                                                        un->setPublishedState(13);
                                                        un->updDoubl();
                                                    }
                                                    if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                        MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                                    }
        //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                                };
    } else if (TypeUnitNodeEnum::RLM_KRL == target->getType()) {
        updateStateConditionReactor = [un = target, isAuto = isAuto, fromAbonent = fromAbonent, onOff = onOffValue](){
                                                    const auto& swpRLM = un->swpRLMType0x31();
                                                    if(1 == swpRLM.isOff() && !onOff) // выкл
                                                    {
                                                        return;
                                                    } else if(1 == swpRLM.isOn() && onOff) // вкл
                                                    {
                                                        return;
                                                    }
                                                    if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                                                        JourEntity msg;
                                                        msg.setObject(un->getName());
                                                        msg.setObjecttype(un->getType());
                                                        msg.setD1(un->getNum1());
                                                        msg.setD2(un->getNum2());
                                                        msg.setD3(un->getNum3());
                                                        msg.setD4(un->getOutType());
                                                        msg.setDirection(un->getDirection());
                                                        msg.setType(13);
                                                        msg.setComment(tr("Ком. упр. не выполнена"));
                                                        msg.setParams(un->makeJson());
                                                        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                                                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                                                    }
                                                    if(10 != un->getPublishedState()) {
                                                        un->setPublishedState(13);
                                                        un->updDoubl();
                                                    }
                                                    if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                        MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                                    }
        //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                                };
    }

    auto tmpCAW = QSharedPointer<ConfirmationAdmissionWaiter>::create(target);
    tmpCAW->init();

    auto msMgr = QSharedPointer<ManagerSingleMsg>::create(target, maker, jour);
    tmpCAW->setManagerFirstMsg(msMgr);
    tmpCAW->setUpdateStateConditionReactor(updateStateConditionReactor);
    msMgr->setReject(reject);
    target->setWaitAutoCommand(isAuto);
    target->updDoubl();
    ContainerRequesters::appLsWaiter(tmpCAW);
}

GraphTerminal * PortManager::loadPortsTcpGraphTerminal(QString fileName) {
    Q_UNUSED(fileName)
    int nPort = IniFileService::getValueBySectionKey("INTEGRATION", "Port", "0").toInt();

    if(-1 != nPort)
        return new GraphTerminal(nPort);

    return nullptr;
}

QList<AbstractPort *> PortManager::loadPortsUdpObj(QString fileName) {
    Q_UNUSED(fileName)
    QList<AbstractPort *> result;

    int cntTrItm = IniFileService::getValueBySectionKey("TREE", "Count", "0").toInt();

    //qDebug() << "cntTrItm" << cntTrItm;
    if(0 >= cntTrItm)
        return result;

    QSet<QPair<QString, QString> > stIpPort;
    QSet<QString> stPort;

    for(int index = 0; index < cntTrItm; index++)
    {
        QString strGroup("Obj_%1");
        strGroup = strGroup.arg(index + 1);

        int udpUse = IniFileService::getValueBySectionKey(strGroup, "UdpUse").toInt();
        QString udpAdress =IniFileService::getValueBySectionKey(strGroup, "UdpAdress");
        QString updPort = IniFileService::getValueBySectionKey(strGroup, "UpdPort");
        if (1 == udpUse && !udpAdress.isEmpty() && !updPort.isEmpty()){
            QPair<QString, QString> tmp(udpAdress, updPort);
            stIpPort.insert(tmp);
            stPort.insert(updPort);
        }
    }

    for(const auto& prt : as_const(stPort)) {
            result.append(PortFactory(AbstractPort::UDP).create(AbstractPort::UDP, result.size()));
        Port::typeDefPort(result.last())->setStrPort(prt);
        for(const auto& tmp : as_const(stIpPort)) {
            if(prt == tmp.second)
                Port::typeDefPort(result.last())->addToSetIpPort(tmp);
        }
    }


    return result;
}

void PortManager::procDK(QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous) {
    qDebug() << "DkStatus --> " << current->toString();
    if(current.isNull() || previous.isNull())
        return;

    QMap<int, QString> mapDKCiclStatus = {
        {0,"DKIgnore"},
        {1,"DKReady"},
        {2,"DKNorm"},
        {3,"DKWasAlarn"},
        {4,"DKWas"},
        {5,"DKDone"},
        {-1,"DKWrong"}
    };

    if(DKCiclStatus::DKIgnore != previous->getDkStatus() &&
       DKCiclStatus::DKWrong != previous->getDkStatus() &&
       DKCiclStatus::DKDone != previous->getDkStatus() &&
       current->getDkInvolved()) {
        int unCalcDkStatus = current->calcDKStatus();
        qDebug() << "DkStatus -- unCalcDkStatus " << mapDKCiclStatus.value(unCalcDkStatus);
        qDebug() << "DkStatus -- unDkStatus " << mapDKCiclStatus.value(current->getDkStatus());
        if(DKCiclStatus::DKReady == previous->getDkStatus() &&
                DKCiclStatus::DKNorm == unCalcDkStatus) {
            current->setDkStatus(DKCiclStatus::DKNorm);
        } else if((DKCiclStatus::DKNorm == previous->getDkStatus() || DKCiclStatus::DKReady == previous->getDkStatus())&&
                DKCiclStatus::DKWasAlarm == unCalcDkStatus) {
            current->setDkStatus(DKCiclStatus::DKWasAlarm);
        } else if(DKCiclStatus::DKWasAlarm == previous->getDkStatus() &&
                DKCiclStatus::DKNorm == unCalcDkStatus) {
            current->setDkStatus(DKCiclStatus::DKDone);
        } else if(DKCiclStatus::DKWasAlarm == previous->getDkStatus() &&
                DKCiclStatus::DKWas == unCalcDkStatus) {
            current->setDkStatus(DKCiclStatus::DKDone);
        } else if((DKCiclStatus::DKNorm == previous->getDkStatus() &&
                 DKCiclStatus::DKNorm == unCalcDkStatus) ||
                (DKCiclStatus::DKWasAlarm == previous->getDkStatus() &&
                 DKCiclStatus::DKWasAlarm == unCalcDkStatus)) {
            current->setDkStatus(previous->getDkStatus());
        } else {
            current->setDkStatus(DKCiclStatus::DKWrong);
        }
        current->updDoubl();
    }
    qDebug() << "DkStatus -- unNewDkStatus " << mapDKCiclStatus.value(current->getDkStatus());
    qDebug() << "DkStatus <--";
}


void PortManager::manageOverallReadQueue()
{
    const auto &tmpQueue = popOverallReadQueue();
    for (const auto &itm : tmpQueue) {
        QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
//        AbstractPort * pt = m_udpPortsVector.value(itm.portIndex(), nullptr);
        if(true /*DataQueueItem::isValideDirectionI(itm)*/) {
            uint8_t num1Sender = itm.data().at(2);
            uint8_t CMD = itm.data().at(4);
            QString hostSender = Utils::hostAddressToString(itm.address());
            switch (CMD) {
            case static_cast<uint8_t>(0x41): {
                for(auto scr : as_const(ContainerRequesters::getLsSCR())) {
                    if(scr->getIpPort() == tmpPair
                    && (TypeUnitNodeEnum::BL_IP == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::SSOI_BL_IP == static_cast<uint8_t>(scr->getUnReciver()->getType()))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
//                DataQueueItem request;
//                parcingStatusWord0x41(itm, request);

                HandlerStateWord0x41(itm).handl();
//
                break;
            }
            case static_cast<uint8_t>(0x42): {
                for(auto scr : as_const(ContainerRequesters::getLsSCR())) {
                    if(scr->getIpPort() == tmpPair
                    && (TypeUnitNodeEnum::BL_IP == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::SSOI_BL_IP == static_cast<uint8_t>(scr->getUnReciver()->getType()))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
                DataQueueItem request;
//                parcingStatusWord0x42(itm, request);
                HandlerStateWord0x42(itm).handl();

                break;
            }
            case static_cast<uint8_t>(0x31): {
                for(auto scr : as_const(ContainerRequesters::getLsSCR())) {
                    if(scr->getIpPort() == tmpPair &&
                       (TypeUnitNodeEnum::TG_Base == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::RLM_C == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::RLM_KRL == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::BOD_T4K_M == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::BOD_SOTA == static_cast<uint8_t>(scr->getUnReciver()->getType()))
                    && static_cast<uint8_t>(scr->getUnReciver()->getNum1()) == static_cast<uint8_t>(itm.data().at(2))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
//                DataQueueItem request;
//                parcingStatusWord0x31(itm, request);
                HandlerStateWord0x31(itm).handl();

                break;
            }
            case static_cast<uint8_t>(0x32): {
                for(auto scr : as_const(ContainerRequesters::getLsSCR())) {
                    if(scr->getIpPort() == tmpPair
                    && (TypeUnitNodeEnum::TG_Base == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::BOD_T4K_M == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::BOD_SOTA == static_cast<uint8_t>(scr->getUnReciver()->getType()))
                    && static_cast<uint8_t>(scr->getUnReciver()->getNum1()) == static_cast<uint8_t>(itm.data().at(2))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
//                DataQueueItem request;
//                parcingStatusWord0x32(itm, request);
                HandlerStateWord0x32(itm).handl();


                break;
            }
            case static_cast<uint8_t>(0x33): {
                for(auto scr : as_const(ContainerRequesters::getLsSCR())) {
                    if(scr->getIpPort() == tmpPair
                    && (TypeUnitNodeEnum::TG_Base == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::BOD_T4K_M == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::Y4_T4K_M == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::DD_T4K_M == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::BOD_SOTA == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::Y4_SOTA == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::DD_SOTA == static_cast<uint8_t>(scr->getUnReciver()->getType()))
                    && static_cast<uint8_t>(scr->getUnReciver()->getNum1()) == static_cast<uint8_t>(itm.data().at(2))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
//                DataQueueItem request;
//                parcingStatusWord0x33(itm, request);
                HandlerStateWord0x33(itm).handl();

                break;
            }
            case static_cast<uint8_t>(0x34): {
                for(auto scr : as_const(ContainerRequesters::getLsSCR())) {
                    if(scr->getIpPort() == tmpPair
                    && (TypeUnitNodeEnum::TG_Base == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::BOD_T4K_M == static_cast<uint8_t>(scr->getUnReciver()->getType())
                     || TypeUnitNodeEnum::BOD_SOTA == static_cast<uint8_t>(scr->getUnReciver()->getType()))
                    && static_cast<uint8_t>(scr->getUnReciver()->getNum1()) == static_cast<uint8_t>(itm.data().at(2))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
//                DataQueueItem request;
//                parcingStatusWord0x34(itm, request);
                HandlerStateWord0x34(itm).handl();

                break;
            }
            case static_cast<uint8_t>(0x30): {

//                qDebug() << "case static_cast<uint8_t>(0x30)";

                //find sender (local reciver)
                for(auto& sender : TopologyService::getSortedMetaRealUnitNodes()) {
                    if(sender->equale(hostSender, num1Sender)) {
                        const auto& msm = sender->takeFirstManagerSingleMsg();
                        if(!msm.isNull()) {
                            msm->callAccept();
                        }
                        sender->setNeedPostponeQueueMsg(sender->getListManagersSingleMsg().isEmpty()
                                                     || true);
                        continue;
                    }
                }

                auto sortLsWaiter = ContainerRequesters::getLsWaiter();
                if(!sortLsWaiter.isEmpty()) {
                    std::sort(sortLsWaiter.begin(), sortLsWaiter.end(), [](QSharedPointer<AbstractRequester> a, QSharedPointer<AbstractRequester> b) {
                        return a->getLastPushTime() > b->getLastPushTime();
                    });
                }


                for(auto ar : as_const(sortLsWaiter)) {
                    if(ar->getIpPort() == tmpPair ) {

                        if(BeatStatus::RequestStep1 == ar->getBeatStatus()) { // переводим в первое ожидание

                            if(!ar->getUnReciver().isNull() &&
                               RequesterType::DKWaiter == ar->getRequesterType() &&
                               static_cast<uint8_t>(ar->getUnReciver()->getNum1()) == static_cast<uint8_t>(itm.data().at(2))) {
                                for(auto  un : ar.dynamicCast<ProcessDKWaiter>()->getLsTrackedUN()) {
                                    un->setDkInvolved(true);
                                    if(TypeUnitNodeEnum::TG == un->getType() /* или датчик */) {
                                        if(DKCiclStatus::DKWrong == un->getDkStatus()) {
                                            un->setDkStatus(DKCiclStatus::DKWrong);
                                        } else if(DKCiclStatus::DKReady != un->getDkStatus()) {
                                            const auto& swp31 = un->swpTGType0x31();
                                            const auto& swp32 = un->swpTGType0x32().C(un->getNum2());
                                            const auto& swp33 = un->swpTGType0x33().C(un->getNum2());
                                            if(!swp31.isNull() && (swp32.cdate() < swp31.cdate() && swp33.cdate() < swp31.cdate())
                                            && (1 == swp31.isOn()
                                             || (1 == swp31.isOn()
                                              && 1 != swp31.isNorm())
                                             || (1 == swp31.isOn()
                                              && 1 == swp31.isOpened()
                                              && 1 == swp31.isWasOpened())
                                             || (1 == swp31.isAlarm()
                                              && 1 == swp31.isWasAlarm()))) {
                                                un->setDkStatus(DKCiclStatus::DKWrong);
                                            } else if(!swp32.isNull() && (swp31.cdate() < swp32.cdate() && swp33.cdate() < swp32.cdate())
                                                   && (1 != swp32.isNorm()
                                                    || 1 == swp32.isFault()
                                                    || 1 == swp32.isOpened()
                                                    || 1 == swp32.isAlarm())) {
                                                un->setDkStatus(DKCiclStatus::DKWrong);
                                            } else if(!swp33.isNull() && (swp31.cdate() < swp33.cdate() && swp32.cdate() < swp33.cdate())
                                                   && (1 != swp33.isNorm()
                                                    || 1 == swp33.isFault()
                                                    || 1 == swp33.isOpened()
                                                    || 1 == swp33.isAlarm())) {
                                                un->setDkStatus(DKCiclStatus::DKWrong);
                                            }
                                        } else {
                                            un->setDkStatus(DKCiclStatus::DKReady);
                                        }
                                    } else {
                                        un->setDkStatus(DKCiclStatus::DKReady);
                                    }
                                    un->updDoubl();
                                }
                            }

                            if(RequesterType::DKWaiter == ar->getRequesterType()) {
                                SignalSlotCommutator::emitStartDKWait(ar->getTimeIntervalWaiteFirst());
                                ar->startWaiteSecondRequest();
                            } else if(RequesterType::LockRequester == ar->getRequesterType()) {
                                ar->startWaiteSecondRequest();
                            } else {
                                ar->startWaiteSecondRequest();
                            }


                        } else if(BeatStatus::RequestStep2 == ar->getBeatStatus()) { // удаляем завершившихся и переводим во второе ожидание другие

                            finishDKWaiter(ar);
                            if(!ar->getUnTarget().isNull()
                            && 13 == ar->getUnTarget()->getPublishedState()
                            && !(TypeUnitNodeEnum::SD_BL_IP == ar->getUnTarget()->getType()
                              && 1 == ar->getUnTarget()->getBazalt())
                            && !(TypeUnitNodeEnum::SSOI_SD_BL_IP == ar->getUnTarget()->getType()
                              && 1 == ar->getUnTarget()->getBazalt())) {
                                ar->getUnTarget()->setPublishedState(0);
                                ar->getUnTarget()->updDoubl();
                            }
                            break;

                        } else if(BeatStatus::End == ar->getBeatStatus()) { // кончаем конценных, но такого не бывает

                            if(RequesterType::LockRequester == ar->getRequesterType()) {
                                SignalSlotCommutator::emitStopLockWait();
                            }

                            ContainerRequesters::removeLsWaiter(ar);
                            if(!ar->getUnTarget().isNull()
                            && 13 == ar->getUnTarget()->getPublishedState()
                            && !(TypeUnitNodeEnum::SD_BL_IP == ar->getUnTarget()->getType()
                              && 1 == ar->getUnTarget()->getBazalt())
                            && !(TypeUnitNodeEnum::SSOI_SD_BL_IP == ar->getUnTarget()->getType()
                              && 1 == ar->getUnTarget()->getBazalt())) {
                                ar->getUnTarget()->setPublishedState(0);
                                ar->getUnTarget()->updDoubl();
                            }
                            break;

                        } else if(BeatStatus::Unsuccessful == ar->getBeatStatus() || BeatStatus::Successful == ar->getBeatStatus()) { // точно пора удалять
                            ContainerRequesters::removeLsWaiter(ar);
                            if(!ar->getUnTarget().isNull()
                            && 13 == ar->getUnTarget()->getPublishedState()
                            && !(TypeUnitNodeEnum::SD_BL_IP == ar->getUnTarget()->getType()
                              && 1 == ar->getUnTarget()->getBazalt())
                            && !(TypeUnitNodeEnum::SSOI_SD_BL_IP == ar->getUnTarget()->getType()
                              && 1 == ar->getUnTarget()->getBazalt())) {
                                ar->getUnTarget()->setPublishedState(0);
                                ar->getUnTarget()->updDoubl();
                            }
                            break;
                        }

                        if(!ar->getUnTarget().isNull()
                        && 13 == ar->getUnTarget()->getPublishedState()
                        && !(TypeUnitNodeEnum::SD_BL_IP == ar->getUnTarget()->getType()
                          && 1 == ar->getUnTarget()->getBazalt())
                        && !(TypeUnitNodeEnum::SSOI_SD_BL_IP == ar->getUnTarget()->getType()
                          && 1 == ar->getUnTarget()->getBazalt())) {
                            ar->getUnTarget()->setPublishedState(0);
                            ar->getUnTarget()->updDoubl();
                        }

                    }
                }

                for(auto& sender : TopologyService::getSortedMetaRealUnitNodes()) {
                    if(sender->equale(hostSender, num1Sender)) {
                        auto reciver = TopologyService::findReciver(sender);
                        if((TypeUnitNodeEnum::BOD_T4K_M == reciver->getType()
                         || TypeUnitNodeEnum::BOD_SOTA == reciver->getType())
                        && 0x20 == reciver->getNeededStateWordType()) {
                            reciver->setDefaultNeededStateWordType(0x2E);
                            reciver->setNeededStateWordType(0x2E);
                            break;
                        }
                    }
                }

                break;
            }
            default:
                break;
            }

            bool keypass = true;
            for(auto ar : as_const(ContainerRequesters::getLsWaiter())) {
                if(BeatStatus::Unsuccessful == ar->getBeatStatus() || BeatStatus::Successful == ar->getBeatStatus()) {
                    ContainerRequesters::removeLsWaiter(ar); //
                } else if(true == keypass && BeatStatus::Start == ar->getBeatStatus()) {
                    keypass = false;
                    ar->startFirstRequest();
                }
            }
        }
    }
}

void PortManager::finishDKWaiter(QSharedPointer<AbstractRequester> ar) {
    if(RequesterType::DKWaiter == ar->getRequesterType()) {
        for(QSharedPointer<UnitNode>  un : ar.dynamicCast<ProcessDKWaiter>()->getLsTrackedUN()) {

            const auto& isAutoDK = un->getIsAutoDkInvolved();

            JourEntity msg;
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setD4(un->getOutType());
            msg.setDirection(un->getDirection());
            msg.setParams(un->makeJson());

            bool needSendEventsAndStates = false;
            if(DKCiclStatus::DKDone == un->getDkStatus()) {
                msg.setComment(tr("Ком. ДК выполнена"));
                msg.setType(3);
                if(!un->getName().isEmpty() && 1 != un->getMetaEntity() && !isAutoDK) {
                    SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                }
                needSendEventsAndStates = true;
            } else {
                QString comment = tr("Ком. ДК не выполнена");
                if(isAutoDK)
                    comment = tr("Ком. ДК (Авто) не выполнена");
                msg.setComment(comment);
                msg.setType(11);
                if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                    SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    SoundAdjuster::playAlarm2();
                }
            }
            un->setDkInvolved(false);
            un->setDkStatus(DKCiclStatus::DKIgnore);
            un->updDoubl();
            if(needSendEventsAndStates)
                GraphTerminal::sendAbonentEventsAndStates(un);
            TopologyService::systemUnitNodesSetDkInvolvedFalse();
            SignalSlotCommutator::emitUpdUN();
        }
//                                SignalSlotCommutator::getInstance()->emitStopDKWait();
//                                removeLsWaiter(ar);
    } else if(RequesterType::LockRequester == ar->getRequesterType()){

        if(RequesterType::LockRequester == ar->getRequesterType()) {
        }

        ar->startWaiteEndSecondWaite();
    }

    if(RequesterType::LockRequester != ar->getRequesterType()) {
        if(RequesterType::DKWaiter == ar->getRequesterType()) {
            SignalSlotCommutator::emitStopDKWait();
        }
        ContainerRequesters::removeLsWaiter(ar);
    }
}

void PortManager::unLostedConnect(QSharedPointer<UnitNode> un)
{
//    //qDebug() << "PortManager::unLostedConnect(" << un << ")";
    if(1 == un->isConnected()) {
        un->setStateWord(0x41u, StateWord());
        un->setStateWord(0x31u, StateWord());
        un->setStateWord(0x32u, StateWord());
        un->setStateWord(0x33u, StateWord());
        un->setStateWord(0x34u, StateWord());

        un->setPublishedState(10);
        if((un->getControl()
         || TypeUnitNodeEnum::IU_BL_IP == un->getType()
         || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType())
        && !un->getName().isEmpty()
        && 1 != un->getMetaEntity()
        && TypeUnitNodeEnum::Y4_T4K_M != un->getType()
        && TypeUnitNodeEnum::DD_T4K_M != un->getType()
        && TypeUnitNodeEnum::Y4_SOTA != un->getType()
        && TypeUnitNodeEnum::DD_SOTA != un->getType()) {
            JourEntity msg;
            msg.setObject(un->getName());
            msg.setType(10);
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setD4(un->getOutType());
            msg.setDirection(un->getDirection());
            msg.setComment(tr("Нет связи"));
            msg.setParams(un->makeJson());
            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(un, msg);

            if(20 == msg.getType()) {
                SoundAdjuster::playAlarm();
            } else if(10 == msg.getType() || 12 == msg.getType() || 21 == msg.getType()) {
                SoundAdjuster::playAlarm2();
            }

            if(1 == un->getAlarmMsgOn() && 10 == msg.getType()) {
                MessageBoxServer::showAttentionJourMsg(msg);
            }
        }

        un->updDoubl();
    }


    for(const auto& uncld : as_const(un->getListChilde())) {
        unLostedConnect(uncld);
    }

    for(auto scr : as_const(ContainerRequesters::getLsSCR())) {
        if(scr->getUnReciver() == un && BeatStatus::Unsuccessful == scr->getBeatStatus()) {
            scr->startFirstRequest();
            break;
        }
    }

    SignalSlotCommutator::emitUpdUN();

}
