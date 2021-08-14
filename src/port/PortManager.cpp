#include <QVector>
#include "ShedulerDK.h"
//#include <QDebug>
#include "SignalSlotCommutator.h"

#include "PortFactory.h"
#include "PortManager.h"
#include "Port.h"
#include "DataQueueItem.h"
#include "Utils.h"
#include "ServerSettingUtils.h"
#include "StatusConnectRequester.h"
#include "LockWaiter.h"
#include "global.h"
#include <QMessageBox>
#include "MultiUNStatusConnectRequester.h"
#include <QQueue>
#include <SoundAdjuster.h>
#include "ProcessDKWaiter.h"
#include "UnitNodeFactory.h"

#include "DataBaseManager.h"
#include "UnitNode.h"
#include "Port.h"
#include "DataQueueItem.h"
#include "ConfirmationAdmissionWaiter.h"
#include "OnOffIUWaiter.h"
#include "GraphTerminal.h"
#include "SimpleIni.h"

#include "SWPBLIPType0x41.h"
#include "SWPRLMType0x31.h"
#include "SWPRLMCType0x31.h"
#include "SWPSDBLIPType0x42.h"
#include "SWPSDBLIPType0x41.h"
#include "SWPIUBLIPType0x41.h"
#include "SWPTGType0x31.h"
#include "SWPTGType0x34.h"
#include "SWPTGType0x33.h"
#include "SWPTGSubType0x33.h"
#include "SWPTGType0x32.h"
#include "SWPTGSubType0x32.h"
#include "ManagerSingleMsg.h"

QSharedPointer<ShedulerDK> PortManager::shedulerDK;

PortManager::PortManager(QSharedPointer<DataBaseManager> dbm, QObject *parent) : QObject(parent), MAX_COUNT_PORTS(1), m_dbm(dbm)
{
//    m_portFactorys.reserve(1);
//    m_portFactorys.insert(Protocol::UDP, new PortFactory());

    m_udpPortsVector.reserve(MAX_COUNT_PORTS);

    connect(&SignalSlotCommutator::instance(), SIGNAL(requestOnOffCommand(bool, bool, QSharedPointer<UnitNode> , bool)), this, SLOT(requestOnOffCommand(bool, bool, QSharedPointer<UnitNode> , bool)));
    connect(&SignalSlotCommutator::instance(), SIGNAL(lockOpenCloseCommand(bool, QSharedPointer<UnitNode> , bool)), this, SLOT(lockOpenCloseCommand(bool, QSharedPointer<UnitNode> , bool)));
    connect(&SignalSlotCommutator::instance(), SIGNAL(autoOnOffIU(bool, bool, QSharedPointer<UnitNode> )), this, SLOT(requestAutoOnOffIUCommand(bool, bool, QSharedPointer<UnitNode> )));
    connect(&SignalSlotCommutator::instance(), SIGNAL(requestDK(bool, bool, QSharedPointer<UnitNode> )), this, SLOT(requestDK(bool, bool, QSharedPointer<UnitNode> )));
    connect(&SignalSlotCommutator::instance(), SIGNAL(alarmsReset(QSharedPointer<UnitNode> )), this, SLOT(requestAlarmReset(QSharedPointer<UnitNode> )));

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

    timerFirstWakeUp.singleShot(20'000, [](){
        QList<QSharedPointer<UnitNode>> list = ServerSettingUtils::sortMetaRealUnitNodes();

        for(const auto& un : qAsConst(list)) {
            if(10 != un->getPublishedState())
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

            if((target->getControl() || TypeUnitNode::IU_BL_IP == target->getType())) {
                JourEntity msg;
                msg.setObject(target->getName());
                msg.setType(10);
                msg.setObjecttype(target->getType());
                msg.setD1(target->getNum1());
                msg.setD2(target->getNum2());
                msg.setD3(target->getNum3());
                msg.setDirection(target->getDirection());
                msg.setComment(tr("Нет связи (начальное состояние)"));
                DataBaseManager::insertJourMsg_wS(msg);
                GraphTerminal::sendAbonentEventsAndStates(target, msg);

                SoundAdjuster::playAlarm2();
            }

//            for(const auto& uncld : as_const(un->getListChilde())) {
//                unLostedConnect(uncld);
//            }

            for(auto scr : as_const(getLsSCR())) {
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


QList<QSharedPointer<AbstractRequester> > PortManager::lsSCR = QList<QSharedPointer<AbstractRequester> >();

QList<QSharedPointer<AbstractRequester> > PortManager::lsWaiter = QList<QSharedPointer<AbstractRequester> >();

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

QList<QSharedPointer<AbstractRequester> > PortManager::getLsWaiter()
{
    return lsWaiter;
}

void PortManager::setLsWaiter(const QList<QSharedPointer<AbstractRequester> > &value)
{
    lsWaiter = value;
}

void PortManager::appLsWaiter(QSharedPointer<AbstractRequester> value) {
    if(value.isNull())
        return;

    if(value->isValid())
        lsWaiter.append(value);
}

void PortManager::prependLsWaiter(QSharedPointer<AbstractRequester> value) {
    if(value.isNull())
        return;

    if(value->isValid())
        lsWaiter.prepend(value);
}


void PortManager::removeLsWaiter(QSharedPointer<AbstractRequester> value) {

    value->timerTripleStop();
    lsWaiter.removeAll(value);
    value->setBeatStatus(BeatStatus::Unsuccessful);
}

void PortManager::clearLsWaiter()
{
    for(int i = 0, n = lsWaiter.size(); i < n; i++) {
        QSharedPointer<AbstractRequester> value = lsWaiter.at(i);
        value->timerTripleStop();
        value->setBeatStatus(BeatStatus::Unsuccessful);
    }
    lsWaiter.clear();
}

QList<QSharedPointer<AbstractRequester> > PortManager::getLsSCR()
{
    return lsSCR;
}

void PortManager::setLsSCR(const QList<QSharedPointer<AbstractRequester> > &value)
{
    lsSCR = value;
}

void PortManager::appLsSCR(QSharedPointer<AbstractRequester> value) {
    if(value.isNull())
        return;

    if(value->isValid())
        lsSCR.append(value);
}

void PortManager::prependLsSCR(QSharedPointer<AbstractRequester> value) {
    if(value.isNull())
        return;

    if(value->isValid())
        lsSCR.prepend(value);
}


void PortManager::removeLsSCR(QSharedPointer<AbstractRequester> value) {

    value->timerTripleStop();
    lsSCR.removeAll(value);
    value->setBeatStatus(BeatStatus::Unsuccessful);
}

void PortManager::clearLsSCR()
{
    for(int i = 0, n = lsSCR.size(); i < n; i++) {
        QSharedPointer<AbstractRequester>  value = lsSCR.at(i);
        value->timerTripleStop();
        value->setBeatStatus(BeatStatus::Unsuccessful);
    }
    lsSCR.clear();
}


void PortManager::setupPort(const int index) {
    setupPort(m_udpPortsVector.at(index));
}

void PortManager::setupPort(AbstractPort *port) {
    connect(port, SIGNAL(readyRead( int )), this, SLOT(readAll( int )), Qt::QueuedConnection);
    connect(port, SIGNAL(readyRead( int )), this, SIGNAL(readyRead( int )), Qt::QueuedConnection);
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
    disconnect(&SignalSlotCommutator::instance(), SIGNAL(lostConnect(QSharedPointer<UnitNode> )), this, SLOT(unLostedConnect(QSharedPointer<UnitNode> )));

    clearLsSCR();

    QSet<QSharedPointer<UnitNode> > tmpSet;
    for(const auto& un : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
        if(ServerSettingUtils::getSetMetaRealUnitNodes().contains(un) &&
          (TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::RLM_C == un->getType() ||
           TypeUnitNode::RLM_KRL == un->getType() ||
           TypeUnitNode::TG_Base == un->getType())) {
            tmpSet.insert(un);
        } else if(TypeUnitNode::SD_BL_IP == un->getType() ||
                  TypeUnitNode::IU_BL_IP == un->getType() ||
                  TypeUnitNode::TG == un->getType()) {
            if(!un->getParentUN().isNull() &&
               (TypeUnitNode::BL_IP == un->getParentUN()->getType() || TypeUnitNode::TG_Base == un->getParentUN()->getType()) &&
               ServerSettingUtils::getSetMetaRealUnitNodes().contains(un->getParentUN())) {
                tmpSet.insert(un->getParentUN());
            }
        }
    }

//    for(const QSharedPointer<UnitNode> &un : as_const(tmpSet)) {
//        qDebug() << "tmpSet -- " << un->toString();
//    }

    for(const auto& un : as_const(tmpSet)) {
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::RLM_C == un->getType() ||
           TypeUnitNode::RLM_KRL == un->getType() ||
           TypeUnitNode::TG_Base == un->getType()) {
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
            for(auto scr : as_const(lsSCR)) {
                if(scr->getIpPort() == unIpPort) {
//                    qDebug() << "PortManager::startStatusRequest() -- match scr->getPtrPort("<<scr->getPtrPort()<<")";
                    static_cast<MultiUNStatusConnectRequester*>(scr.data())->addLsTrackedUN(un);
//                    qDebug() << "PortManager::startStatusRequest() -- match scr->getLsTrackedUN("<<scr->getLsTrackedUN()<<")";
                    needMakeNew = false;
                    break;
                }
            }
            if(needMakeNew) {
                auto tmpSCR = QSharedPointer<MultiUNStatusConnectRequester>::create(un);
                tmpSCR->init();
                tmpSCR->setPtrPort(ptrPort);
                lsSCR.append(tmpSCR);
                tmpSCR->addLsTrackedUN(un);
//                qDebug() << "PortManager::startStatusRequest() -- new scr->getPtrPort("<<tmpSCR->getPtrPort()<<")";
//                qDebug() << "PortManager::startStatusRequest() -- new scr->getLsTrackedUN("<<tmpSCR->getLsTrackedUN()<<")";
//                qDebug() << "PortManager::startStatusRequest() -- new lsSCR.size("<<lsSCR.size()<<")";
            }
        }
    }

    for(auto& scr : as_const(getLsSCR())) {
        scr->startFirstRequest();
    }

    connect(&SignalSlotCommutator::instance(), SIGNAL(lostConnect(QSharedPointer<UnitNode> )), this, SLOT(unLostedConnect(QSharedPointer<UnitNode> )));
//    qDebug() << "PortManager::startStatusRequest() <--";
}

void PortManager::requestAlarmReset(QSharedPointer<UnitNode>  selUN) {
    if(selUN.isNull()) {
        QSet<QSharedPointer<UnitNode> > lsTmp = ServerSettingUtils::getSetMetaRealUnitNodes();
        for(const QSharedPointer<UnitNode>  &un : lsTmp) {
            if(TypeUnitNode::BL_IP == un->getType() ||
               TypeUnitNode::RLM_C == un->getType() ||
               TypeUnitNode::RLM_KRL == un->getType() ||
               TypeUnitNode::TG_Base == un->getType())
                selUN = un;
            if(!selUN.isNull()) {
                QPair<QString, QString> tmpPair(selUN->getUdpAdress(), QVariant(selUN->getUdpPort()).toString());
                for(const auto& pt : as_const(m_udpPortsVector)) {
                    if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {

                        auto tmpCAW = QSharedPointer<ConfirmationAdmissionWaiter>::create(selUN);
                        tmpCAW->init();
                        DataQueueItem itm = tmpCAW->getFirstMsg();
                        DataQueueItem::fillAlarmReset0x24(itm, selUN);

                        appLsWaiter(tmpCAW);
//                        tmpCAW->startFirstRequest();
                        break;
                    }
                }
            }
            selUN = nullptr;
        }
    } else {
        QSharedPointer<UnitNode>  un = selUN;
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::IU_BL_IP == un->getType() ||
           TypeUnitNode::SD_BL_IP == un->getType()) {
            while(TypeUnitNode::BL_IP != un->getType()) {
                un = un->getParentUN();
            }
        } else if(TypeUnitNode::TG == un->getType() ||
                  TypeUnitNode::TG_Base == un->getType()) {
            while(TypeUnitNode::TG_Base != un->getType()) {
                un = un->getParentUN();
            }
        }
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::RLM_C == un->getType() ||
           TypeUnitNode::RLM_KRL == un->getType() ||
           TypeUnitNode::TG_Base == un->getType()) {
            selUN = un;
            auto tmpCAW = QSharedPointer<ConfirmationAdmissionWaiter>::create(selUN);
            tmpCAW->init();
            DataQueueItem itm = tmpCAW->getFirstMsg();
            DataQueueItem::fillAlarmReset0x24(itm, selUN);
            tmpCAW->setFirstMsg(itm);
            appLsWaiter(tmpCAW);
//            tmpCAW->startFirstRequest();
        }
    }
    //    write();
}


void PortManager::requestDK(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) {
    //
    QList<QSharedPointer<UnitNode> > lsTrgtUN;
    if(unTarget.isNull()) {
        QSet<QSharedPointer<UnitNode> > lsTmp = ServerSettingUtils::getSetMetaRealUnitNodes();
        for(const QSharedPointer<UnitNode>  &un : lsTmp) {
            if(TypeUnitNode::BL_IP == un->getType() ||
               TypeUnitNode::RLM_C == un->getType() ||
               TypeUnitNode::RLM_KRL == un->getType() ||
               TypeUnitNode::TG_Base == un->getType()
                    /* или датчик */) {
                lsTrgtUN.append(un);
                qDebug() << lsTrgtUN.constLast()->toString();
            }
        }
    } else if(!unTarget.isNull()) {
        QSharedPointer<UnitNode>  un = unTarget;
        lsTrgtUN.append(UnitNode::findReciver(un));
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
            DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(msg);
        }
    }

    for(QSharedPointer<UnitNode>  un : lsTrgtUN) {
        QPair<QString, QString> tmpPair(un->getUdpAdress(), QVariant(un->getUdpPort()).toString());
        for(const auto& pt : as_const(m_udpPortsVector)) {
            if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {

                auto tmpPDKW = QSharedPointer<ProcessDKWaiter>::create(isAuto, un);
                tmpPDKW->init();
                appLsWaiter(tmpPDKW);
//                tmpPDKW->startFirstRequest();
                break;
            }
        }
        if(unTarget.isNull() && !un->getName().isEmpty()/* && un->getControl()*/) {
            auto tmpUN = un;
            if(1 == tmpUN->getMetaEntity()) {
                for(const auto &chld : as_const(tmpUN->getListChilde())) {
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
                msg.setDirection(tmpUN->getDirection());

                if(!isAuto) {
                    DataBaseManager::insertJourMsg_wS(msg);
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
        if(!isAuto && !unTarget->getName().isEmpty() && 1 != unTarget->getMetaEntity()) {
            DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(unTarget, msg);
        }
    }
}


void PortManager::requestAutoOnOffIUCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) {
    if(unTarget.isNull())
        return;

    if(TypeUnitNode::IU_BL_IP == unTarget->getType()) {
        QPair<QString, QString> tmpPair(unTarget->getUdpAdress(), QVariant(unTarget->getUdpPort()).toString());
        for(const auto& pt : as_const(m_udpPortsVector)) {
            if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {
                bool needJour = true;
                for(auto ar : as_const(getLsWaiter())) {
                    if((RequesterType::AutoOnOffWaiter == ar->getRequesterType()) && (ar->getUnTarget() == unTarget || ar->getUnTarget()->getDoubles().contains(unTarget))) {
                        ar->timerTripleStop();
                        ar->setBeatStatus(BeatStatus::Unsuccessful);

                        needJour = false;
//                        return;
                    }
                }

                auto tmpOOIUW = QSharedPointer<OnOffIUWaiter>::create(unTarget);
                tmpOOIUW->init();
                unTarget->setWaitAutoCommand(isAuto);
                appLsWaiter(tmpOOIUW);
//                tmpOOIUW->startFirstRequest();

                if(needJour) {
                    JourEntity msg;
                    msg.setObject(unTarget->getName());
                    msg.setObjecttype(unTarget->getType());
                    msg.setD1(unTarget->getNum1());
                    msg.setD2(unTarget->getNum2());
                    msg.setD3(unTarget->getNum3());
                    msg.setType(130);
                    msg.setDirection(unTarget->getDirection());
                    QString comment;
                    if(fromAbonent)
                        comment = tr("Удал. ком. Вкл");
                    else
                        comment = tr("Послана ком. Вкл");
                    if(isAuto)
                        comment += tr(" (Авто)");

                    msg.setComment(comment);

                    if(!unTarget->getName().isEmpty() && 1 != unTarget->getMetaEntity()) {
                        DataBaseManager::insertJourMsg_wS(msg);
                        GraphTerminal::sendAbonentEventsAndStates(unTarget, msg);
                    }
                }

                break;
            }
        }
    }
}

void PortManager::lockOpenCloseCommand(QSharedPointer<UnitNode> selUN, bool value)
{
    lockOpenCloseCommand(false, selUN, value);
}

void PortManager::requestModeSensor(QSharedPointer<UnitNode> un, QByteArray stateWord)
{
    if(un.isNull() || stateWord.isEmpty()) {
        return;
    }

    auto tmpCAW = QSharedPointer<ConfirmationAdmissionWaiter>::create(un);
    tmpCAW->init();

    DataQueueItem itm = tmpCAW->getFirstMsg();
    DataQueueItem::fillOnOff0x20(itm, un);
    auto data = itm.data();

    if(TypeUnitNode::RLM_C == un->getType()){
        data[4] = stateWord.at(2);
        data[5] = stateWord.at(3);
    } else if(TypeUnitNode::RLM_KRL == un->getType()){
        data[4] = stateWord.at(0);
    } else if(TypeUnitNode::TG == un->getType()){
        data = data.replace(4, 7, stateWord);
    }

    data.chop(1);
    data.append(Utils::getByteSumm(data)); //<CHKS>
    itm.setData(data);

    tmpCAW->setFirstMsg(itm);

    connect(tmpCAW.data(), &AbstractRequester::successful, [](){
        QMessageBox::information(nullptr,
                                 tr("Инфо"),
                                 tr("Параметры датчика записаны успешно!"),
                                 QMessageBox::Ok);
    });

    connect(tmpCAW.data(), &AbstractRequester::unsuccessful, [](){
        QMessageBox::warning(nullptr,
                             tr("Ошибка"),
                             tr("Ошибка записи параметров датчика!"),
                             QMessageBox::Ok);
    });

    appLsWaiter(tmpCAW);

    JourEntity msg;
    msg.setObject(un->getName());
    msg.setObjecttype(un->getType());
    msg.setD1(un->getNum1());
    msg.setD2(un->getNum2());
    msg.setD3(un->getNum3());
    msg.setDirection(un->getDirection());
    msg.setComment(QObject::tr("Запись настройки"));
    msg.setType(134);
    if((un->getControl() || TypeUnitNode::IU_BL_IP == un->getType()) && !un->getName().isEmpty() && 1 != un->getMetaEntity()) {
        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(un, msg);
    }
}

void PortManager::lockOpenCloseCommand(bool out, QSharedPointer<UnitNode> selUN, bool value)
{

    auto lw = QSharedPointer<LockWaiter>::create(selUN);

    lw->init();

    if(0 == lw->getInitVarianrt() || lw->getUnReciverIuBlIp().isNull() || lw->getUnReciverSdBlIp().isNull()) {
        return;
    }

    appLsWaiter(lw);

    JourEntity msg;
    msg.setObject(selUN->getName());
    msg.setObjecttype(selUN->getType());
    msg.setD1(selUN->getNum1());
    msg.setD2(selUN->getNum2());
    msg.setD3(selUN->getNum3());
    msg.setDirection(selUN->getDirection());

    if(out) {
        msg.setComment(tr("Удал. ком. ") + (value ? tr("Открыть") : tr("Закрыть")));
        msg.setType((value ? 1004 : 1003));
    } else {
        msg.setType((value ? 150 : 151));
        msg.setComment(tr("Послана ком. ") + (value ? tr("Открыть") : tr("Закрыть")));
    }
    if(!selUN->getName().isEmpty() && 1 != selUN->getMetaEntity()) {
        DataBaseManager::insertJourMsg_wS(msg);
        GraphTerminal::sendAbonentEventsAndStates(selUN, msg);
    }
    lw->startFirstRequest();

}


void PortManager::requestOnOffCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget, const bool onOffValue)
{
    QSharedPointer<UnitNode>  target = unTarget;

    if(TypeUnitNode::SD_BL_IP != target->getType() &&
       TypeUnitNode::IU_BL_IP != target->getType() &&
       TypeUnitNode::RLM_C != target->getType() &&
       TypeUnitNode::RLM_KRL != target->getType())
        return; // с этим типом устройств не работаем

    // ищем устройство в списке мета и реальных устройств -->
    if(!ServerSettingUtils::getSetMetaRealUnitNodes().contains(target)) {
        for(const auto& un : as_const(ServerSettingUtils::getSetMetaRealUnitNodes()))
            if(un->getDoubles().contains(target)) {
                target = un;
                break;
            }
    }
    // ищем устройство в списке мета и реальных устройств <--

    // value true - Вкл. Оставляем работать шедулер (реквестер) автовыключения/автовыключения -->
    if(!onOffValue) {
        if(TypeUnitNode::IU_BL_IP == target->getType()) { // Прерываем работу если это было ИУ
//            auto reciverIU = UnitNode::findReciver(selUN);
            for(auto ar : as_const(getLsWaiter())) {
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

    QSharedPointer<UnitNode>  reciver = UnitNode::findReciver(target);

    if(!reciver.isNull()) {

        if(TypeUnitNode::BL_IP == reciver->getType() && !target->getStateWord(0x41u).getByteWord().isEmpty()) {
            quint8 D1 = 0x00; // байт для БЛ
            quint8 mask = 0x00;
            if(TypeUnitNode::SD_BL_IP == target->getType()) {
                D1 = target->getStateWord(0x41u).getByteWord().at(3);
                mask = target->swpSDBLIPType0x41().mask();
            } else if(TypeUnitNode::IU_BL_IP == target->getType()) {
                D1 = target->getStateWord(0x41u).getByteWord().at(1) & 0x0F;
                mask = target->swpIUBLIPType0x41().mask();
            }

            if(onOffValue)
                D1 = D1 | mask;
            else if(!onOffValue)
                D1 = D1 & ~mask;

            auto tmpCAW = QSharedPointer<ConfirmationAdmissionWaiter>::create(reciver);
            tmpCAW->init();
            DataQueueItem itm = tmpCAW->getFirstMsg();
            QByteArray data;
            if(TypeUnitNode::SD_BL_IP == target->getType()) {
                DataQueueItem::fillOnOff0x20(itm, target);
                data = itm.data();
            } else if(TypeUnitNode::IU_BL_IP == target->getType()) {
                DataQueueItem::fillOnOff0x23(itm, target);
                data = itm.data();
            }
            data[4] = D1;
            data.chop(1);
            data.append(Utils::getByteSumm(data)); //<CHKS>
            itm.setData(data);
            tmpCAW->setFirstMsg(itm);
//            tmpCAW->setUnTarget(target);
            appLsWaiter(tmpCAW);
    //        tmpCAW->startFirstRequest();

        } else if(TypeUnitNode::RLM_C == reciver->getType() ||
                  TypeUnitNode::RLM_KRL == reciver->getType()) {
            auto tmpCAW = QSharedPointer<ConfirmationAdmissionWaiter>::create(reciver);
            tmpCAW->init();
//            tmpCAW->setUnTarget(target);
            DataQueueItem itm = tmpCAW->getFirstMsg();
            if(onOffValue)
                DataQueueItem::fillOn0x26(itm, reciver);
            else
                DataQueueItem::fillOff0x25(itm, reciver);
            tmpCAW->setFirstMsg(itm);
            unTarget->setWaitAutoCommand(isAuto);
            appLsWaiter(tmpCAW);
        }

        JourEntity msg;
        msg.setObject(unTarget->getName());
        msg.setObjecttype(unTarget->getType());
        msg.setD1(unTarget->getNum1());
        msg.setD2(unTarget->getNum2());
        msg.setD3(unTarget->getNum3());
        msg.setDirection(unTarget->getDirection());

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

        if(!unTarget->getName().isEmpty() && 1 != unTarget->getMetaEntity()) {
            DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(unTarget, msg);
        }
    }
}

GraphTerminal * PortManager::loadPortsTcpGraphTerminal(QString fileName) {
    Q_UNUSED(fileName)
    int nPort = ServerSettingUtils::getValueSettings("Port", "INTEGRATION", fileName).toInt();

    if(-1 != nPort)
        return new GraphTerminal(nPort);

    return nullptr;
}

QList<AbstractPort *> PortManager::loadPortsUdpObj(QString fileName) {
    QList<AbstractPort *> result;

    int cntTrItm = ServerSettingUtils::getValueSettings("Count", "TREE", fileName).toInt();

    //qDebug() << "cntTrItm" << cntTrItm;
    if(0 >= cntTrItm)
        return result;

    QSet<QPair<QString, QString> > stIpPort;
    QSet<QString> stPort;

    for(int index = 0; index < cntTrItm; index++)
    {
        QString strGroup("Obj_%1");
        strGroup = strGroup.arg(index + 1);

        int udpUse = ServerSettingUtils::getValueSettings("UdpUse", strGroup, fileName).toInt();
        QString udpAdress =ServerSettingUtils::getValueSettings("UdpAdress", strGroup, fileName).toString();
        QString updPort = ServerSettingUtils::getValueSettings("UpdPort", strGroup, fileName).toString();
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

bool PortManager::procUzoBLIPStatusWord0x41(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -->";
    if((TypeUnitNode::SD_BL_IP != currentUN->getType() && TypeUnitNode::IU_BL_IP != currentUN->getType())
    || 1 > currentUN->getNum2()
    || 4 < currentUN->getNum2()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(1) <--";
        return false;
    }


    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousCopyUNLockSdBlIp, previousCopyUNLockIuBlIp;
    QSharedPointer<UnitNode>  unLockSdBlIp, unLockIuBlIp;
    for(const auto &tmpUN : as_const(reciver->getListChilde())) {
        if(TypeUnitNode::IU_BL_IP == tmpUN->getType() && tmpUN->getNum2() == currentUN->getNum2()) {
            previousCopyUNLockIuBlIp = UnitNodeFactory::makeShare(*tmpUN);
            unLockIuBlIp = tmpUN;
            break;
        }
    }

    for(const auto& tmpUN : as_const(reciver->getListChilde())) {
        if(TypeUnitNode::SD_BL_IP == tmpUN->getType() && tmpUN->getNum2() == currentUN->getNum2() && 0 != tmpUN->getBazalt()) {
            previousCopyUNLockSdBlIp = UnitNodeFactory::makeShare(*tmpUN);
            unLockSdBlIp = tmpUN;
            break;
        }
    }

    if(unLockSdBlIp.isNull() || unLockIuBlIp.isNull()) {
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(3) <--";
        return false;
    } else if(0 == unLockSdBlIp->getBazalt()) {
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(4) <--";
        return false;
    }

    unLockSdBlIp->setStateWord(0x41u, stateWord);
    unLockIuBlIp->setStateWord(0x41u, stateWord);

    const auto &swpCurrentBLIP = unLockSdBlIp->swpBLIPType0x41();
    const auto &swpPreviousBLIP = previousCopyUNLockSdBlIp->swpBLIPType0x41();
    if(1 == swpCurrentBLIP.isExistDK()
    || 1 == swpCurrentBLIP.isWasDK()
    || 1 == swpPreviousBLIP.isExistDK()
    || 1 == swpPreviousBLIP.isWasDK()) {
        {
            auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                                  DataQueueItem::makeAlarmReset0x24);
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
                reciver->pushUniqManagerSingleMsg(msMsg);
            }
        }
        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(5) <--";
        return true;
    }

    const auto &swpCurrentSD = unLockSdBlIp->swpSDBLIPType0x41(),
               &swpPreviousSD = previousCopyUNLockSdBlIp->swpSDBLIPType0x41();
    const auto &swpCurrentIU = unLockIuBlIp->swpIUBLIPType0x41(),
               &swpPreviousIU = previousCopyUNLockIuBlIp->swpIUBLIPType0x41();

    auto isChangedStatus = false;
    if(swpCurrentSD.isAlarm() != swpPreviousSD.isAlarm() ||
       swpCurrentIU.isOff() != swpPreviousIU.isOff() ||
       swpCurrentSD.isNorm() != swpPreviousSD.isNorm() ||
       swpCurrentIU.isOn() != swpPreviousIU.isOn()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }

//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isChangedStatus " << isChangedStatus;

    // проверка на запрещённые переходы состояний -->
    auto isForbiddenTransferStatusForReaction = false;
    if(
            (1 == swpPreviousSD.isAlarm() &&
             1 == swpPreviousIU.isOff() && //Открыто
             1 == swpCurrentSD.isAlarm() &&
             1 == swpCurrentIU.isOn()) || //Открыто ключом

            (1 == swpPreviousSD.isNorm() &&
             1 == swpPreviousIU.isOn() && //Закрыто
             1 == swpCurrentSD.isNorm() &&
             1 == swpCurrentIU.isOff())) //Закрыто ключом
    { // запрещённая обработка перехода
      // (Открыто -> Открыто ключом, Закрыто -> Закрыто ключом)
        isForbiddenTransferStatusForReaction = true;
    }
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isForbiddenTransferStatusForReaction " << isForbiddenTransferStatusForReaction;

    // переводим на другой шаг обработчик открытия и закрытия этого УЗ -->
    if(!isForbiddenTransferStatusForReaction && isChangedStatus) {
        QPair<QString, QString> tmpPair(reciver->getUdpAdress(), QString::number(reciver->getUdpPort()));
        for(auto ar : as_const(getLsWaiter())) {
            if(ar->getIpPort() == tmpPair &&
               RequesterType::LockRequester == ar->getRequesterType() &&
               ar->getUnTarget() == unLockSdBlIp) {
                SignalSlotCommutator::emitEndLockWait();
                if(BeatStatus::RequestStep1 == ar->getBeatStatus()) {
//                                ar->startSecondRequest();
                    continue;
                } else if(BeatStatus::Waite == ar->getBeatStatus()) {
                    ar->startSecondRequest(3'000);
                } else if(BeatStatus::RequestStep2 == ar->getBeatStatus()) {
//                                ar->startEnd();
                    continue;
                } else if(BeatStatus::WaiteEnd == ar->getBeatStatus()) {
                      ar->startEnd();
                }
            }
        }
    }
    // переводим на другой шаг обработчик открытия и закрытия этого УЗ <--

    auto isForbiddenTransferStatusForJour = false;
    if(
            isForbiddenTransferStatusForReaction
            ||
            (1 == swpPreviousSD.isAlarm() &&
             1 == swpPreviousIU.isOn() &&  //Открыто ключом
             1 == swpCurrentSD.isAlarm() &&
             1 == swpCurrentIU.isOff()) //Открыто
            ||
            (1 == swpPreviousSD.isNorm() &&
             1 == swpPreviousIU.isOff() && //Закрыто ключом
             1 == swpCurrentSD.isNorm() &&
             1 == swpCurrentIU.isOn())  //Закрыто
//            ||
//            (1 == swpPreviousSD.isAlarm() &&
//             1 == swpPreviousIU.isOff() && //Открыто
//             1 == swpCurrentSD.isAlarm() &&
//             1 == swpCurrentIU.isOn())  //Открыто ключом
//            ||
//             (1 == swpPreviousSD.isNorm() &&
//              1 == swpPreviousIU.isOn() && //Закрыто
//              1 == swpCurrentSD.isNorm() &&
//              1 == swpCurrentIU.isOff()) //Закрыто ключом
      )
    { // запрещённая запись перехода (Открыто <-> Открыто ключом, Закрыто <-> Закрыто ключом)
        isForbiddenTransferStatusForJour = true;
    }
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isForbiddenTransferStatusForJour " << isForbiddenTransferStatusForJour;
    // проверка на запрещённые переходы состояний <--

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState() || -1 == reciver->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciver->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isWakeUp " << isWakeUp;

    int typeMsg = -1;
    QString commentMsg;

    if(1 == swpCurrentSD.isAlarm() &&
       1 == swpCurrentIU.isOff() &&
       (swpCurrentSD.isAlarm() != swpPreviousSD.isAlarm() ||
        swpCurrentIU.isOff() != swpPreviousIU.isOff())) {
        //Открыто
        commentMsg = QObject::tr("Открыто");
        typeMsg = 111;
        unLockSdBlIp->setPublishedState(111);
        unLockIuBlIp->setPublishedState(100);
    } else if(1 == swpCurrentSD.isNorm() &&
              1 == swpCurrentIU.isOn() &&
              (swpCurrentSD.isNorm() != swpPreviousSD.isNorm() ||
               swpCurrentIU.isOn() != swpPreviousIU.isOn())) {
        //Закрыто
        commentMsg = QObject::tr("Закрыто");
        typeMsg = 110;
        unLockSdBlIp->setPublishedState(110);
        unLockIuBlIp->setPublishedState(101);
    } else if(1 == swpCurrentSD.isAlarm() &&
              1 == swpCurrentIU.isOn() &&
              (swpCurrentSD.isAlarm() != swpPreviousSD.isAlarm() ||
               swpCurrentIU.isOn() != swpPreviousIU.isOn())) {
        //Открыто ключом
        commentMsg = QObject::tr("Открыто ключом");
        typeMsg = 113;
        unLockSdBlIp->setPublishedState(113);
        unLockIuBlIp->setPublishedState(101);
    } else if(1 == swpCurrentSD.isNorm() &&
              1 == swpCurrentIU.isOff() &&
              (swpCurrentSD.isNorm() != swpPreviousSD.isNorm() ||
               swpCurrentIU.isOff() != swpPreviousIU.isOff())) {
        //Закрыто ключом
        commentMsg = QObject::tr("Закрыто ключом");
        typeMsg = 112;
        unLockSdBlIp->setPublishedState(112);
        unLockIuBlIp->setPublishedState(100);
    }

//    qDebug() << "состояние УЗО -->" << commentMsg;
//    qDebug() << "pSD: " << previousCopyUNLockSdBlIp->toString() << swpPreviousSD.byteWord().toHex();
//    qDebug() << "cSD: " << unLockSdBlIp->toString() << swpCurrentSD.byteWord().toHex();
//    qDebug() << "pIU: " << previousCopyUNLockIuBlIp->toString() << swpPreviousIU.byteWord().toHex();
//    qDebug() << "cIU: " << unLockIuBlIp->toString() << swpCurrentIU.byteWord().toHex();
//    qDebug() << "состояние УЗО <--";

    if((isWakeUp || isFirstWakeUp || !isForbiddenTransferStatusForJour) && isChangedStatus && -1 != typeMsg) {
        // следует записать сообщение
        JourEntity msg;

        // заполняем поля сообщения за отправителя
        const auto &sendetMsgUN = ((1 != unLockSdBlIp->getMetaEntity()) ?
                                       unLockSdBlIp :
                                       ((1 != unLockIuBlIp->getMetaEntity()) ?
                                            unLockIuBlIp :
                                            nullptr));

        msg.setObject(sendetMsgUN->getName());
        msg.setObjecttype(sendetMsgUN->getType());
        msg.setD1(sendetMsgUN->getNum1());
        msg.setD2(sendetMsgUN->getNum2());
        msg.setD3(sendetMsgUN->getNum3());
        msg.setDirection(sendetMsgUN->getDirection());
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(sendetMsgUN, msg);
        if(113 == msg.getType()) {
            SoundAdjuster::playAlarm();
        }
    }

    unLockSdBlIp->updDoubl();
    unLockIuBlIp->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    if(1 == swpCurrentSD.isWasAlarm()) {
        //нужен сброс
        DataQueueItem alarmReset0x24;
        alarmReset0x24.setPort(currentUN->getUdpPort());
        alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
        DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

        if(alarmReset0x24.isValid()) {
            reciver->pushUniqQueueMsg(alarmReset0x24);
        }
    }

//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41(5) <--";
    return true;
}

bool PortManager::procIUBLIPStatusWord0x41(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procIUBLIPStatusWord0x41() -->";
    if(TypeUnitNode::IU_BL_IP != currentUN->getType()
    || 1 > currentUN->getNum2()
    || 4 < currentUN->getNum2()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procIUBLIPStatusWord0x41(1) <--";
        return false;
    }

    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procIUBLIPStatusWord0x41(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x41u, stateWord);

    const auto &swpCurrentBLIP = currentUN->swpBLIPType0x41();
    const auto &swpPreviousBLIP = previousUN->swpBLIPType0x41();
    if(1 == swpCurrentBLIP.isExistDK()
    || 1 == swpCurrentBLIP.isWasDK()
    || 1 == swpPreviousBLIP.isExistDK()
    || 1 == swpPreviousBLIP.isWasDK()) {
        {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
            }
        }
        qDebug() << "PortManager::procIUBLIPStatusWord0x41(5) <--";
        return true;
    }

    const auto &swpCurrent = currentUN->swpIUBLIPType0x41(),
               &swpPrevious = previousUN->swpIUBLIPType0x41();

    auto isChangedStatus = false;
    if(swpCurrent.isOff() != swpPrevious.isOff() ||
       swpCurrent.isOn() != swpPrevious.isOn()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procIUBLIPStatusWord0x41() -- isChangedStatus " << isChangedStatus;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState() || -1 == reciver->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procIUBLIPStatusWord0x41() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciver->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procIUBLIPStatusWord0x41() -- isWakeUp " << isWakeUp;

    // запись вкл/выкл ИУ -->
    int typeMsg = -1;
    QString commentMsg;

    if(1 == swpCurrent.isOff()) {
        commentMsg = QObject::tr("Выкл");
        typeMsg = 100;
        currentUN->setPublishedState(100);
        reciver->setPublishedState(100);
    } else if(1 == swpCurrent.isOn()) {
        commentMsg = QObject::tr("Вкл");
        typeMsg = 101;
        currentUN->setPublishedState(101);
        reciver->setPublishedState(101);
    }

//    qDebug() << "состояние ИУ -->" << commentMsg;
//    qDebug() << "pIU: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cIU: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние ИУ <--";

    if((isWakeUp || isFirstWakeUp || isChangedStatus) && 1 != currentUN->getMetaEntity() && -1 != typeMsg) {
        // следует записать сообщение
        JourEntity msg;

        // заполняем поля сообщения за отправителя
        msg.setObject(currentUN->getName());
        msg.setObjecttype(currentUN->getType());
        msg.setD1(currentUN->getNum1());
        msg.setD2(currentUN->getNum2());
        msg.setD3(currentUN->getNum3());
        msg.setDirection(currentUN->getDirection());
        if(currentUN->takeResetWaitAutoCommand())
            commentMsg += tr(" (Авто)");
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
    }
    // запись вкл/выкл ИУ <--

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procIUBLIPStatusWord0x41(3) <--";
    return true;
}

bool PortManager::procSDBLIPStatusWord0x41(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -->";
    if(TypeUnitNode::SD_BL_IP != currentUN->getType()
    || 1 == currentUN->getBazalt()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procSDBLIPStatusWord0x41(1) <--";
        return false;
    }

    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procSDBLIPStatusWord0x41(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x41u, stateWord);

    const auto &swpCurrentBLIP = currentUN->swpBLIPType0x41();
    const auto &swpPreviousBLIP = previousUN->swpBLIPType0x41();
    if(1 == swpCurrentBLIP.isExistDK()
    || 1 == swpCurrentBLIP.isWasDK()
    || 1 == swpPreviousBLIP.isExistDK()
    || 1 == swpPreviousBLIP.isWasDK()) {
        {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
            }
        }
        qDebug() << "PortManager::procSDBLIPStatusWord0x41(5) <--";
        return true;
    }

    const auto &swpCurrent = currentUN->swpSDBLIPType0x41(),
               &swpPrevious = previousUN->swpSDBLIPType0x41();

    auto isChangedStatus = false;
    if(swpCurrent.isAlarm() != swpPrevious.isAlarm() ||
       swpCurrent.isWasAlarm() != swpPrevious.isWasAlarm() ||
       swpCurrent.isNorm() != swpPrevious.isNorm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -- isChangedStatus " << isChangedStatus;

    auto isSwitchOnOff = false;
    if(!swpPrevious.isNull() &&
       (swpCurrent.isOff() != swpPrevious.isOff() ||
        swpCurrent.isOn() != swpPrevious.isOn())) {
        // состояние не зменилось - что-то пропускаем
        isSwitchOnOff = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -- isSwitchOnOff " << isSwitchOnOff;


    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciver->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needAlarmReset0x24 = false;
    auto makedAlarmReset0x24 = false;
    if(1 == swpCurrent.isOn() &&
//       1 == swpCurrent.isAlarm() &&
       1 == swpCurrent.isWasAlarm()) { // сброс тревоги
        needAlarmReset0x24 = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41 -- needAlarmReset0x24" << needAlarmReset0x24;
    if(needAlarmReset0x24) {
        //нужен сброс
        DataQueueItem alarmReset0x24;
        alarmReset0x24.setPort(currentUN->getUdpPort());
        alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
        DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

        if(alarmReset0x24.isValid()) {
            reciver->pushUniqQueueMsg(alarmReset0x24);
            makedAlarmReset0x24 = true;
        }
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41 -- makedAlarmReset0x24" << makedAlarmReset0x24;

    JourEntity prepareMsg;
    // заполняем поля сообщения за отправителя
    prepareMsg.setObject(currentUN->getName());
    prepareMsg.setObjecttype(currentUN->getType());
    prepareMsg.setD1(currentUN->getNum1());
    prepareMsg.setD2(currentUN->getNum2());
    prepareMsg.setD3(currentUN->getNum3());
    prepareMsg.setDirection(currentUN->getDirection());

    // запись вкл/выкл СД -->
    int typeMsg = -1;
    QString commentMsg;
    bool needRepeatActualState = false;

    if(1 == swpCurrent.isOff()) {
        commentMsg = QObject::tr("Выкл");
        typeMsg = 100;
        reciver->setPublishedState(100);
    } else if(1 == swpCurrent.isOn()) {
        commentMsg = QObject::tr("Вкл");
        typeMsg = 101;
        reciver->setPublishedState(101);
        needRepeatActualState = true;
    }

//    qDebug() << "состояние СД -->" << commentMsg;
//    qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние СД <--";

    if(isSwitchOnOff && 1 != currentUN->getMetaEntity() && -1 != typeMsg) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
    } else {
        needRepeatActualState = false;
    }
    typeMsg = -1;

    bool iniState = false;
    // запись тревог и нормы СД
    if(1 == swpCurrent.isOn()
    && 1 == swpCurrent.isAlarm()
    && 1 == swpCurrent.isWasAlarm()
    && (swpPrevious.isAlarm() != swpCurrent.isAlarm()
     || swpPrevious.isWasAlarm() != swpCurrent.isWasAlarm()
     || needRepeatActualState)) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        reciver->setPublishedState(20);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isNorm()
           && ((swpPrevious.isNorm() != swpCurrent.isNorm()
             && 1 != currentUN->getPublishedState())
            || needRepeatActualState)) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
        reciver->setPublishedState(1);
    } else if(1 == swpCurrent.isOn() &&
              1 != swpCurrent.isNorm() &&
              (isFirstWakeUp || isWakeUp)) {
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        iniState = true;
    }
    if(isWakeUp || isFirstWakeUp) {
        commentMsg += " (начальное состояние)";
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41 -- iniState" << iniState;


//    qDebug() << "состояние СД -->" << commentMsg;
//    qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние СД <--";

    if((isWakeUp ||
        isFirstWakeUp ||
        20 == currentUN->getPublishedState() ||
        currentUN->getPublishedState() != previousUN->getPublishedState() ||
        isChangedStatus ||
        needRepeatActualState) &&
       1 != currentUN->getMetaEntity() &&
       -1 != typeMsg &&
       currentUN->getControl()) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);

        if(20 == typeMsg && !iniState) {
            SoundAdjuster::playAlarm();
        }
    } else if(!isSwitchOnOff && 1 == swpCurrent.isOff()) {
        currentUN->setPublishedState(1);

        if(isWakeUp || isFirstWakeUp) {
            commentMsg = QObject::tr("Выкл (начальное состояние)");
            typeMsg = 100;
            JourEntity msg = prepareMsg;
            // заполняем поля сообщения
            msg.setComment(commentMsg);
            msg.setType(typeMsg);

            SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
            GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    if(20 == typeMsg && !iniState) {
        // тригер на ИУ
        for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(currentUN))) {
            SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
        }
        //нужен сброс
    }

//    qDebug() << "PortManager::procSDBLIPStatusWord0x41(3) <--";
    return true;
}

DataQueueItem PortManager::parcingStatusWord0x42(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "Utils::parcingStatusWord0x42() -->";
    const StateWord newStateWord(item.data().mid(5, 4));
    resultRequest = item;
    resultRequest.setData();

    QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::sortMetaRealUnitNodes();

    for(const QSharedPointer<UnitNode>  &un : tmpSet) {
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress()))
        || item.port() != un->getUdpPort()
        || static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1()))
            continue;

        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
            reciver->setStateWord(0x42u, newStateWord);
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x42 --x match";
            continue;
        }

        if(procDkBLIPStatusWord0x42(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x42 --> procDkBLIPStatusWord0x42() " << true;
        } else if(procSDBLIPStatusWord0x42(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x42 --> procSDBLIPStatusWord0x42() " << true;
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x42 --X proc " << false;
        }
    }

//    qDebug() << "Utils::parcingStatusWord0x42() <--";
    return resultRequest;

}

bool PortManager::procDkBLIPStatusWord0x42(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procDkBLIPStatusWord0x42() -->";
    if(0 == currentUN->getDK()
    || DKCiclStatus::DKIgnore == currentUN->getDkStatus()
    || DKCiclStatus::DKWrong == currentUN->getDkStatus()
    || DKCiclStatus::DKDone == currentUN->getDkStatus()
    || !currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procDkBLIPStatusWord0x42(1) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x42u, stateWord);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procDkBLIPStatusWord0x42(2) <--";
    return true;
}

bool PortManager::procSDBLIPStatusWord0x42(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
    //    qDebug() << "PortManager::procSDBLIPStatusWord0x42() -->";
    if(TypeUnitNode::SD_BL_IP != currentUN->getType()
    || 1 == currentUN->getBazalt()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procSDBLIPStatusWord0x42(1) <--";
        return false;
    }

    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procSDBLIPStatusWord0x42(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x42u, stateWord);

    const auto &swpCurrent = currentUN->swpSDBLIPType0x42(),
               &swpPrevious = previousUN->swpSDBLIPType0x42();

    auto isChangedStatus = false;
    if(swpCurrent.isInAlarm() != swpPrevious.isInAlarm() ||
       swpCurrent.isLineBreak() != swpPrevious.isLineBreak()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x42() -- isChangedStatus " << isChangedStatus;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x42() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciver->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x42() -- isWakeUp " << isWakeUp;

    // запись вкл/выкл СД -->
    QString commentMsg;

    if(1 == swpCurrent.isInAlarm()) {
        commentMsg = QObject::tr("Выкл");

//        qDebug() << "состояние СД -->" << commentMsg;
//        qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//        qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//        qDebug() << "состояние СД <--";
    }

    if(1 == swpCurrent.isShortCircuit()) {
        commentMsg = QObject::tr("Замыкание");

//        qDebug() << "состояние СД -->" << commentMsg;
//        qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//        qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//        qDebug() << "состояние СД <--";
    }

    if(1 == swpCurrent.isLineBreak()) {
        commentMsg = QObject::tr("Обрыв");

//        qDebug() << "состояние СД -->" << commentMsg;
//        qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//        qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//        qDebug() << "состояние СД <--";
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procSDBLIPStatusWord0x42(3) <--";
        return true;
}

DataQueueItem PortManager::parcingStatusWord0x41(DataQueueItem &item, DataQueueItem & resultRequest)
{
//    qDebug() << "Utils::parcingStatusWord0x41() -->";
    const StateWord newStateWord(item.data().mid(5, 4));
    resultRequest = item;
    resultRequest.setData();

    QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::sortMetaRealUnitNodes();

    for(const QSharedPointer<UnitNode>  &un : tmpSet) {
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress()))
        || item.port() != un->getUdpPort()
        || static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1()))
            continue;

        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
            reciver->setStateWord(0x41u, newStateWord);
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x41 --x match";
            continue;
        }

        if(procDkBLIPStatusWord0x41(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x41 --> procDkBLIPStatusWord0x41() " << true;
        } else if(procUzoBLIPStatusWord0x41(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x41 --> procUzoBLIPStatusWord0x41() " << true;
        } else if(procIUBLIPStatusWord0x41(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x41 --> procIUBLIPStatusWord0x41() " << true;
        } else if(procSDBLIPStatusWord0x41(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x41 --> procSDBLIPStatusWord0x41() " << true;
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x41 --X proc " << false;
        }
    }

//    qDebug() << "Utils::parcingStatusWord0x41() <--";
    return resultRequest;

}

bool PortManager::procDkBLIPStatusWord0x41(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procDkBLIPStatusWord0x41() -->";
    if(0 == currentUN->getDK()
    || TypeUnitNode::SD_BL_IP != currentUN->getType()
    || DKCiclStatus::DKIgnore == currentUN->getDkStatus()
    || DKCiclStatus::DKWrong == currentUN->getDkStatus()
    || DKCiclStatus::DKDone == currentUN->getDkStatus()
    || !currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procDkBLIPStatusWord0x41(1) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x41u, stateWord);

    auto swpCurrent = currentUN->swpSDBLIPType0x41();
    if(1 == swpCurrent.isOff()) {
        currentUN->setDkStatus(DKCiclStatus::DKWrong);

        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

        return true;
    }

    //qDebug() << "DkStatus --> " << currentUN->toString();
    auto unCalcDkStatus = currentUN->calcDKStatus();
    //qDebug() << "DkStatus -- unCalcDkStatus " << unCalcDkStatus;
    //qDebug() << "DkStatus -- unDkStatus " << currentUN->getDkStatus();
    if(DKCiclStatus::DKReady == previousUN->getDkStatus() &&
            DKCiclStatus::DKNorm == unCalcDkStatus)
        currentUN->setDkStatus(DKCiclStatus::DKNorm);
    else if((DKCiclStatus::DKNorm == previousUN->getDkStatus() || DKCiclStatus::DKReady == previousUN->getDkStatus())&&
            DKCiclStatus::DKWasAlarn == unCalcDkStatus)
        currentUN->setDkStatus(DKCiclStatus::DKWasAlarn);
    else if(DKCiclStatus::DKWasAlarn == previousUN->getDkStatus() &&
            DKCiclStatus::DKNorm == unCalcDkStatus)
        currentUN->setDkStatus(DKCiclStatus::DKDone);
    else if(DKCiclStatus::DKWasAlarn == previousUN->getDkStatus() &&
            DKCiclStatus::DKWas == unCalcDkStatus)
        currentUN->setDkStatus(DKCiclStatus::DKDone);
    else if((DKCiclStatus::DKNorm == previousUN->getDkStatus() &&
             DKCiclStatus::DKNorm == unCalcDkStatus) ||
            (DKCiclStatus::DKWasAlarn == previousUN->getDkStatus() &&
             DKCiclStatus::DKWasAlarn == unCalcDkStatus))
        currentUN->setDkStatus(previousUN->getDkStatus());
    else
        currentUN->setDkStatus(DKCiclStatus::DKWrong);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    //qDebug() << "DkStatus -- unNewDkStatus " << currentUN->getDkStatus();
    //qDebug() << "DkStatus <--";
//    qDebug() << "PortManager::procDkBLIPStatusWord0x41(2) <--";
    return true;
}

DataQueueItem PortManager::parcingStatusWord0x31(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "PortManager::parcingStatusWord0x31 --> " << item.address() << static_cast<quint8>(item.data().at(2));
    StateWord newStateWord(item.data().mid(5, item.data().at(3)));
    resultRequest = item;
    resultRequest.setData();

    QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::sortMetaRealUnitNodes();

    for(QSharedPointer<UnitNode>  un : tmpSet) {
        if(TypeUnitNode::RLM_C != un->getType()
        && TypeUnitNode::RLM_KRL != un->getType()
        && TypeUnitNode::TG != un->getType()) {
//            qDebug() << "PortManager::parcingStatusWord0x31 -- continue(1)";
            continue;
        }
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress()))
        || item.port() != un->getUdpPort()
        || static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1())) {
//            qDebug() << "PortManager::parcingStatusWord0x31 -- continue(2)";
            continue;
        }

        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
//            reciver->setStateWord(newStateWord);
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x31 --x match";
            continue;
        }

        if(procDkStatusWord0x31(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x31 --> procDkStatusWord0x31() " << true;
        } else if(procRlmStatusWord0x31(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x31 --> procRlmStatusWord0x31() " << true;
        } else if(procRlmCStatusWord0x31(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x31 --> procRlmCStatusWord0x31() " << true;
        } else if(procTgStatusWord0x31(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x31 --> procTgStatusWord0x31() " << true;
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x31 --X proc " << true;
        }

    }
//    qDebug() << "PortManager::parcingStatusWord0x31 <--";
    return resultRequest;
}

bool PortManager::procDkStatusWord0x31(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
    if(!currentUN->getDkInvolved()) {
        return false;
    }

    const auto &isAutoDK = currentUN->getIsAutoDkInvolved();

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x31u, stateWord);

    if((TypeUnitNode::RLM_C == currentUN->getType()
     && (1 == currentUN->swpRLMCType0x31().isOff()
      || 1 == currentUN->swpRLMCType0x31().isFault()
        ))
    || (TypeUnitNode::RLM_KRL == currentUN->getType()
     && (1 == currentUN->swpRLMType0x31().isOff()
      || 1 == currentUN->swpRLMType0x31().isFault()
        ))
    || (TypeUnitNode::TG == currentUN->getType()
     && 1 == currentUN->swpTGType0x31().isOff())
      ) { // ДК уже никогда не выполнить
        for(const auto &ar : as_const(getLsWaiter())) {
             if(RequesterType::DKWaiter == ar->getRequesterType()) {
                 auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                 if(dwWaiter->getLsTrackedUN().contains(currentUN)) {
                     finishDKWaiter(dwWaiter);
                     qDebug() << "PortManager::procDkStatusWord0x31 remove dwWaiter";
                     break;
                 }
             }
        }
    }


    if(DKCiclStatus::DKDone != currentUN->getDkStatus()) {
        procDK(currentUN, previousUN);
        if(DKCiclStatus::DKDone == currentUN->getDkStatus()) {
            for(const auto &ar : as_const(getLsWaiter())) {
                 if(RequesterType::DKWaiter == ar->getRequesterType()) {
                     auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                     if(dwWaiter->removeLsTrackedUN(currentUN)) {
                         if(0 == dwWaiter->getLsTrackedUN().size()) {
                             removeLsWaiter(dwWaiter);
                             SignalSlotCommutator::emitStopDKWait();
                         }
                         qDebug() << "PortManager::removeLsTrackedUN(" << currentUN->toString() << ")";
                         break;
                     }
                 }
            }
            JourEntity msg;
            msg.setObject(currentUN->getName());
            msg.setObjecttype(currentUN->getType());
            msg.setD1(currentUN->getNum1());
            msg.setD2(currentUN->getNum2());
            msg.setD3(currentUN->getNum3());
            msg.setDirection(currentUN->getDirection());
            msg.setComment(tr("Ком. ДК выполнена"));
            msg.setType(3);
            if(!isAutoDK) {
                SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
            }

            GraphTerminal::sendAbonentEventsAndStates(currentUN);
        }
    }
    if((TypeUnitNode::RLM_C == currentUN->getType()
     && 1 == currentUN->swpRLMCType0x31().isOn()
     && (
         1 == currentUN->swpRLMCType0x31().isOutAlarm()
//      || 1 == currentUN->swpRLMC().isWasDK()
      || 1 == currentUN->swpRLMCType0x31().isWasAlarm())
        )
    || (TypeUnitNode::RLM_KRL == currentUN->getType()
     && 1 == currentUN->swpRLMType0x31().isOn()
     && (
         1 == currentUN->swpRLMType0x31().isOutAlarm()
//      || 1 == currentUN->swpRLM().isWasDK()
      || 1 == currentUN->swpRLMType0x31().isWasAlarm()
      || 1 == currentUN->swpRLMType0x31().isWasOpened())
        )
    || (TypeUnitNode::TG == currentUN->getType()
     && 1 == currentUN->swpTGType0x31().isOn()
     && (
         1 == currentUN->swpTGType0x31().isWasAlarm()
//      || 1 == currentUN->swpTGType0x31().isWasDK()
      || 1 == currentUN->swpTGType0x31().isOutAlarm()
      || 1 == currentUN->swpTGType0x31().isWasOpened())
        )) {
        //нужен сброс
        auto reciver = UnitNode::findReciver(currentUN);
        if(reciver.isNull()) {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
                qDebug() << "PortManager::procDkStatusWord0x31 -- DataQueueItem::fillAlarmReset0x24(" << alarmReset0x24.data().toHex() << ", " << currentUN->toString() << ");";
            }
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    return true;
}

bool PortManager::procRlmStatusWord0x31(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procRlmStatusWord0x31() -->";
    if(TypeUnitNode::RLM_KRL != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procRlmStatusWord0x31(1) <--";
        return false;
    }

    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procRlmStatusWord0x31(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x31u, stateWord);

    const auto &swpCurrent = currentUN->swpRLMType0x31(),
               &swpPrevious = previousUN->swpRLMType0x31();

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
            }
        }
        qDebug() << "PortManager::procRlmStatusWord0x31(5) <--";
        return true;
    }

    auto isChangedStatus = false;
    if(swpCurrent.isFault() != swpPrevious.isFault()
    || swpCurrent.isOpened() != swpPrevious.isOpened()
    || swpCurrent.isWasOpened() != swpPrevious.isWasOpened()
    || swpCurrent.isAlarm() != swpPrevious.isAlarm()
    || swpCurrent.isWasAlarm() != swpPrevious.isWasAlarm() ||
       swpCurrent.isNorm() != swpPrevious.isNorm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31() -- isChangedStatus " << isChangedStatus;

    auto isSwitchOnOff = false;
    if(!swpPrevious.isNull() &&
       (swpCurrent.isOff() != swpPrevious.isOff() ||
        swpCurrent.isOn() != swpPrevious.isOn())) {
        // состояние не зменилось - что-то пропускаем
        isSwitchOnOff = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31() -- isSwitchOnOff " << isSwitchOnOff;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needAlarmReset0x24 = false;
    auto makedAlarmReset0x24 = false;
    if(1 == swpCurrent.isOn()
    && (
        1 == currentUN->swpRLMType0x31().isOutAlarm()
     || 1 == currentUN->swpRLMType0x31().isWasDK()
     || 1 == currentUN->swpRLMType0x31().isWasAlarm()
     || 1 == currentUN->swpRLMType0x31().isWasOpened())) { // сброс тревоги
        needAlarmReset0x24 = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31 -- needAlarmReset0x24" << needAlarmReset0x24;
    if(needAlarmReset0x24) {
        //нужен сброс
        DataQueueItem alarmReset0x24;
        alarmReset0x24.setPort(currentUN->getUdpPort());
        alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
        DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

        if(alarmReset0x24.isValid()) {
            reciver->pushUniqQueueMsg(alarmReset0x24);
            makedAlarmReset0x24 = true;
        }
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31 -- makedAlarmReset0x24" << makedAlarmReset0x24;

    JourEntity prepareMsg;
    // заполняем поля сообщения за отправителя
    prepareMsg.setObject(currentUN->getName());
    prepareMsg.setObjecttype(currentUN->getType());
    prepareMsg.setD1(currentUN->getNum1());
    prepareMsg.setD2(currentUN->getNum2());
    prepareMsg.setD3(currentUN->getNum3());
    prepareMsg.setDirection(currentUN->getDirection());

    int typeMsg = -1;
    QString commentMsg;
    bool needRepeatActualState = false;

    // запись вкл/выкл РЛМ
    if(1 == swpCurrent.isOff()) {
        commentMsg = QObject::tr("Выкл");
        typeMsg = 100;
    } else if(1 == swpCurrent.isOn()) {
        commentMsg = QObject::tr("Вкл");
        typeMsg = 101;
        needRepeatActualState = true;
    }

//    qDebug() << "состояние RLM -->" << commentMsg;
//    qDebug() << "pRLM: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cRLM: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние RLM <--";

    if(isSwitchOnOff && 1 != currentUN->getMetaEntity() && -1 != typeMsg) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
    } else {
        needRepeatActualState = false;
    }
    typeMsg = -1;

    bool iniState = false;
    // запись тревога/норма РЛМ
    if(1 == swpCurrent.isFault()
    && (swpCurrent.isFault() != swpPrevious.isFault() || needRepeatActualState)) {
        //сохранение неисправность или Норма
        commentMsg = QObject::tr("Неисправность");
        typeMsg = 12;
        currentUN->setPublishedState(12);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isOpened()
           && 1 == swpCurrent.isWasOpened()
           && (swpPrevious.isOpened() != swpCurrent.isOpened()
            || swpPrevious.isWasOpened() != swpCurrent.isWasOpened()
            || needRepeatActualState)) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-ВСКРЫТИЕ");
        typeMsg = 21;
        currentUN->setPublishedState(21);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isAlarm()
           && 1 == swpCurrent.isWasAlarm()
           && (swpPrevious.isAlarm() != swpCurrent.isAlarm()
            || swpPrevious.isWasAlarm() != swpCurrent.isWasAlarm()
            || needRepeatActualState)) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isNorm()
           && ((swpPrevious.isNorm() != swpCurrent.isNorm()
             && 1 != currentUN->getPublishedState()) || needRepeatActualState)) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
    } else if(1 == swpCurrent.isOn() &&
              1 != swpCurrent.isNorm() &&
              (isFirstWakeUp || isWakeUp)) {
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        iniState = true;
    }
    if(isWakeUp || isFirstWakeUp) {
        commentMsg += " (начальное состояние)";
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41 -- iniState" << iniState;

//    qDebug() << "состояние RLM -->" << commentMsg;
//    qDebug() << "pRLM: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cRLM: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние RLM <--";

    if((isWakeUp ||
        isFirstWakeUp ||
        12 == currentUN->getPublishedState() ||
        20 == currentUN->getPublishedState() ||
        21 == currentUN->getPublishedState() ||
        currentUN->getPublishedState() != previousUN->getPublishedState() ||
        needRepeatActualState
        ) &&
       (needRepeatActualState || isChangedStatus) &&
       1 != currentUN->getMetaEntity() &&
       -1 != typeMsg &&
       currentUN->getControl()) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);

        if(20 == typeMsg && !iniState) {
            SoundAdjuster::playAlarm();
        } else if(12 == typeMsg || 21 == typeMsg) {
            SoundAdjuster::playAlarm2();
        }
    } else if(!isSwitchOnOff && 1 == swpCurrent.isOff()) {
        currentUN->setPublishedState(1);

        if(isWakeUp || isFirstWakeUp) {
            commentMsg = QObject::tr("Выкл (начальное состояние)");
            typeMsg = 100;
            JourEntity msg = prepareMsg;
            // заполняем поля сообщения
            msg.setComment(commentMsg);
            msg.setType(typeMsg);

            SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
            GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    if((21 == typeMsg || 20 == typeMsg) && !iniState) {
        // тригер на ИУ
        for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(currentUN))) {
            SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
        }
        //нужен сброс
    }

    return true;
}

bool PortManager::procRlmCStatusWord0x31(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procRlmCStatusWord0x31() -->";
    if(TypeUnitNode::RLM_C != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procRlmCStatusWord0x31(1) <--";
        return false;
    }

    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procRlmCStatusWord0x31(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x31u, stateWord);

    const auto &swpCurrent = currentUN->swpRLMCType0x31(),
               &swpPrevious = previousUN->swpRLMCType0x31();

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
            }
        }
        qDebug() << "PortManager::procRlmCStatusWord0x31(5) <--";
        return true;
    }

    auto isChangedStatus = false;
    if(swpCurrent.isFault() != swpPrevious.isFault()
    || swpCurrent.isAlarm() != swpPrevious.isAlarm()
    || swpCurrent.isWasAlarm() != swpPrevious.isWasAlarm() ||
       swpCurrent.isNorm() != swpPrevious.isNorm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procRlmCStatusWord0x31() -- isChangedStatus " << isChangedStatus;

    auto isSwitchOnOff = false;
    if(!swpPrevious.isNull() &&
       (swpCurrent.isOff() != swpPrevious.isOff() ||
        swpCurrent.isOn() != swpPrevious.isOn())) {
        // состояние не зменилось - что-то пропускаем
        isSwitchOnOff = true;
    }
//    qDebug() << "PortManager::procRlmCStatusWord0x31() -- isSwitchOnOff " << isSwitchOnOff;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procRlmCStatusWord0x31() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procRlmCStatusWord0x31() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needAlarmReset0x24 = false;
    auto makedAlarmReset0x24 = false;
    if(1 == swpCurrent.isOn()
    && (1 == currentUN->swpRLMCType0x31().isOutAlarm()
     || 1 == currentUN->swpRLMCType0x31().isWasDK()
     || 1 == currentUN->swpRLMCType0x31().isWasAlarm())) { // сброс тревоги
        needAlarmReset0x24 = true;
    }
//    qDebug() << "PortManager::procRlmCStatusWord0x31 -- needAlarmReset0x24" << needAlarmReset0x24;
    if(needAlarmReset0x24) {
        //нужен сброс
        DataQueueItem alarmReset0x24;
        alarmReset0x24.setPort(currentUN->getUdpPort());
        alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
        DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

        if(alarmReset0x24.isValid()) {
            reciver->pushUniqQueueMsg(alarmReset0x24);
            makedAlarmReset0x24 = true;
        }
    }
//    qDebug() << "PortManager::procRlmCStatusWord0x31 -- makedAlarmReset0x24" << makedAlarmReset0x24;

    JourEntity prepareMsg;
    // заполняем поля сообщения за отправителя
    prepareMsg.setObject(currentUN->getName());
    prepareMsg.setObjecttype(currentUN->getType());
    prepareMsg.setD1(currentUN->getNum1());
    prepareMsg.setD2(currentUN->getNum2());
    prepareMsg.setD3(currentUN->getNum3());
    prepareMsg.setDirection(currentUN->getDirection());

    int typeMsg = -1;
    QString commentMsg;
    bool needRepeatActualState = false;

    // запись вкл/выкл РЛМC
    if(1 == swpCurrent.isOff()) {
        commentMsg = QObject::tr("Выкл");
        typeMsg = 100;
    } else if(1 == swpCurrent.isOn()) {
        commentMsg = QObject::tr("Вкл");
        typeMsg = 101;
        needRepeatActualState = true;
    }

//    qDebug() << "состояние RLMC -->" << commentMsg;
//    qDebug() << "pRLM: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cRLM: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние RLMC <--";

    if(isSwitchOnOff && 1 != currentUN->getMetaEntity() && -1 != typeMsg) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
    } else {
        needRepeatActualState = false;
    }
    typeMsg = -1;

    bool iniState = false;
    // запись тревога/норма РЛМC
    if(1 == swpCurrent.isFault()
    && (swpCurrent.isFault() != swpPrevious.isFault()
     || needRepeatActualState)) {
        //сохранение неисправность или Норма
        commentMsg = QObject::tr("Неисправность");
        typeMsg = 12;
        currentUN->setPublishedState(12);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isAlarm()
           && 1 == swpCurrent.isWasAlarm()
           && (swpPrevious.isAlarm() != swpCurrent.isAlarm()
            || swpPrevious.isWasAlarm() != swpCurrent.isWasAlarm()
            || needRepeatActualState)) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isNorm()
           && ((swpPrevious.isNorm() != swpCurrent.isNorm()
             && 1 != currentUN->getPublishedState())
            || needRepeatActualState)) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
    } else if(1 == swpCurrent.isOn() &&
              1 != swpCurrent.isNorm() &&
              (isFirstWakeUp || isWakeUp)) {
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        iniState = true;
    }
    if(isWakeUp || isFirstWakeUp) {
        commentMsg += " (начальное состояние)";
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41 -- iniState" << iniState;

//    qDebug() << "состояние RLMC -->" << commentMsg;
//    qDebug() << "pRLMC: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cRLMC: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние RLMC <--";

    if((isWakeUp ||
        isFirstWakeUp ||
        12 == currentUN->getPublishedState() ||
        20 == currentUN->getPublishedState() ||
        currentUN->getPublishedState() != previousUN->getPublishedState() ||
        needRepeatActualState
        ) &&
       (needRepeatActualState || isChangedStatus) &&
       1 != currentUN->getMetaEntity() &&
       -1 != typeMsg &&
       currentUN->getControl()) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);

        if(20 == typeMsg && !iniState) {
            SoundAdjuster::playAlarm();
        } else if(12 == typeMsg) {
            SoundAdjuster::playAlarm2();
        }

    } else if(!isSwitchOnOff && 1 == swpCurrent.isOff()) {
        currentUN->setPublishedState(1);

        if(isWakeUp || isFirstWakeUp) {
            commentMsg = QObject::tr("Выкл (начальное состояние)");
            typeMsg = 100;
            JourEntity msg = prepareMsg;
            // заполняем поля сообщения
            msg.setComment(commentMsg);
            msg.setType(typeMsg);

            SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
            GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    if(20 == typeMsg && !iniState) {
        // тригер на ИУ
        for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(currentUN))) {
            SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
        }
        //нужен сброс
    }

//    qDebug() << "PortManager::procRlmCStatusWord0x31(X) <--";
    return true;
}

bool PortManager::procTgStatusWord0x31(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procTgStatusWord0x31() -->";
    if(TypeUnitNode::TG != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procTgStatusWord0x31(1) <--";
        return false;
    }

    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procTgStatusWord0x31(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x31u, stateWord);

    const auto &swpCurrent = currentUN->swpTGType0x31(),
               &swpPrevious = previousUN->swpTGType0x31();

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
            }
        }
        qDebug() << "PortManager::procTgStatusWord0x31(5) <--";
        return true;
    }

    auto isChangedStatus = false;
    if(swpCurrent.isOpened() != swpPrevious.isOpened()
    || swpCurrent.isWasOpened() != swpPrevious.isWasOpened()
    || swpCurrent.isAlarm() != swpPrevious.isAlarm()
    || swpCurrent.isWasAlarm() != swpPrevious.isWasAlarm() ||
       swpCurrent.isNorm() != swpPrevious.isNorm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x31() -- isChangedStatus " << isChangedStatus;

    auto isSwitchOnOff = false;
    if(!swpPrevious.isNull() &&
       (swpCurrent.isOff() != swpPrevious.isOff() ||
        swpCurrent.isOn() != swpPrevious.isOn())) {
        // состояние не зменилось - что-то пропускаем
        isSwitchOnOff = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x31() -- isSwitchOnOff " << isSwitchOnOff;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState() || -1 == reciver->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x31() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciver->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x31() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needAlarmReset0x24 = false;
    auto makedAlarmReset0x24 = false;
    if(1 == swpCurrent.isOn()
    && (1 == swpCurrent.isWasAlarm()
     || 1 == swpCurrent.isWasDK()
     || 1 == swpCurrent.isOutAlarm()
     || 1 == swpCurrent.isWasOpened())) { // сброс тревоги
        needAlarmReset0x24 = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x31 -- needAlarmReset0x24" << needAlarmReset0x24;
    if(needAlarmReset0x24) {
        //нужен сброс
        DataQueueItem alarmReset0x24;
        alarmReset0x24.setPort(currentUN->getUdpPort());
        alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
        DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

        if(alarmReset0x24.isValid()) {
            reciver->pushUniqQueueMsg(alarmReset0x24);
            makedAlarmReset0x24 = true;
        }
    }
//    qDebug() << "PortManager::procTgStatusWord0x31 -- makedAlarmReset0x24" << makedAlarmReset0x24;

    JourEntity prepareMsg;
    // заполняем поля сообщения за отправителя
    prepareMsg.setObject(currentUN->getName());
    prepareMsg.setObjecttype(currentUN->getType());
    prepareMsg.setD1(currentUN->getNum1());
    prepareMsg.setD2(currentUN->getNum2());
    prepareMsg.setD3(currentUN->getNum3());
    prepareMsg.setDirection(currentUN->getDirection());

    int typeMsg = -1;
    QString commentMsg;

    // запись вкл/выкл РЛМ
    if(1 == swpCurrent.isOff()) {
        commentMsg = QObject::tr("Выкл");
        typeMsg = 100;
    } else if(1 == swpCurrent.isOn()) {
        commentMsg = QObject::tr("Вкл");
        typeMsg = 101;
    }

//    qDebug() << "состояние TG -->" << commentMsg;
//    qDebug() << "pTG: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cTG: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние TG <--";

    if(isSwitchOnOff && 1 != currentUN->getMetaEntity() && -1 != typeMsg) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
    }
    typeMsg = -1;

    bool iniState = false;
    // запись тревога/норма РЛМ
    if(1 == swpCurrent.isOn()
    && 1 == swpCurrent.isOpened()
    && 1 == swpCurrent.isWasOpened()
    && (swpPrevious.isOpened() != swpCurrent.isOpened()
     || swpPrevious.isWasOpened() != swpCurrent.isWasOpened())) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-ВСКРЫТИЕ");
        typeMsg = 21;
        currentUN->setPublishedState(21);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isAlarm()
           && 1 == swpCurrent.isWasAlarm()
           && (swpPrevious.isAlarm() != swpCurrent.isAlarm()
            || swpPrevious.isWasAlarm() != swpCurrent.isWasAlarm())) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isNorm()
           && swpPrevious.isNorm() != swpCurrent.isNorm()
           && 1 != currentUN->getPublishedState()) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
    } else if(1 == swpCurrent.isOn() &&
              1 != swpCurrent.isNorm() &&
              (isFirstWakeUp || isWakeUp)) {
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        iniState = true;
    }
    if(isWakeUp || isFirstWakeUp) {
        commentMsg += " (начальное состояние)";
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41 -- iniState" << iniState;

//    qDebug() << "состояние TG -->" << commentMsg;
//    qDebug() << "pTG: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cTG: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние TG <--";

    if((isWakeUp ||
        isFirstWakeUp ||
        20 == currentUN->getPublishedState() ||
        21 == currentUN->getPublishedState() ||
        currentUN->getPublishedState() != previousUN->getPublishedState()) &&
       isChangedStatus &&
       1 != currentUN->getMetaEntity() &&
       -1 != typeMsg &&
       currentUN->getControl()) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);

        if(20 == typeMsg && !iniState) {
            SoundAdjuster::playAlarm();
        } else if(21 == typeMsg) {
            SoundAdjuster::playAlarm2();
        }
    } else if(!isSwitchOnOff && 1 == swpCurrent.isOff()) {
        currentUN->setPublishedState(1);

        if(isWakeUp || isFirstWakeUp) {
            commentMsg = QObject::tr("Выкл (начальное состояние)");
            typeMsg = 100;
            JourEntity msg = prepareMsg;
            // заполняем поля сообщения
            msg.setComment(commentMsg);
            msg.setType(typeMsg);

            SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
            GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    if((21 == typeMsg || 20 == typeMsg) && !iniState) {
        // тригер на ИУ
        for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(currentUN))) {
            SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
        }
        //нужен сброс
    }

//    qDebug() << "PortManager::procTgStatusWord0x31(X) <--";
    return true;
}

DataQueueItem PortManager::parcingStatusWord0x32(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "PortManager::parcingStatusWord0x32 --> " << item.address() << static_cast<quint8>(item.data().at(2));
    StateWord newStateWord(item.data().mid(5, item.data().at(3)));
    resultRequest = item;
    resultRequest.setData();

    QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::sortMetaRealUnitNodes();

    for(QSharedPointer<UnitNode>  un : tmpSet) {
        if(TypeUnitNode::TG != un->getType()) {
//            qDebug() << "PortManager::parcingStatusWord0x32 -- continue(1)";
            continue;
        }
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress()))
        || item.port() != un->getUdpPort()
        || static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1())) {
//            qDebug() << "PortManager::parcingStatusWord0x32 -- continue(2)";
            continue;
        }

        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
//            reciver->setStateWord(newStateWord);
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x32 --x match";
            continue;
        }

        if(procDkStatusWord0x32(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x32 --> procDkStatusWord0x32() " << true;
        } else if(procTgStatusWord0x32(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x32 --> procTgStatusWord0x32() " << true;
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x32 --X proc " << false;
        }

    }
//    qDebug() << "PortManager::parcingStatusWord0x32 <--";
    return resultRequest;
}

bool PortManager::procDkStatusWord0x32(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
    if(!currentUN->getDkInvolved() || TypeUnitNode::TG != currentUN->getType()) {
        return false;
    }

    const auto &isAutoDK = currentUN->getIsAutoDkInvolved();

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x32u, stateWord);

    const auto &swpCurrent = currentUN->swpTGType0x32().C(currentUN->getNum2());

    if(1 == swpCurrent.isFault()) { // ДК уже никогда не выполнить
        for(const auto &ar : as_const(getLsWaiter())) {
             if(RequesterType::DKWaiter == ar->getRequesterType()) {
                 auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                 if(dwWaiter->getLsTrackedUN().contains(currentUN)) {
                     finishDKWaiter(dwWaiter);
                     qDebug() << "PortManager::procDkStatusWord0x31 remove dwWaiter";
                     return true;
                 }
             }
        }
    }


    if(DKCiclStatus::DKDone != currentUN->getDkStatus()) {
        procDK(currentUN, previousUN);
        if(DKCiclStatus::DKDone == currentUN->getDkStatus()) {
            for(const auto &ar : as_const(getLsWaiter())) {
                 if(RequesterType::DKWaiter == ar->getRequesterType()) {
                     auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                     if(dwWaiter->removeLsTrackedUN(currentUN)) {
                         if(0 == dwWaiter->getLsTrackedUN().size()) {
                             removeLsWaiter(dwWaiter);
                             SignalSlotCommutator::emitStopDKWait();
                         }
                         qDebug() << "PortManager::removeLsTrackedUN(" << currentUN->toString() << ")";
                         break;
                     }
                 }
            }
            JourEntity msg;
            msg.setObject(currentUN->getName());
            msg.setObjecttype(currentUN->getType());
            msg.setD1(currentUN->getNum1());
            msg.setD2(currentUN->getNum2());
            msg.setD3(currentUN->getNum3());
            msg.setDirection(currentUN->getDirection());
            msg.setComment(tr("Ком. ДК выполнена"));
            msg.setType(3);
            if(!isAutoDK) {
                SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
            }

            GraphTerminal::sendAbonentEventsAndStates(currentUN);
        }
    }
    if(1 == swpCurrent.isInAlarm()
//    || 1 == swpCurrent.isWasDK()
    || 1 == swpCurrent.isSideAlarm()
    || 1 == swpCurrent.isWasOpened()) {
        //нужен сброс
        auto reciver = UnitNode::findReciver(currentUN);
        if(reciver.isNull()) {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
                qDebug() << "PortManager::procDkStatusWord0x31 -- DataQueueItem::fillAlarmReset0x24(" << alarmReset0x24.data().toHex() << ", " << currentUN->toString() << ");";
            }
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    return true;
}

bool PortManager::procTgStatusWord0x32(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procTgStatusWord0x32() -->";
    if(TypeUnitNode::TG != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procTgStatusWord0x32(1) <--";
        return false;
    }

    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procTgStatusWord0x32(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x32u, stateWord);

    const auto &swpCurrent = currentUN->swpTGType0x32(),
               &swpPrevious = previousUN->swpTGType0x32();
    const auto &swpCurrentCi = swpCurrent.C(currentUN->getNum2()),
               &swpPreviousCi = swpPrevious.C(currentUN->getNum2());

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
            }
        }
        qDebug() << "PortManager::procTgStatusWord0x32(5) <--";
        return true;
    }

    auto isChangedStatus = false;
    if(swpCurrentCi.isInOpened() != swpPreviousCi.isInOpened()
    || swpCurrentCi.isWasOpened() != swpPreviousCi.isWasOpened()
    || swpCurrentCi.isInAlarm() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isOutAlarm() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isSideAlarm() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isFault() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isNorm() != swpPreviousCi.isNorm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x32() -- isChangedStatus " << isChangedStatus;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x32() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x32() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needAlarmReset0x24 = false;
    auto makedAlarmReset0x24 = false;
    if(1 == swpCurrentCi.isInAlarm()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpCurrentCi.isSideAlarm()
    || 1 == swpCurrentCi.isWasOpened()) { // сброс тревоги
        needAlarmReset0x24 = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x32 -- needAlarmReset0x24" << needAlarmReset0x24;
    if(needAlarmReset0x24) {
        //нужен сброс
        DataQueueItem alarmReset0x24;
        alarmReset0x24.setPort(currentUN->getUdpPort());
        alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
        DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

        if(alarmReset0x24.isValid()) {
            reciver->pushUniqQueueMsg(alarmReset0x24);
            makedAlarmReset0x24 = true;
        }
    }
//    qDebug() << "PortManager::procTgStatusWord0x32 -- makedAlarmReset0x24" << makedAlarmReset0x24;

    JourEntity prepareMsg;
    // заполняем поля сообщения за отправителя
    prepareMsg.setObject(currentUN->getName());
    prepareMsg.setObjecttype(currentUN->getType());
    prepareMsg.setD1(currentUN->getNum1());
    prepareMsg.setD2(currentUN->getNum2());
    prepareMsg.setD3(currentUN->getNum3());
    prepareMsg.setDirection(currentUN->getDirection());

    int typeMsg = -1;
    QString commentMsg;

    bool iniState = false;
    // запись неисправность/вскрытие/тревога/норма TG
    if(1 == swpCurrentCi.isFault()
    && swpCurrentCi.isFault() != swpPreviousCi.isFault()) {
        //сохранение неисправность или Норма
        commentMsg = QObject::tr("Неисправность");
        typeMsg = 12;
        currentUN->setPublishedState(12);
    } else if(1 == swpCurrentCi.isOpened()
           && swpPreviousCi.isOpened() != swpCurrentCi.isOpened()) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-ВСКРЫТИЕ");
        typeMsg = 21;
        currentUN->setPublishedState(21);
    } else if(1 == swpCurrentCi.isAlarm()
           && swpPreviousCi.isAlarm() != swpCurrentCi.isAlarm()) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
    } else if(1 == swpCurrentCi.isNorm()
           && swpPreviousCi.isNorm() != swpCurrentCi.isNorm()
           && 1 != currentUN->getPublishedState()) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
    } else if(1 != swpCurrentCi.isNorm()&&
              (isFirstWakeUp || isWakeUp)) {
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        iniState = true;
    }
    if(isWakeUp || isFirstWakeUp) {
        commentMsg += " (начальное состояние)";
    }

//    qDebug() << "состояние TG -->" << commentMsg;
//    qDebug() << "pTG: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cTG: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние TG <--";

    if((isWakeUp ||
        isFirstWakeUp ||
        12 == currentUN->getPublishedState() ||
        20 == currentUN->getPublishedState() ||
        21 == currentUN->getPublishedState() ||
        currentUN->getPublishedState() != previousUN->getPublishedState()) &&
       isChangedStatus &&
       1 != currentUN->getMetaEntity() &&
       -1 != typeMsg &&
       currentUN->getControl()) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);

        if(20 == typeMsg) {
            SoundAdjuster::playAlarm();
        } else if(12 == typeMsg || 21 == typeMsg) {
            SoundAdjuster::playAlarm2();
        }
    }

    if((21 == typeMsg || 20 == typeMsg) && !iniState) {
        // тригер на ИУ
        for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(currentUN))) {
            SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
        }
        //нужен сброс
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procTgStatusWord0x32(X) <--";
    return true;
}

DataQueueItem PortManager::parcingStatusWord0x33(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "PortManager::parcingStatusWord0x33 --> " << item.address() << static_cast<quint8>(item.data().at(2));
    StateWord newStateWord(item.data().mid(5, item.data().at(3)));
    resultRequest = item;
    resultRequest.setData();

    QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::sortMetaRealUnitNodes();

    for(QSharedPointer<UnitNode>  un : tmpSet) {
        if(TypeUnitNode::TG != un->getType()) {
//            qDebug() << "PortManager::parcingStatusWord0x33 -- continue(1)";
            continue;
        }
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress()))
        || item.port() != un->getUdpPort()
        || static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1())) {
//            qDebug() << "PortManager::parcingStatusWord0x33 -- continue(2)";
            continue;
        }

        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
//            reciver->setStateWord(newStateWord);
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x33 --x match";
            continue;
        }

        if(procDkStatusWord0x33(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x33 --> procDkStatusWord0x33() " << true;
        } else if(procTgStatusWord0x33(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x33 --> procTgStatusWord0x33() " << true;
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x33 --X proc " << false;
        }

    }
//    qDebug() << "PortManager::parcingStatusWord0x33 <--";
    return resultRequest;
}

bool PortManager::procDkStatusWord0x33(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procDkStatusWord0x33 -->";
    if(!currentUN->getDkInvolved() || TypeUnitNode::TG != currentUN->getType()) {
//        qDebug() << "PortManager::procDkStatusWord0x33(1) <--";
        return false;
    }

    const auto &isAutoDK = currentUN->getIsAutoDkInvolved();

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x33u, stateWord);

    const auto &swpCurrent = currentUN->swpTGType0x33().C(currentUN->getNum2());

    if(1 == swpCurrent.isFault()) { // ДК уже никогда не выполнить
        for(const auto &ar : as_const(getLsWaiter())) {
             if(RequesterType::DKWaiter == ar->getRequesterType()) {
                 auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                 if(dwWaiter->getLsTrackedUN().contains(currentUN)) {
                     finishDKWaiter(dwWaiter);
                     qDebug() << "PortManager::procDkStatusWord0x31 remove dwWaiter";
                     return true;
                 }
             }
        }
    }

    if(DKCiclStatus::DKDone != currentUN->getDkStatus()) {
        procDK(currentUN, previousUN);
        if(DKCiclStatus::DKDone == currentUN->getDkStatus()) {
            for(const auto &ar : as_const(getLsWaiter())) {
                 if(RequesterType::DKWaiter == ar->getRequesterType()) {
                     auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                     if(dwWaiter->removeLsTrackedUN(currentUN)) {
                         if(0 == dwWaiter->getLsTrackedUN().size()) {
                             removeLsWaiter(dwWaiter);
                             SignalSlotCommutator::emitStopDKWait();
                         }
//                         qDebug() << "PortManager::removeLsTrackedUN(" << currentUN->toString() << ")";
                         break;
                     }
                 }
            }
            JourEntity msg;
            msg.setObject(currentUN->getName());
            msg.setObjecttype(currentUN->getType());
            msg.setD1(currentUN->getNum1());
            msg.setD2(currentUN->getNum2());
            msg.setD3(currentUN->getNum3());
            msg.setDirection(currentUN->getDirection());
            msg.setComment(tr("Ком. ДК выполнена"));
            msg.setType(3);
            if(!isAutoDK) {
                SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
            }

            GraphTerminal::sendAbonentEventsAndStates(currentUN);
        }
    }
    if(1 == swpCurrent.isInAlarm()
//    || 1 == swpCurrent.isWasDK()
    || 1 == swpCurrent.isSideAlarm()
    || 1 == swpCurrent.isWasOpened()) {
        //нужен сброс
        auto reciver = UnitNode::findReciver(currentUN);
        if(reciver.isNull()) {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
//                qDebug() << "PortManager::procDkStatusWord0x33 -- DataQueueItem::fillAlarmReset0x24(" << alarmReset0x24.data().toHex() << ", " << currentUN->toString() << ");";
            }
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procDkStatusWord0x33(1) <--";
    return true;
}

bool PortManager::procTgStatusWord0x33(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procTgStatusWord0x33() -->";
    if(TypeUnitNode::TG != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procTgStatusWord0x33(1) <--";
        return false;
    }

    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procTgStatusWord0x33(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x33u, stateWord);

    const auto &swpCurrent = currentUN->swpTGType0x33(),
               &swpPrevious = previousUN->swpTGType0x33();
    const auto &swpCurrentCi = swpCurrent.C(currentUN->getNum2()),
               &swpPreviousCi = swpPrevious.C(currentUN->getNum2());

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        {
            //нужен сброс
            DataQueueItem alarmReset0x24;
            alarmReset0x24.setPort(currentUN->getUdpPort());
            alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
            DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

            if(alarmReset0x24.isValid()) {
                reciver->pushUniqQueueMsg(alarmReset0x24);
            }
        }
        qDebug() << "PortManager::procTgStatusWord0x33(5) <--";
        return true;
    }

    auto isChangedStatus = false;
    if(swpCurrentCi.isInOpened() != swpPreviousCi.isInOpened()
    || swpCurrentCi.isWasOpened() != swpPreviousCi.isWasOpened()
    || swpCurrentCi.isInAlarm() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isOutAlarm() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isSideAlarm() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isFault() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isNorm() != swpPreviousCi.isNorm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x33() -- isChangedStatus " << isChangedStatus;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x33() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x33() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needAlarmReset0x24 = false;
    auto makedAlarmReset0x24 = false;
    if(1 == swpCurrentCi.isInAlarm()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpCurrentCi.isSideAlarm()
    || 1 == swpCurrentCi.isWasOpened()) { // сброс тревоги
        needAlarmReset0x24 = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x33 -- needAlarmReset0x24" << needAlarmReset0x24;
    if(needAlarmReset0x24) {
        //нужен сброс
        DataQueueItem alarmReset0x24;
        alarmReset0x24.setPort(currentUN->getUdpPort());
        alarmReset0x24.setAddress(Utils::hostAddress(currentUN->getUdpAdress()));
        DataQueueItem::fillAlarmReset0x24(alarmReset0x24, currentUN);

        if(alarmReset0x24.isValid()) {
            reciver->pushUniqQueueMsg(alarmReset0x24);
            makedAlarmReset0x24 = true;
        }
    }
//    qDebug() << "PortManager::procTgStatusWord0x33 -- makedAlarmReset0x24" << makedAlarmReset0x24;

    JourEntity prepareMsg;
    // заполняем поля сообщения за отправителя
    prepareMsg.setObject(currentUN->getName());
    prepareMsg.setObjecttype(currentUN->getType());
    prepareMsg.setD1(currentUN->getNum1());
    prepareMsg.setD2(currentUN->getNum2());
    prepareMsg.setD3(currentUN->getNum3());
    prepareMsg.setDirection(currentUN->getDirection());

    int typeMsg = -1;
    QString commentMsg;

    bool iniState = false;
    // запись неисправность/вскрытие/тревога/норма TG
    if(1 == swpCurrentCi.isFault()
    && swpCurrentCi.isFault() != swpPreviousCi.isFault()) {
        //сохранение неисправность или Норма
        commentMsg = QObject::tr("Неисправность");
        typeMsg = 12;
        currentUN->setPublishedState(12);
    } else if(1 == swpCurrentCi.isOpened()
           && swpPreviousCi.isOpened() != swpCurrentCi.isOpened()) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-ВСКРЫТИЕ");
        typeMsg = 21;
        currentUN->setPublishedState(21);
    } else if(1 == swpCurrentCi.isAlarm()
           && swpPreviousCi.isAlarm() != swpCurrentCi.isAlarm()) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
    } else if(1 == swpCurrentCi.isNorm()
           && swpPreviousCi.isNorm() != swpCurrentCi.isNorm()
           && 1 != currentUN->getPublishedState()) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
    } else if(1 != swpCurrentCi.isNorm() &&
              (isFirstWakeUp || isWakeUp)) {
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        iniState = true;
    }
    if(isWakeUp || isFirstWakeUp) {
        commentMsg += " (начальное состояние)";
    }

//    qDebug() << "состояние TG -->" << commentMsg;
//    qDebug() << "pTG: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cTG: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние TG <--";

    if((isWakeUp ||
        isFirstWakeUp ||
        12 == currentUN->getPublishedState() ||
        20 == currentUN->getPublishedState() ||
        21 == currentUN->getPublishedState() ||
        currentUN->getPublishedState() != previousUN->getPublishedState()) &&
       isChangedStatus &&
       1 != currentUN->getMetaEntity() &&
       -1 != typeMsg &&
       currentUN->getControl()) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);

        if(20 == typeMsg) {
            SoundAdjuster::playAlarm();
        } else if(12 == typeMsg || 21 == typeMsg) {
            SoundAdjuster::playAlarm2();
        }

    }

    if((21 == typeMsg || 20 == typeMsg) && !iniState) {
        // тригер на ИУ
        for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(currentUN))) {
            SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
        }
        //нужен сброс
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procTgStatusWord0x33(X) <--";
    return true;
}

DataQueueItem PortManager::parcingStatusWord0x34(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "PortManager::parcingStatusWord0x34 -->";
    StateWord newStateWord(item.data().mid(5, item.data().at(3)));
    resultRequest = item;
    resultRequest.setData();

    QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::sortMetaRealUnitNodes();

    for(QSharedPointer<UnitNode>  un : tmpSet) {
        if(TypeUnitNode::TG != un->getType()) {
//            qDebug() << "PortManager::parcingStatusWord0x34 -- continue(1)";
            continue;
        }
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress()))
        || item.port() != un->getUdpPort()
        || static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1())) {
//            qDebug() << "PortManager::parcingStatusWord0x34 -- continue(2)";
            continue;
        }

        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
//            reciver->setStateWord(newStateWord);
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x34 --x match";
            continue;
        }

        if(procDkStatusWord0x34(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x34 --> procDkStatusWord0x34() " << true;
        } else if(procTgStatusWord0x34(un, newStateWord)) {
//            qDebug() << "PortManager::parcingStatusWord0x34 --> procTgStatusWord0x34() " << true;
        } else {
//            qDebug() << "PortManager::parcingStatusWord0x34 --X proc " << false;
        }

    }
//    qDebug() << "PortManager::parcingStatusWord0x34 <--";
    return resultRequest;
}

bool PortManager::procDkStatusWord0x34(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procDkStatusWord0x34 -->";
    if(!currentUN->getDkInvolved()
    || TypeUnitNode::TG != currentUN->getType()) {
//        qDebug() << "PortManager::procDkStatusWord0x34(1) <--";
        return false;
    }

    const auto &isAutoDK = currentUN->getIsAutoDkInvolved();

    currentUN->setStateWord(0x34u, stateWord);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procDkStatusWord0x34(1) <--";
    return true;
}

bool PortManager::procTgStatusWord0x34(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord)
{
//    qDebug() << "PortManager::procTgStatusWord0x34() -->";
    if(TypeUnitNode::TG != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procTgStatusWord0x34(1) <--";
        return false;
    }

    auto reciver = UnitNode::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procTgStatusWord0x34(2) <--";
        return false;
    }

    currentUN->setStateWord(0x34u, stateWord);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procTgStatusWord0x34(X) <--";
    return true;
}


void PortManager::procDK(QSharedPointer<UnitNode>  current, QSharedPointer<UnitNode>  previous) {
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
                DKCiclStatus::DKNorm == unCalcDkStatus)
            current->setDkStatus(DKCiclStatus::DKNorm);
        else if((DKCiclStatus::DKNorm == previous->getDkStatus() || DKCiclStatus::DKReady == previous->getDkStatus())&&
                DKCiclStatus::DKWasAlarn == unCalcDkStatus)
            current->setDkStatus(DKCiclStatus::DKWasAlarn);
        else if(DKCiclStatus::DKWasAlarn == previous->getDkStatus() &&
                DKCiclStatus::DKNorm == unCalcDkStatus)
            current->setDkStatus(DKCiclStatus::DKDone);
        else if(DKCiclStatus::DKWasAlarn == previous->getDkStatus() &&
                DKCiclStatus::DKWas == unCalcDkStatus)
            current->setDkStatus(DKCiclStatus::DKDone);
        else if((DKCiclStatus::DKNorm == previous->getDkStatus() &&
                 DKCiclStatus::DKNorm == unCalcDkStatus) ||
                (DKCiclStatus::DKWasAlarn == previous->getDkStatus() &&
                 DKCiclStatus::DKWasAlarn == unCalcDkStatus))
            current->setDkStatus(previous->getDkStatus());
        else
            current->setDkStatus(DKCiclStatus::DKWrong);
        current->updDoubl();
        qDebug() << "DkStatus -- unNewDkStatus " << mapDKCiclStatus.value(current->getDkStatus());
        qDebug() << "DkStatus <--";
    }
}


void PortManager::manageOverallReadQueue()
{
    const auto tmpQueue = popOverallReadQueue();
    for (auto itm : tmpQueue) {
        QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
//        AbstractPort * pt = m_udpPortsVector.value(itm.portIndex(), nullptr);
        if(DataQueueItem::isValideDirectionI(itm)) {
            quint8 num1Sender = itm.data().at(1);
            quint8 CMD = itm.data().at(4);
            QString hostSender = Utils::hostAddressToString(itm.address());
            switch (CMD) {
            case static_cast<quint8>(0x41): {
                for(auto scr : as_const(getLsSCR())) {
                    if(scr->getIpPort() == tmpPair &&
                       TypeUnitNode::BL_IP == static_cast<quint8>(scr->getUnReciver()->getType())) {
                        scr->resetBeatCount();
                        break;
                    }
                }
                DataQueueItem request;
                parcingStatusWord0x41(itm, request);

                break;
            }
            case static_cast<quint8>(0x42): {
                for(auto scr : as_const(getLsSCR())) {
                    if(scr->getIpPort() == tmpPair &&
                       TypeUnitNode::BL_IP == static_cast<quint8>(scr->getUnReciver()->getType())) {
                        scr->resetBeatCount();
                        break;
                    }
                }
                DataQueueItem request;
                parcingStatusWord0x42(itm, request);

                break;
            }
            case static_cast<quint8>(0x31): {
                for(auto scr : as_const(getLsSCR())) {
                    if(scr->getIpPort() == tmpPair &&
                       (TypeUnitNode::TG_Base == static_cast<quint8>(scr->getUnReciver()->getType()) ||
                        TypeUnitNode::RLM_C == static_cast<quint8>(scr->getUnReciver()->getType()) ||
                        TypeUnitNode::RLM_KRL == static_cast<quint8>(scr->getUnReciver()->getType())) &&
                       static_cast<quint8>(scr->getUnReciver()->getNum1()) == static_cast<quint8>(itm.data().at(2))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
                DataQueueItem request;
                parcingStatusWord0x31(itm, request);

                break;
            }
            case static_cast<quint8>(0x32): {
                for(auto scr : as_const(getLsSCR())) {
                    if(scr->getIpPort() == tmpPair && TypeUnitNode::TG_Base == static_cast<quint8>(scr->getUnReciver()->getType()) && static_cast<quint8>(scr->getUnReciver()->getNum1()) == static_cast<quint8>(itm.data().at(2))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
                DataQueueItem request;
                parcingStatusWord0x32(itm, request);

                break;
            }
            case static_cast<quint8>(0x33): {
                for(auto scr : as_const(getLsSCR())) {
                    if(scr->getIpPort() == tmpPair && TypeUnitNode::TG_Base == static_cast<quint8>(scr->getUnReciver()->getType()) && static_cast<quint8>(scr->getUnReciver()->getNum1()) == static_cast<quint8>(itm.data().at(2))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
                DataQueueItem request;
                parcingStatusWord0x33(itm, request);

                break;
            }
            case static_cast<quint8>(0x34): {
                for(auto scr : as_const(getLsSCR())) {
                    if(scr->getIpPort() == tmpPair && TypeUnitNode::TG_Base == static_cast<quint8>(scr->getUnReciver()->getType()) && static_cast<quint8>(scr->getUnReciver()->getNum1()) == static_cast<quint8>(itm.data().at(2))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
                DataQueueItem request;
                parcingStatusWord0x34(itm, request);

                break;
            }
            case static_cast<quint8>(0x30): {

//                qDebug() << "case static_cast<quint8>(0x30)";

                //find sender (local reciver)
                for(auto &sender : ServerSettingUtils::sortMetaRealUnitNodes()) {
                    if(sender->equale(hostSender, num1Sender)) {
                        sender->pullManagerSingleMsg();
                    }
                }

                for(auto ar : as_const(getLsWaiter())) {
                    if(ar->getIpPort() == tmpPair ) {

                        if(BeatStatus::RequestStep1 == ar->getBeatStatus()) { // переводим в первое ожидание

                            if(!ar->getUnReciver().isNull() &&
                               RequesterType::DKWaiter == ar->getRequesterType() &&
                               static_cast<quint8>(ar->getUnReciver()->getNum1()) == static_cast<quint8>(itm.data().at(2))) {
                                for(auto  un : ar.dynamicCast<ProcessDKWaiter>()->getLsTrackedUN()) {
                                    un->setDkInvolved(true);
                                    un->setDkStatus(DKCiclStatus::DKReady);
                                    un->updDoubl();
                                }
                            }

                            if(RequesterType::DKWaiter == ar->getRequesterType()) {
                                SignalSlotCommutator::emitStartDKWait(ar->getTimeIntervalWaiteFirst());
                            } else if(RequesterType::LockRequester == ar->getRequesterType()) {
                                SignalSlotCommutator::emitStartLockWait(ar->getTimeIntervalWaiteFirst());
                            }

                            ar->startWaiteSecondRequest();

                        } else if(BeatStatus::RequestStep2 == ar->getBeatStatus()) { // удаляем завершившихся и переводим во второе ожидание другие

                            finishDKWaiter(ar);

                        } else if(BeatStatus::End == ar->getBeatStatus()) { // кончаем конценных, но такого не бывает

                            if(RequesterType::LockRequester == ar->getRequesterType()) {
                                SignalSlotCommutator::emitStopLockWait();
                            }

                            removeLsWaiter(ar);

                        } else if(BeatStatus::Unsuccessful == ar->getBeatStatus() || BeatStatus::Successful == ar->getBeatStatus()) { // точно пора удалять
                            removeLsWaiter(ar);
                        }
                    }
                }
                break;
            }
            default:
                break;
            }

            bool keypass = true;
            for(auto ar : as_const(getLsWaiter())) {
                if(BeatStatus::Unsuccessful == ar->getBeatStatus() || BeatStatus::Successful == ar->getBeatStatus()) {
                    removeLsWaiter(ar); //
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

            const auto &isAutoDK = un->getIsAutoDkInvolved();

            JourEntity msg;
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setDirection(un->getDirection());

            bool needSendEventsAndStates = false;
            if(DKCiclStatus::DKDone == un->getDkStatus()) {
                msg.setComment(tr("Ком. ДК выполнена"));
                msg.setType(3);
                if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                    DataBaseManager::insertJourMsg_wS(msg);
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
                    DataBaseManager::insertJourMsg_wS(msg);
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    SoundAdjuster::playAlarm2();
                }
            }
            un->setDkInvolved(false);
            un->setDkStatus(DKCiclStatus::DKIgnore);
            un->updDoubl();
            if(needSendEventsAndStates)
                GraphTerminal::sendAbonentEventsAndStates(un);
            SignalSlotCommutator::emitUpdUN();
        }
//                                SignalSlotCommutator::getInstance()->emitStopDKWait();
//                                removeLsWaiter(ar);
    } else if(RequesterType::LockRequester == ar->getRequesterType()){

        if(RequesterType::LockRequester == ar->getRequesterType()) {
            SignalSlotCommutator::emitStartLockWait(ar->getTimeIntervalWaiteSecond());
        }

        ar->startWaiteEndSecondWaite();
    }

    if(RequesterType::LockRequester != ar->getRequesterType()) {
        if(RequesterType::DKWaiter == ar->getRequesterType()) {
            SignalSlotCommutator::emitStopDKWait();
        }
        removeLsWaiter(ar);
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
        if((un->getControl() || TypeUnitNode::IU_BL_IP == un->getType()) && !un->getName().isEmpty() && 1 != un->getMetaEntity()) {
            JourEntity msg;
            msg.setObject(un->getName());
            msg.setType(10);
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setDirection(un->getDirection());
            msg.setComment(tr("Нет связи"));
            DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(un, msg);

            if(20 == msg.getType()) {
                SoundAdjuster::playAlarm();
            } else if(10 == msg.getType() || 12 == msg.getType() || 21 == msg.getType()) {
                SoundAdjuster::playAlarm2();
            }
        }

        un->updDoubl();
    }


    for(const auto& uncld : as_const(un->getListChilde())) {
        unLostedConnect(uncld);
    }

    for(auto scr : as_const(getLsSCR())) {
        if(scr->getUnReciver() == un && BeatStatus::Unsuccessful == scr->getBeatStatus()) {
            scr->startFirstRequest();
            break;
        }
    }

    SignalSlotCommutator::emitUpdUN();

}
