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

#include "SWPBLIP.h"
#include "SWPRLM.h"
#include "SWPRLMC.h"
#include "SWPSDBLIP.h"
#include "SWPIUBLIP.h"
#include "SWPTGType0x31.h"
#include "SWPTGType0x34.h"
#include "SWPTGType0x33.h"
#include "SWPTGSubType0x33.h"
#include "SWPTGType0x32.h"
#include "SWPTGSubType0x32.h"

QSharedPointer<ShedulerDK> PortManager::shedulerDK;

PortManager::PortManager(QSharedPointer<DataBaseManager> dbm, QObject *parent) : QObject(parent), MAX_COUNT_PORTS(1), m_dbm(dbm)
{
//    m_portFactorys.reserve(1);
//    m_portFactorys.insert(Protocol::UDP, new PortFactory());

    m_udpPortsVector.reserve(MAX_COUNT_PORTS);

    connect(SignalSlotCommutator::getInstance(), SIGNAL(requestOnOffCommand(bool, QSharedPointer<UnitNode> , bool)), this, SLOT(requestOnOffCommand(bool, QSharedPointer<UnitNode> , bool)));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(lockOpenCloseCommand(bool, QSharedPointer<UnitNode> , bool)), this, SLOT(lockOpenCloseCommand(bool, QSharedPointer<UnitNode> , bool)));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(requestDK(QSharedPointer<UnitNode> )), this, SLOT(requestDK(QSharedPointer<UnitNode> )));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(autoOnOffIU(bool, QSharedPointer<UnitNode> )), this, SLOT(requestAutoOnOffIUCommand(bool, QSharedPointer<UnitNode> )));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(requestDK(bool, QSharedPointer<UnitNode> )), this, SLOT(requestDK(bool, QSharedPointer<UnitNode> )));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(alarmsReset(QSharedPointer<UnitNode> )), this, SLOT(requestAlarmReset(QSharedPointer<UnitNode> )));

    {
        CSimpleIniA ini;
        QString filePath = QCoreApplication::applicationDirPath() + "/rifx.ini";
        ini.LoadFile(filePath.toStdString().c_str());

        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

        auto autoDK = codec->toUnicode(ini.GetValue("RIF", "AutoDK"));

        if(0 != autoDK.toInt()) {
            shedulerDK = QSharedPointer<ShedulerDK>::create(QTime(autoDK.toInt(), 0));
            connect(shedulerDK.data(), SIGNAL(activated()), this, SLOT(requestDK()));
            shedulerDK->start();
        }
    }

}

QList<AbstractPort *> PortManager::m_udpPortsVector = QList<AbstractPort *>();

GraphTerminal * PortManager::graphTerminal = nullptr;


QList<QSharedPointer<AbstractRequester> > PortManager::lsSCR = QList<QSharedPointer<AbstractRequester> >();

QList<QSharedPointer<AbstractRequester> > PortManager::lsWaiter = QList<QSharedPointer<AbstractRequester> >();


//Port* PortManager::createPort(AbstractPort::Protocol protocol, QObject *parent, const int index) {
//    return new Port(protocol, parent, index, m_dbm);
//}


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
    disconnect(SignalSlotCommutator::getInstance(), SIGNAL(lostConnect(QSharedPointer<UnitNode> )), this, SLOT(unLostedConnect(QSharedPointer<UnitNode> )));

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

    connect(SignalSlotCommutator::getInstance(), SIGNAL(lostConnect(QSharedPointer<UnitNode> )), this, SLOT(unLostedConnect(QSharedPointer<UnitNode> )));
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
                        DataQueueItem::makeAlarmReset0x24(itm, selUN);

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
            DataQueueItem::makeAlarmReset0x24(itm, selUN);
            tmpCAW->setFirstMsg(itm);
            appLsWaiter(tmpCAW);
//            tmpCAW->startFirstRequest();
        }
    }
    //    write();
}

void PortManager::requestDK(QSharedPointer<UnitNode> selUN)
{
    requestDK(false, selUN);
}

void PortManager::requestDK(bool out, QSharedPointer<UnitNode> selUN) {
    //
    QList<QSharedPointer<UnitNode> > lsTrgtUN;
    if(selUN.isNull()) {
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
    } else if(!selUN.isNull()) {
        QSharedPointer<UnitNode>  un = selUN;
        lsTrgtUN.append(UnitNode::findReciver(un));
    }

    if(lsTrgtUN.isEmpty())
        return;

    if(selUN.isNull()) {
        JourEntity msg;
        msg.setObject(tr("РИФ Общий"));
        if(out) {
            msg.setComment(tr("Удал. ком. ДК Послана ком. ДК"));
            msg.setType(1133);
        } else {
            msg.setComment(tr("Послана ком. ДК"));
            msg.setType(133);
        }
        DataBaseManager::insertJourMsg_wS(msg);
        GraphTerminal::sendAbonentEventsAndStates(msg);
    }

    for(QSharedPointer<UnitNode>  un : lsTrgtUN) {
        QPair<QString, QString> tmpPair(un->getUdpAdress(), QVariant(un->getUdpPort()).toString());
        for(const auto& pt : as_const(m_udpPortsVector)) {
            if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {

                auto tmpPDKW = QSharedPointer<ProcessDKWaiter>::create(un);
                tmpPDKW->init();
                appLsWaiter(tmpPDKW);
//                tmpPDKW->startFirstRequest();
                break;
            }
        }
        if(selUN.isNull() && !un->getName().isEmpty()/* && un->getControl()*/) {
            auto tmpUN = un;
            if(1 == tmpUN->getMetaEntity()) {
                for(const auto &chld : as_const(tmpUN->getListChilde())) {
                    if(1 != chld->getMetaEntity()) {
                        tmpUN = chld;
                        break;
                    }
                }

            }
            if(!tmpUN->getName().isEmpty() && 1 != tmpUN->getMetaEntity()) {
                JourEntity msg;
                if(out) {
                    msg.setComment(tr("Удал. ком. ДК Послана ком. ДК"));
                    msg.setType(1133);
                } else {
                    msg.setComment(tr("Послана ком. ДК"));
                    msg.setType(133);
                }
                msg.setObject(tmpUN->getName());
                msg.setObjecttype(tmpUN->getType());
                msg.setD1(tmpUN->getNum1());
                msg.setD2(tmpUN->getNum2());
                msg.setD3(tmpUN->getNum3());
                msg.setDirection(tmpUN->getDirection());

                DataBaseManager::insertJourMsg_wS(msg);
                GraphTerminal::sendAbonentEventsAndStates(msg);
            }
        }
    }
    if(!selUN.isNull()/* && selUN->getControl()*/) {
        JourEntity msg;
        msg.setObjecttype(selUN->getType());
        msg.setD1(selUN->getNum1());
        msg.setD2(selUN->getNum2());
        msg.setD3(selUN->getNum3());
        msg.setDirection(selUN->getDirection());

        if(out) {
            msg.setComment(tr("Удал. ком. ДК Послана ком. ДК"));
            msg.setType(1133);
        } else {
            msg.setComment(tr("Послана ком. ДК"));
            msg.setType(133);
        }
        msg.setObject(selUN->getName());
        if(!selUN->getName().isEmpty() && 1 != selUN->getMetaEntity()) {
            DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(selUN, msg);
        }
    }
}

void PortManager::requestAutoOnOffIUCommand(QSharedPointer<UnitNode> selUN)
{
    requestAutoOnOffIUCommand(false, selUN);
}

void PortManager::requestAutoOnOffIUCommand(bool out, QSharedPointer<UnitNode> selUN) {
    if(TypeUnitNode::IU_BL_IP == selUN->getType()) {
        QPair<QString, QString> tmpPair(selUN->getUdpAdress(), QVariant(selUN->getUdpPort()).toString());
        for(const auto& pt : as_const(m_udpPortsVector)) {
            if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {
                bool needJour = true;
                for(auto ar : as_const(getLsWaiter())) {
                    if((RequesterType::AutoOnOffWaiter == ar->getRequesterType()) && (ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN))) {
                        ar->timerTripleStop();
                        ar->setBeatStatus(BeatStatus::Unsuccessful);

                        needJour = false;
//                        return;
                    }
                }

                auto tmpOOIUW = QSharedPointer<OnOffIUWaiter>::create(selUN);
                tmpOOIUW->init();
                appLsWaiter(tmpOOIUW);
//                tmpOOIUW->startFirstRequest();

                if(needJour) {
                    JourEntity msg;
                    msg.setObject(selUN->getName());
                    msg.setObjecttype(selUN->getType());
                    msg.setD1(selUN->getNum1());
                    msg.setD2(selUN->getNum2());
                    msg.setD3(selUN->getNum3());
                    msg.setType(130);
                    msg.setDirection(selUN->getDirection());

                    if(out)
                        msg.setComment(tr("Удал. ком. Вкл"));
                    else
                        msg.setComment(tr("Послана ком. Вкл"));
                    if(!selUN->getName().isEmpty() && 1 != selUN->getMetaEntity()) {
                        DataBaseManager::insertJourMsg_wS(msg);
                        GraphTerminal::sendAbonentEventsAndStates(selUN, msg);
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
    } else if(un->getStateWord().getByteWord().size() > stateWord.size()) {
        return;
    }

    auto tmpCAW = QSharedPointer<ConfirmationAdmissionWaiter>::create(un);
    tmpCAW->init();

    DataQueueItem itm = tmpCAW->getFirstMsg();
    DataQueueItem::makeOnOff0x20(itm, un);
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
        SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
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

void PortManager::requestOnOffCommand(QSharedPointer<UnitNode> selUN, bool value)
{
    requestOnOffCommand(false, selUN, value);
}

void PortManager::requestOnOffCommand(bool out, QSharedPointer<UnitNode> selUN, bool value)
{
    QSharedPointer<UnitNode>  target = selUN;

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
    if(!value) {
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

        if(TypeUnitNode::BL_IP == reciver->getType() && !target->getStateWord().getByteWord().isEmpty()) {
            quint8 D1 = 0x00; // байт для БЛ
            quint8 mask = 0x00;
            if(TypeUnitNode::SD_BL_IP == target->getType()) {
                D1 = target->getStateWord().getByteWord().at(3);
                mask = target->swpSDBLIP().mask();
            } else if(TypeUnitNode::IU_BL_IP == target->getType()) {
                D1 = target->getStateWord().getByteWord().at(1) & 0x0F;
                mask = target->swpIUBLIP().mask();
            }

            if(value)
                D1 = D1 | mask;
            else if(!value)
                D1 = D1 & ~mask;

            auto tmpCAW = QSharedPointer<ConfirmationAdmissionWaiter>::create(reciver);
            tmpCAW->init();
            DataQueueItem itm = tmpCAW->getFirstMsg();
            QByteArray data;
            if(TypeUnitNode::SD_BL_IP == target->getType()) {
                DataQueueItem::makeOnOff0x20(itm, target);
                data = itm.data();
            } else if(TypeUnitNode::IU_BL_IP == target->getType()) {
                DataQueueItem::makeOnOff0x23(itm, target);
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
            if(value)
                DataQueueItem::makeOn0x26(itm, reciver);
            else
                DataQueueItem::makeOff0x25(itm, reciver);
            tmpCAW->setFirstMsg(itm);
            appLsWaiter(tmpCAW);
        }

        JourEntity msg;
        msg.setObject(selUN->getName());
        msg.setObjecttype(selUN->getType());
        msg.setD1(selUN->getNum1());
        msg.setD2(selUN->getNum2());
        msg.setD3(selUN->getNum3());
        msg.setDirection(selUN->getDirection());

        if(out) {
            msg.setComment(tr("Удал. ком. ") + (value ? tr("Вкл") : tr("Выкл")));
            msg.setType((value ? 1000 : 1001));
        } else {
            msg.setComment(tr("Послана ком. ") + (value ? tr("Вкл") : tr("Выкл")));
            msg.setType((value ? 130 : 131));
        }
        if(!selUN->getName().isEmpty() && 1 != selUN->getMetaEntity()) {
            DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(selUN, msg);
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

DataQueueItem PortManager::parcingStatusWord0x41(DataQueueItem &item, DataQueueItem & resultRequest)
{
//    //qDebug() << "Utils::parcingStatusWord0x41 -->";
    const StateWord newStateWord(item.data().mid(5, 4));
    resultRequest = item;
    resultRequest.setData();

    const QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::getSetMetaRealUnitNodes().values();
    for(QSharedPointer<UnitNode>  un : tmpSet) {
//        if(item.address().isEqual(QHostAddress(un->getUdpAdress())) && item.port() == un->getUdpPort() && TypeUnitNode::BL_IP == un->getType()) {
//            un->setCountStatusConnectRequesterWaitAnswer(0);
//        }
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress())) || item.port() != un->getUdpPort() || static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1()))
            continue;
        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
            reciver->setStateWord(newStateWord);
        }
        QSharedPointer<UnitNode> previousCopyUNLockSdBlIp, previousCopyUNLockIuBlIp;
        QSharedPointer<UnitNode>  unLockSdBlIp, unLockIuBlIp;
        bool isLockPair = false;
        if(1 <= un->getNum2() && 4 >= un->getNum2()) {
            if(!reciver.isNull()) {
                for(const auto &tmpUN : as_const(reciver->getListChilde())) {
                    if(TypeUnitNode::IU_BL_IP == tmpUN->getType() && tmpUN->getNum2() == un->getNum2()) {
                        previousCopyUNLockIuBlIp = UnitNodeFactory::makeShare(*tmpUN);
                        unLockIuBlIp = tmpUN;
                        break;
                    }
                }

                for(const auto& tmpUN : as_const(reciver->getListChilde())) {
                    if(TypeUnitNode::SD_BL_IP == tmpUN->getType() && tmpUN->getNum2() == un->getNum2() && 0 != tmpUN->getBazalt()) {
                        previousCopyUNLockSdBlIp = UnitNodeFactory::makeShare(*tmpUN);
                        unLockSdBlIp = tmpUN;
                        break;
                    }
                }
            }

            if(unLockSdBlIp.isNull() || unLockIuBlIp.isNull()) {
//                previousCopyUNLockIuBlIp.clear();
//                previousCopyUNLockSdBlIp.clear();
//                unLockIuBlIp.clear();
//                unLockSdBlIp.clear();
                isLockPair = false;
            } else if(0 != unLockSdBlIp->getBazalt()) {
                isLockPair = true;
            }
        }
        QSharedPointer<UnitNode> previousCopyUN = UnitNodeFactory::makeShare(*un);
        un->setStateWord(newStateWord);
//        un->updDoubl();

        if(isLockPair && (!unLockSdBlIp.isNull() || !unLockIuBlIp.isNull())) {
            unLockSdBlIp->setStateWord(newStateWord);
            unLockIuBlIp->setStateWord(newStateWord);
        }

        if(TypeUnitNode::BL_IP == un->getType() && !un->swpBLIP().isNull() && !previousCopyUN->swpBLIP().isNull()) {
            if((un->swpBLIP().isWasDK() != previousCopyUN->swpBLIP().isWasDK()) ||
               (un->swpBLIP().isExistDK() != previousCopyUN->swpBLIP().isExistDK())) {
                un->setStateWord(newStateWord);if(10 == un->getPublishedState()) {un->setPublishedState(-1); }
                un->updDoubl();
                SignalSlotCommutator::getInstance()->emitUpdUN();
            }
        }

        if(0 != un->getDK() &&
           DKCiclStatus::DKIgnore != previousCopyUN->getDkStatus() &&
           DKCiclStatus::DKWrong != previousCopyUN->getDkStatus() &&
           DKCiclStatus::DKDone != previousCopyUN->getDkStatus() &&
           un->getDkInvolved()) {
//            //qDebug() << "DkStatus --> " << un->toString();
            int unCalcDkStatus = un->calcDKStatus();
//            //qDebug() << "DkStatus -- unCalcDkStatus " << unCalcDkStatus;
//            //qDebug() << "DkStatus -- unDkStatus " << un->getDkStatus();
            if(DKCiclStatus::DKReady == previousCopyUN->getDkStatus() &&
                    DKCiclStatus::DKNorm == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKNorm);
            else if((DKCiclStatus::DKNorm == previousCopyUN->getDkStatus() || DKCiclStatus::DKReady == previousCopyUN->getDkStatus())&&
                    DKCiclStatus::DKWasAlarn == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKWasAlarn);
            else if(DKCiclStatus::DKWasAlarn == previousCopyUN->getDkStatus() &&
                    DKCiclStatus::DKNorm == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKDone);
            else if(DKCiclStatus::DKWasAlarn == previousCopyUN->getDkStatus() &&
                    DKCiclStatus::DKWas == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKDone);
            else if((DKCiclStatus::DKNorm == previousCopyUN->getDkStatus() &&
                     DKCiclStatus::DKNorm == unCalcDkStatus) ||
                    (DKCiclStatus::DKWasAlarn == previousCopyUN->getDkStatus() &&
                     DKCiclStatus::DKWasAlarn == unCalcDkStatus))
                un->setDkStatus(previousCopyUN->getDkStatus());
            else
                un->setDkStatus(DKCiclStatus::DKWrong);
//            un->updDoubl();
//            //qDebug() << "DkStatus -- unNewDkStatus " << un->getDkStatus();
//            //qDebug() << "DkStatus <--";
        }

        if((!previousCopyUN.isNull() && !un.isNull() && (previousCopyUN->getStateWord().getByteWord() != un->getStateWord().getByteWord())) ||
           (!previousCopyUNLockSdBlIp.isNull() && !unLockSdBlIp.isNull() && (previousCopyUNLockSdBlIp->getStateWord().getByteWord() != unLockSdBlIp->getStateWord().getByteWord())) ||
           (!previousCopyUNLockIuBlIp.isNull() && !unLockIuBlIp.isNull() && (previousCopyUNLockIuBlIp->getStateWord().getByteWord() != unLockIuBlIp->getStateWord().getByteWord()))) {
            un->setStateWord(newStateWord);
            if(!unLockIuBlIp.isNull() && !unLockSdBlIp.isNull() && isLockPair) {
                unLockSdBlIp->setStateWord(newStateWord);
                unLockIuBlIp->setStateWord(newStateWord);
            }

//            un->updDoubl();
//            SignalSlotCommutator::getInstance()->emitUpdUN();

            if(!un->getDkInvolved()) {

                JourEntity msg;
                msg.setObject(un->getName());
                msg.setObjecttype(un->getType());
                msg.setD1(un->getNum1());
                msg.setD2(un->getNum2());
                msg.setD3(un->getNum3());
                msg.setDirection(un->getDirection());

                if(un->getDkInvolved()) {
//                    //qDebug() << "DkInvolved continue " << un->toString();
                    un->updDoubl();
                    SignalSlotCommutator::getInstance()->emitUpdUN();
                    continue;
                } else if(!un->getParentUN().isNull() && un->getParentUN()->getDkInvolved()) {
//                    //qDebug() << "DkInvolved continue " << un->toString();
                    un->updDoubl();
                    SignalSlotCommutator::getInstance()->emitUpdUN();
                    continue;
                } else if(isLockPair) { // запись сообщения УЗ
                    if(unLockSdBlIp->swpSDBLIP().isAlarm() == previousCopyUNLockSdBlIp->swpSDBLIP().isAlarm() &&
                       unLockIuBlIp->swpIUBLIP().isOff() == previousCopyUNLockIuBlIp->swpIUBLIP().isOff() &&
                       unLockSdBlIp->swpSDBLIP().isNorm() == previousCopyUNLockSdBlIp->swpSDBLIP().isNorm() &&
                       unLockIuBlIp->swpIUBLIP().isOn() == previousCopyUNLockIuBlIp->swpIUBLIP().isOn()) { // состояние не зменилось - пропускаем
                        if(10 == unLockSdBlIp->getPublishedState()) {
                            unLockSdBlIp->setPublishedState(-1);
                        }
                        if(10 == unLockIuBlIp->getPublishedState()) {
                            unLockIuBlIp->setPublishedState(-1);
                        }
                        if(10 == reciver->getPublishedState()) {
                            reciver->setPublishedState(-1);
                        }

                        unLockSdBlIp->updDoubl();
                        unLockIuBlIp->updDoubl();
                        SignalSlotCommutator::getInstance()->emitUpdUN();
                        continue;
                    } else if(
                            (1 == previousCopyUNLockSdBlIp->swpSDBLIP().isAlarm() &&
                             1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOff() && //Открыто
                             1 == unLockSdBlIp->swpSDBLIP().isAlarm() &&
                             1 == unLockIuBlIp->swpIUBLIP().isOn()) || //Открыто ключом

                            (1 == previousCopyUNLockSdBlIp->swpSDBLIP().isNorm() &&
                             1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOn() && //Закрыто
                             1 == unLockSdBlIp->swpSDBLIP().isNorm() &&
                             1 == unLockIuBlIp->swpIUBLIP().isOff())) //Закрыто ключом
                    { // запрещённая обработка перехода (Открыто -> Открыто ключом, Закрыто -> Закрыто ключом)
                        //qDebug() << "isLockPair continue " << un->toString();
                        if(10 == unLockSdBlIp->getPublishedState()) {
                            unLockSdBlIp->setPublishedState(-1);
                        }
                        if(10 == unLockIuBlIp->getPublishedState()) {
                            unLockIuBlIp->setPublishedState(-1);
                        }
                        if(10 == reciver->getPublishedState()) {
                            reciver->setPublishedState(-1);
                        }
                        unLockSdBlIp->updDoubl();
                        unLockIuBlIp->updDoubl();
                        SignalSlotCommutator::getInstance()->emitUpdUN();
                        continue;
                    }

                    if(10 == unLockSdBlIp->getPublishedState()) {
                        unLockSdBlIp->setPublishedState(-1);
                    }
                    if(10 == unLockIuBlIp->getPublishedState()) {
                        unLockIuBlIp->setPublishedState(-1);
                    }
                    if(10 == reciver->getPublishedState()) {
                        reciver->setPublishedState(-1);
                    }
                    unLockSdBlIp->updDoubl();
                    unLockIuBlIp->updDoubl();

                    // переводим на другой шаг обработчик открытия и закрытия этого УЗ
                    QPair<QString, QString> tmpPair(Utils::hostAddressToString(item.address()), QVariant(item.port()).toString());
                    for(auto ar : as_const(getLsWaiter())) {
                        if(ar->getIpPort() == tmpPair &&
                           RequesterType::LockRequester == ar->getRequesterType() &&
                           ar->getUnTarget() == unLockSdBlIp) {
                            SignalSlotCommutator::getInstance()->emitEndLockWait();
                            if(BeatStatus::RequestStep1 == ar->getBeatStatus()) {
//                                ar->startSecondRequest();
                                continue;
                            } else if(BeatStatus::Waite == ar->getBeatStatus()) {
                                ar->startSecondRequest(3000);
                            } else if(BeatStatus::RequestStep2 == ar->getBeatStatus()) {
//                                ar->startEnd();
                                continue;
                            } else if(BeatStatus::WaiteEnd == ar->getBeatStatus()) {
                                  ar->startEnd();
                            }
                        }
                    }

                    /*
                    if(1 == previousCopyUNLockSdBlIp->swpSDBLIP().isAlarm() &&
                       1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOff()) {
                        //Открыто
                        qDebug() << "isLockPair Old O " << un->toString();
                    } else if(1 == previousCopyUNLockSdBlIp->swpSDBLIP().isNorm() &&
                              1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOn()) {
                        //Закрыто
                        qDebug() << "isLockPair Old L " << un->toString();
                    } else if(1 == previousCopyUNLockSdBlIp->swpSDBLIP().isAlarm() &&
                              1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOn()) {
                        //Открыто ключом
                        qDebug() << "isLockPair Old OK " << un->toString();
                    } else if(1 == previousCopyUNLockSdBlIp->swpSDBLIP().isNorm() &&
                              1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOff()) {
                        //Закрыто ключом
                        qDebug() << "isLockPair Old LK " << un->toString();
                    }

                    if(1 == unLockSdBlIp->swpSDBLIP().isAlarm() &&
                       1 == unLockIuBlIp->swpIUBLIP().isOff()) {
                        //Открыто
                        qDebug() << "isLockPair New O " << un->toString();
                    } else if(1 == unLockSdBlIp->swpSDBLIP().isNorm() &&
                              1 == unLockIuBlIp->swpIUBLIP().isOn()) {
                        //Закрыто
                        qDebug() << "isLockPair New L " << un->toString();
                    } else if(1 == unLockSdBlIp->swpSDBLIP().isAlarm() &&
                              1 == unLockIuBlIp->swpIUBLIP().isOn()) {
                        //Открыто ключом
                        qDebug() << "isLockPair New OK " << un->toString();
                    } else if(1 == unLockSdBlIp->swpSDBLIP().isNorm() &&
                              1 == unLockIuBlIp->swpIUBLIP().isOff()) {
                        //Закрыто ключом
                        qDebug() << "isLockPair New LK " << un->toString();
                    }
                    */


                    if(
                    (1 == previousCopyUNLockSdBlIp->swpSDBLIP().isAlarm() &&
                     1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOn() &&  //Открыто ключом
                     1 == unLockSdBlIp->swpSDBLIP().isAlarm() &&
                     1 == unLockIuBlIp->swpIUBLIP().isOff()) ||//Открыто

                    (1 == previousCopyUNLockSdBlIp->swpSDBLIP().isNorm() &&
                     1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOff() && //Закрыто ключом
                     1 == unLockSdBlIp->swpSDBLIP().isNorm() &&
                     1 == unLockIuBlIp->swpIUBLIP().isOn()) || //Закрыто

                    (1 == previousCopyUNLockSdBlIp->swpSDBLIP().isAlarm() &&
                     1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOff() && //Открыто
                     1 == unLockSdBlIp->swpSDBLIP().isAlarm() &&
                     1 == unLockIuBlIp->swpIUBLIP().isOn()) || //Открыто ключом

                     (1 == previousCopyUNLockSdBlIp->swpSDBLIP().isNorm() &&
                      1 == previousCopyUNLockIuBlIp->swpIUBLIP().isOn() && //Закрыто
                      1 == unLockSdBlIp->swpSDBLIP().isNorm() &&
                      1 == unLockIuBlIp->swpIUBLIP().isOff())) //Закрыто ключом
                    { // запрещённая запись перехода (Открыто <-> Открыто ключом, Закрыто <-> Закрыто ключом)
                        qDebug() << "isLockPair not jour " << un->toString();
                    } else {                        
                        msg.setObject(unLockSdBlIp->getName());

    //                    qDebug() << "isLockPair " << un->getName();
                        if(1 == unLockSdBlIp->swpSDBLIP().isAlarm() &&
                           1 == unLockIuBlIp->swpIUBLIP().isOff() &&
                           (unLockSdBlIp->swpSDBLIP().isAlarm() != previousCopyUNLockSdBlIp->swpSDBLIP().isAlarm() ||
                            unLockIuBlIp->swpIUBLIP().isOff() != previousCopyUNLockIuBlIp->swpIUBLIP().isOff())) {
                            //Открыто
                            msg.setComment(QObject::tr("Открыто"));
                            msg.setType(111);
                            un->setPublishedState(111);
                            unLockIuBlIp->setPublishedState(100);
                        } else if(1 == unLockSdBlIp->swpSDBLIP().isNorm() &&
                                  1 == unLockIuBlIp->swpIUBLIP().isOn() &&
                                  (unLockSdBlIp->swpSDBLIP().isNorm() != previousCopyUNLockSdBlIp->swpSDBLIP().isNorm() ||
                                   unLockIuBlIp->swpIUBLIP().isOn() != previousCopyUNLockIuBlIp->swpIUBLIP().isOn())) {
                            //Закрыто
                            msg.setComment(QObject::tr("Закрыто"));
                            msg.setType(110);
                            un->setPublishedState(110);
                            unLockIuBlIp->setPublishedState(101);
                        } else if(1 == unLockSdBlIp->swpSDBLIP().isAlarm() &&
                                  1 == unLockIuBlIp->swpIUBLIP().isOn() &&
                                  (unLockSdBlIp->swpSDBLIP().isAlarm() != previousCopyUNLockSdBlIp->swpSDBLIP().isAlarm() ||
                                   unLockIuBlIp->swpIUBLIP().isOn() != previousCopyUNLockIuBlIp->swpIUBLIP().isOn())) {
                            //Открыто ключом
                            msg.setComment(QObject::tr("Открыто ключом"));
                            msg.setType(113);
                            un->setPublishedState(113);
                            unLockIuBlIp->setPublishedState(101);
                        } else if(1 == unLockSdBlIp->swpSDBLIP().isNorm() &&
                                  1 == unLockIuBlIp->swpIUBLIP().isOff() &&
                                  (unLockSdBlIp->swpSDBLIP().isNorm() != previousCopyUNLockSdBlIp->swpSDBLIP().isNorm() ||
                                   unLockIuBlIp->swpIUBLIP().isOff() != previousCopyUNLockIuBlIp->swpIUBLIP().isOff())) {
                            //Закрыто ключом
                            msg.setComment(QObject::tr("Закрыто ключом"));
                            msg.setType(112);
                            un->setPublishedState(112);
                            unLockIuBlIp->setPublishedState(100);
                        }

                        if(1 != un->getMetaEntity()) {

                            qDebug() << "Загадочные события с УЗ продолжаются, надо вести лог и разобраться... -->";
                            qDebug() << un->toString();
                            qDebug() << "current: " << unLockSdBlIp->swpBLIP().byteWord().toHex();
                            qDebug() << "previous:" << previousCopyUNLockSdBlIp->swpBLIP().byteWord().toHex();
                            qDebug() << "Загадочные события с УЗ продолжаются, надо вести лог и разобраться... <--";

                            SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                            GraphTerminal::sendAbonentEventsAndStates(un, msg);
                            if(113 == msg.getType()) {
                                SoundAdjuster::instance().playAlarm();
                            }

                        } else if(1 != unLockSdBlIp->getMetaEntity()) {
                            msg.setObject(unLockSdBlIp->getName());
                            msg.setObjecttype(unLockSdBlIp->getType());
                            msg.setD1(unLockSdBlIp->getNum1());
                            msg.setD2(unLockSdBlIp->getNum2());
                            msg.setD3(unLockSdBlIp->getNum3());
                            msg.setDirection(unLockSdBlIp->getDirection());

                            qDebug() << "Загадочные события с УЗ продолжаются, надо вести лог и разобраться... -->";
                            qDebug() << un->toString();
                            qDebug() << "current: " << unLockSdBlIp->swpBLIP().byteWord().toHex();
                            qDebug() << "previous:" << previousCopyUNLockSdBlIp->swpBLIP().byteWord().toHex();
                            qDebug() << "Загадочные события с УЗ продолжаются, надо вести лог и разобраться... <--";

                            SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                            GraphTerminal::sendAbonentEventsAndStates(unLockSdBlIp, msg);
                            if(113 == msg.getType()) {
                                SoundAdjuster::instance().playAlarm();
                            }

                        } else if(1 != unLockIuBlIp->getMetaEntity()) {
                            msg.setObject(unLockIuBlIp->getName());
                            msg.setObjecttype(unLockIuBlIp->getType());
                            msg.setD1(unLockIuBlIp->getNum1());
                            msg.setD2(unLockIuBlIp->getNum2());
                            msg.setD3(unLockIuBlIp->getNum3());
                            msg.setDirection(unLockIuBlIp->getDirection());

                            qDebug() << "Загадочные события с УЗ продолжаются, надо вести лог и разобраться... -->";
                            qDebug() << un->toString();
                            qDebug() << "current: " << unLockSdBlIp->swpBLIP().byteWord().toHex();
                            qDebug() << "previous:" << previousCopyUNLockSdBlIp->swpBLIP().byteWord().toHex();
                            qDebug() << "Загадочные события с УЗ продолжаются, надо вести лог и разобраться... <--";

                            SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                            GraphTerminal::sendAbonentEventsAndStates(unLockIuBlIp, msg);
                            if(113 == msg.getType()) {
                                SoundAdjuster::instance().playAlarm();
                            }
                        }

                    }

                } else { // запись сообщения СД или ИУ

                    if((TypeUnitNode::SD_BL_IP == un->getType() && 1 != un->getBazalt()) &&
                       (1 == un->swpSDBLIP().isOn()) &&
                       (1 == un->swpSDBLIP().isAlarm()) && (1 == un->swpSDBLIP().isWasAlarm())) { // сброс тревоги
                        //нужен сброс
                        auto alarmReset0x24 = resultRequest;
                        DataQueueItem::makeAlarmReset0x24(alarmReset0x24, un);
                        if(!reciver.isNull())
                            reciver->queueMsg.enqueue(alarmReset0x24);
                        qDebug() << "PortManager::parcingStatusWord0x41 -- DataQueueItem::makeAlarmReset0x24(" << resultRequest.data().toHex() << ", " << un->toString() << ");";

                    }

                    // запись вкл/выкл СД
                    if((TypeUnitNode::SD_BL_IP == un->getType() && 1 != un->getBazalt()) &&
                       (1 == un->swpSDBLIP().isOff()) &&
                       (0 == previousCopyUN->swpSDBLIP().isOff())) {
                        msg.setComment(QObject::tr("Выкл"));
                        msg.setType(100);
                        reciver->setPublishedState(100);
                    } else if((TypeUnitNode::SD_BL_IP == un->getType() && 1 != un->getBazalt()) &&
                              (1 == un->swpSDBLIP().isOn()) &&
                              (0 == previousCopyUN->swpSDBLIP().isOn())) {
                        msg.setComment(QObject::tr("Вкл"));
                        msg.setType(101);
                        reciver->setPublishedState(101);
                    }                    
                    if(1 != un->getMetaEntity() && 0 != msg.getType()) {
                        SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    }
                    msg.setType(0);

                    // запись тревог и нормы СД
                    if((TypeUnitNode::SD_BL_IP == un->getType() && 1 != un->getBazalt()) &&
                       (1 == un->swpSDBLIP().isOn()) &&
                       (1 == un->swpSDBLIP().isAlarm() && 1 == un->swpSDBLIP().isWasAlarm()) &&
                       (previousCopyUN->swpSDBLIP().isAlarm() != un->swpSDBLIP().isAlarm() || previousCopyUN->swpSDBLIP().isWasAlarm() != un->swpSDBLIP().isWasAlarm())) {
                        //сохранение Тревога или Норма
                        msg.setComment(QObject::tr("Тревога-СРАБОТКА"));
                        msg.setType(20);
                        un->setPublishedState(20);
                        reciver->setPublishedState(20);
                    } else if((TypeUnitNode::SD_BL_IP == un->getType() && 1 != un->getBazalt()) &&
                              (1 == un->swpSDBLIP().isOn()) &&
                              (1 == un->swpSDBLIP().isNorm()) &&
                              (un->swpSDBLIP().isNorm() != previousCopyUN->swpSDBLIP().isNorm()) &&
                              1 != un->getPublishedState()) {
                        msg.setComment(QObject::tr("Норма"));
                        msg.setType(1);
                        un->setPublishedState(1);
                        reciver->setPublishedState(1);
                    }
                    if(un->getControl() && 1 != un->getMetaEntity() && 0 != msg.getType()) {
                        SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                        if(20 == msg.getType()) {
                            SoundAdjuster::instance().playAlarm();
                        } else if(10 == msg.getType() || 12 == msg.getType() || 21 == msg.getType()) {
                            SoundAdjuster::instance().playAlarm2();
                        }
                    }
                    msg.setType(0);

                    // запись вкл/выкл ИУ
                    if((TypeUnitNode::IU_BL_IP == un->getType()) &&
                        (1 == un->swpIUBLIP().isOff()) &&
                        (previousCopyUN->swpIUBLIP().isOff() != un->swpIUBLIP().isOff())) {
                        msg.setComment(QObject::tr("Выкл"));
                        msg.setType(100);
                        un->setPublishedState(100);
                        reciver->setPublishedState(100);
                        qDebug() << un << "!!! OFF !!!" << un->toString() << un->getDoubles();
                    } else if((TypeUnitNode::IU_BL_IP == un->getType()) &&
                              (1 == un->swpIUBLIP().isOn()) &&
                              (previousCopyUN->swpIUBLIP().isOn() != un->swpIUBLIP().isOn())) {
                        msg.setComment(QObject::tr("Вкл"));
                        msg.setType(101);
                        un->setPublishedState(101);
                        reciver->setPublishedState(101);
                        qDebug() << un << "!!! ON !!!" << un->toString() << un->getDoubles();
                    }
                    if(1 != un->getMetaEntity() && 0 != msg.getType()) {
                        SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    }
                    msg.setType(0);

                    if(10 == un->getPublishedState()) {
                        un->setPublishedState(-1);
                    }
                    if(10 == reciver->getPublishedState()) {
                        reciver->setPublishedState(-1);
                    }

                }
            }

//            un->updDoubl();
//            SignalSlotCommutator::getInstance()->emitUpdUN();

            if(!un->getDkInvolved() && (TypeUnitNode::SD_BL_IP == un->getType() /*&& 0 != un->getBazalt()*/) &&
               (1 == un->swpSDBLIP().isOn()) &&
               (1 == un->swpSDBLIP().isAlarm() && 1 == un->swpSDBLIP().isWasAlarm()) &&
               (previousCopyUN->swpSDBLIP().isAlarm() != un->swpSDBLIP().isAlarm() || previousCopyUN->swpSDBLIP().isWasAlarm() != un->swpSDBLIP().isWasAlarm())) {
                //сохранение Тревога или Норма
                for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(un))) {
                    SignalSlotCommutator::getInstance()->emitAutoOnOffIU(qSharedPointerCast<UnitNode>(iuun));
                }
                //нужен сброс
            }
        }
        un->updDoubl();
        SignalSlotCommutator::getInstance()->emitUpdUN();

    }
//    //qDebug() << "Utils::parcingStatusWord0x41 <--";
    return resultRequest;
}

DataQueueItem PortManager::parcingStatusWord0x31(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "PortManager::parcingStatusWord0x31 --> " << item.address() << static_cast<quint8>(item.data().at(2));
    StateWord newStateWord(item.data().mid(5, item.data().at(3)));
    resultRequest = item;
    resultRequest.setData();

    const QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::getSetMetaRealUnitNodes().values();
    for(QSharedPointer<UnitNode>  un : tmpSet) {
        if(TypeUnitNode::RLM_C != un->getType() &&
           TypeUnitNode::RLM_KRL != un->getType() &&
           TypeUnitNode::TG != un->getType())
            continue;
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress())) ||
           item.port() != un->getUdpPort() ||
           static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1())) {
//            qDebug() << "PortManager::parcingStatusWord0x31 -- continue(1)";
            continue;
        }
        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
        }

        QSharedPointer<UnitNode> previousCopyUN = UnitNodeFactory::makeShare(*un);

        if(un.isNull() || previousCopyUN.isNull()) {
//            previousCopyUN.clear();
            qDebug() << "PortManager::parcingStatusWord0x31 -- continue(2)";
            continue;
        }

        un->setStateWord(newStateWord);
//        un->updDoubl();
//        SignalSlotCommutator::getInstance()->emitUpdUN();

        if(!un->getDkInvolved() && (
           (TypeUnitNode::RLM_C == un->getType() && 1 == un->swpRLMC().isOn() && (1 == un->swpRLMC().isInAlarm() || 1 == un->swpRLMC().isOutAlarm() || 1 == un->swpRLMC().isWasAlarm())) ||
           (TypeUnitNode::RLM_KRL == un->getType() && 1 == un->swpRLM().isOn() && (1 == un->swpRLM().isInAlarm() || 1 == un->swpRLM().isOutAlarm() || 1 == un->swpRLM().isWasAlarm())) ||
           (TypeUnitNode::TG == un->getType() && 1 == un->swpTGType0x31().isOn() && (1 == un->swpTGType0x31().isInAlarm() || 1 == un->swpTGType0x31().isOutAlarm() || 1 == un->swpTGType0x31().isWasAlarm() || 1 == un->swpTGType0x31().isInOpened() || 1 == un->swpTGType0x31().isWasOpened())))) {
            //нужен сброс
            auto alarmReset0x24 = resultRequest;
            DataQueueItem::makeAlarmReset0x24(alarmReset0x24, un);
            if(!reciver.isNull()) {
                reciver->queueMsg.enqueue(alarmReset0x24);
//                qDebug() << "PortManager::parcingStatusWord0x31 (1) -- DataQueueItem::makeAlarmReset0x24(" << resultRequest.data().toHex() << ", " << un->toString() << ");";
            }
        }

        if(un->getDkInvolved()) {
//            qDebug() << "PortManager::parcingStatusWord0x31 -- procDK " << un->toString();
            if(DKCiclStatus::DKDone != un->getDkStatus()) {
                procDK(un, previousCopyUN);
                if(DKCiclStatus::DKDone == un->getDkStatus()) {
                    for(const auto &ar : as_const(getLsWaiter())) {
                         if(RequesterType::DKWaiter == ar->getRequesterType()) {
                             auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                             if(dwWaiter->removeLsTrackedUN(un)) {
                                 if(0 == dwWaiter->getLsTrackedUN().size()) {
                                     removeLsWaiter(dwWaiter);
                                     SignalSlotCommutator::getInstance()->emitStopDKWait();
                                 }
                                 qDebug() << "PortManager::removeLsTrackedUN(" << un->toString() << ")";
                                 break;
                             }
                         }
                    }
                    JourEntity msg;
                    msg.setObject(un->getName());
                    msg.setObjecttype(un->getType());
                    msg.setD1(un->getNum1());
                    msg.setD2(un->getNum2());
                    msg.setD3(un->getNum3());
                    msg.setDirection(un->getDirection());
                    msg.setComment(tr("Ком. ДК выполнена"));
                    msg.setType(3);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);

                    un->setPublishedState(-1);
                }
            }
            if(/*!un->getDkInvolved() &&*/ (
               (TypeUnitNode::RLM_C == un->getType() && 1 == un->swpRLMC().isOn() && (1 == un->swpRLMC().isInAlarm() || 1 == un->swpRLMC().isOutAlarm() || 1 == un->swpRLMC().isWasAlarm())) ||
               (TypeUnitNode::RLM_KRL == un->getType() && 1 == un->swpRLM().isOn() && (1 == un->swpRLM().isInAlarm() || 1 == un->swpRLM().isOutAlarm() || 1 == un->swpRLM().isWasAlarm())) ||
               (TypeUnitNode::TG == un->getType() && 1 == un->swpTGType0x31().isOn() && (1 == un->swpTGType0x31().isInAlarm() || 1 == un->swpTGType0x31().isOutAlarm() || 1 == un->swpTGType0x31().isWasAlarm() || 1 == un->swpTGType0x31().isInOpened() || 1 == un->swpTGType0x31().isWasOpened())))) {
                //нужен сброс
                auto alarmReset0x24 = resultRequest;
                DataQueueItem::makeAlarmReset0x24(alarmReset0x24, un);
                if(!reciver.isNull()) {
                    reciver->queueMsg.enqueue(alarmReset0x24);
//                    qDebug() << "PortManager::parcingStatusWord0x31 (2) -- DataQueueItem::makeAlarmReset0x24(" << resultRequest.data().toHex() << ", " << un->toString() << ");";
                }
            }
        }

        bool wasDetectedNew20 = false;
        if(!previousCopyUN.isNull() && !un.isNull() && (previousCopyUN->getStateWord().getByteWord() != un->getStateWord().getByteWord()) && !un->getDkInvolved()) {

            JourEntity msg;
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setDirection(un->getDirection());

            if(TypeUnitNode::RLM_C != un->getType() && TypeUnitNode::RLM_KRL != un->getType() && TypeUnitNode::TG != un->getType()) {
//                    previousCopyUN.clear();
                qDebug() << "PortManager::parcingStatusWord0x31 -- continue(3)";
                continue;
            } else if(/*un->getControl() && */TypeUnitNode::RLM_KRL == un->getType()) {

                // запись вкл/выкл РЛМ
                if((1 == un->swpRLM().isOff()) &&
                   (0 == previousCopyUN->swpRLM().isOff())) {
                    msg.setComment(QObject::tr("Выкл"));
                    msg.setType(100);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                } else if((1 == un->swpRLM().isOn()) &&
                          (0 == previousCopyUN->swpRLM().isOn())) {
                    msg.setComment(QObject::tr("Вкл"));
                    msg.setType(101);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                }
                if(1 != un->getMetaEntity() && 0 != msg.getType()) {
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                }
                msg.setType(0);

                if(10 == un->getPublishedState()) {
                    un->setPublishedState(-1);
                }

                // запись тревога/норма РЛМ
                if((1 == un->swpRLM().isFault()) &&
                   (un->swpRLM().isFault() != previousCopyUN->swpRLM().isFault())) {
                    //сохранение неисправность или Норма
                    msg.setComment(QObject::tr("Неисправность"));
                    msg.setType(12);
                    un->setPublishedState(12);
                } else if((1 == un->swpRLM().isOn()) &&
                          (1 == un->swpRLM().isOpened() && 1 == un->swpRLM().isWasOpened()) &&
                          (previousCopyUN->swpRLM().isOpened() != un->swpRLM().isOpened() || previousCopyUN->swpRLM().isWasOpened() != un->swpRLM().isWasOpened())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-ВСКРЫТИЕ"));
                    msg.setType(21);
                    un->setPublishedState(21);
                } else if((1 == un->swpRLM().isOn()) &&
                          (1 == un->swpRLM().isAlarm() && 1 == un->swpRLM().isWasAlarm()) &&
                          (previousCopyUN->swpRLM().isAlarm() != un->swpRLM().isAlarm() || previousCopyUN->swpRLM().isWasAlarm() != un->swpRLM().isWasAlarm())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-СРАБОТКА"));
                    msg.setType(20);
                    un->setPublishedState(20);
                    wasDetectedNew20 = true;
                } else if((1 == un->swpRLM().isOn()) &&
                          (1 == un->swpRLM().isNorm()) &&
                          (previousCopyUN->swpRLM().isNorm() != un->swpRLM().isNorm()) &&
                          1 != un->getPublishedState()) {
                    msg.setComment(QObject::tr("Норма"));
                    msg.setType(1);
                    un->setPublishedState(1);
                }
                if(1 != un->getMetaEntity() && un->getControl() && 0 != msg.getType()) {
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    if(20 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm();
                    } else if(10 == msg.getType() || 12 == msg.getType() || 21 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm2();
                    }
                }
                msg.setType(0);

            } else if(TypeUnitNode::RLM_C == un->getType()) {

                // запись вкл/выкл РЛМ-С
                if((1 == un->swpRLMC().isOff()) &&
                   (0 == previousCopyUN->swpRLMC().isOff())) {
                    msg.setComment(QObject::tr("Выкл"));
                    msg.setType(100);
                } else if((1 == un->swpRLMC().isOn()) &&
                          ( 0== previousCopyUN->swpRLMC().isOn())) {
                    msg.setComment(QObject::tr("Вкл"));
                    msg.setType(101);
                }
                if(1 != un->getMetaEntity() && 0 != msg.getType()) {
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                }
                msg.setType(0);

                if(10 == un->getPublishedState()) {
                    un->setPublishedState(-1);
                }

                // запись тревога/норма РЛМ-С
                if((1 == un->swpRLMC().isFault()) &&
                   (un->swpRLMC().isFault() != previousCopyUN->swpRLMC().isFault())) {
                    //сохранение неисправность или Норма
                    msg.setComment(QObject::tr("Неисправность"));
                    msg.setType(12);
                    un->setPublishedState(12);
                } else if((1 == un->swpRLMC().isOn()) &&
                          (1 == un->swpRLMC().isAlarm() && 1 == un->swpRLMC().isWasAlarm()) &&
                          (previousCopyUN->swpRLMC().isAlarm() != un->swpRLMC().isAlarm() || previousCopyUN->swpRLMC().isWasAlarm() != un->swpRLMC().isWasAlarm())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-СРАБОТКА"));
                    msg.setType(20);
                    un->setPublishedState(20);
                    wasDetectedNew20 = true;
                } else if((1 == un->swpRLMC().isOn()) &&
                          (1 == un->swpRLMC().isNorm()) &&
                          (previousCopyUN->swpRLMC().isNorm() != un->swpRLMC().isNorm()) &&
                          1 != un->getPublishedState()) {
                    msg.setComment(QObject::tr("Норма"));
                    msg.setType(1);
                    un->setPublishedState(1);
                }
                if(un->getControl() && 1 != un->getMetaEntity() && 0 != msg.getType()) {
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    if(20 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm();
                    } else if(10 == msg.getType() || 12 == msg.getType() || 21 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm2();
                    }
                }
                msg.setType(0);

            } else if(/*un->getControl() && */TypeUnitNode::TG == un->getType()) {

                if(10 == un->getPublishedState()) {
                    un->setPublishedState(-1);
                }

                // запись тревога/норма ТГ
                if(un->getControl() &&
                   (1 == un->swpTGType0x31().isOn() && 1 == un->swpTGType0x31().isOpened()) &&
                   (previousCopyUN->swpTGType0x31().isOpened() != un->swpTGType0x31().isOpened())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-ВСКРЫТИЕ"));
                    msg.setType(21);
                    un->setPublishedState(21);
                } else if(un->getControl() &&
                          (1 == un->swpTGType0x31().isOn() && 1 == un->swpTGType0x31().isAlarm()) &&
                          (previousCopyUN->swpTGType0x31().isAlarm() != un->swpTGType0x31().isAlarm())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-СРАБОТКА"));
                    msg.setType(20);
                    un->setPublishedState(20);
                    wasDetectedNew20 = true;
                } else if(un->getControl() &&
                          (1 == un->swpTGType0x31().isNorm()) &&
                          (previousCopyUN->swpTGType0x31().isNorm() != un->swpTGType0x31().isNorm()) &&
                          1 != un->getPublishedState()) {
                    msg.setComment(QObject::tr("Норма"));
                    msg.setType(1);
                    un->setPublishedState(1);
                }
                if(un->getControl() && 1 != un->getMetaEntity() && 0 != msg.getType()) {
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    if(20 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm();
                    } else if(10 == msg.getType() || 12 == msg.getType() || 21 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm2();
                    }
                }
                msg.setType(0);
            }
        }

        un->updDoubl();
        SignalSlotCommutator::getInstance()->emitUpdUN();

        if(!un->getDkInvolved() && wasDetectedNew20) {
            //сохранение Тревога или Норма
            for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(un))) {
                SignalSlotCommutator::getInstance()->emitAutoOnOffIU(qSharedPointerCast<UnitNode>(iuun));
            }
            //нужен сброс
        }

//        previousCopyUN.clear();
//        qDebug() << "PortManager::parcingStatusWord0x31 -- break(1)";
//        break;
    }
//    qDebug() << "PortManager::parcingStatusWord0x31 <--";
    return resultRequest;
}

DataQueueItem PortManager::parcingStatusWord0x32(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "PortManager::parcingStatusWord0x32 -->";
    StateWord newStateWord(item.data().mid(5, item.data().at(3)));
    resultRequest = item;
    resultRequest.setData();

    const QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::getSetMetaRealUnitNodes().values();
    for(QSharedPointer<UnitNode>  un : tmpSet) {
        if(TypeUnitNode::TG != un->getType())
            continue;
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress())) ||
           item.port() != un->getUdpPort() ||
           static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1())) {
//            qDebug() << "PortManager::parcingStatusWord0x32 -- continue(1)";
            continue;
        }
        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
        }

        auto previousSWP = un->swpTGType0x32();
        QSharedPointer<UnitNode> previousCopyUN = UnitNodeFactory::makeShare(*un);

        un->setStateWordType0x32(newStateWord);
//        un->updDoubl();
//        SignalSlotCommutator::getInstance()->emitUpdUN();

        auto currentSWP = un->swpTGType0x32();
        int ci = un->getNum2();

        if(TypeUnitNode::TG == un->getType() && (1 == currentSWP.isAlarm() || 1 == currentSWP.isOpened() ||
                                                 1 == currentSWP.C(ci).isOutAlarm() || 1 == currentSWP.C(ci).isInAlarm() || 1 == currentSWP.C(ci).isInOpened()  || 1 == currentSWP.C(ci).isWasOpened())) {
            //нужен сброс
            auto alarmReset0x24 = resultRequest;
            DataQueueItem::makeAlarmReset0x24(alarmReset0x24, un);
            if(!reciver.isNull())
                reciver->queueMsg.enqueue(alarmReset0x24);
//                qDebug() << "PortManager::parcingStatusWord0x32 -- DataQueueItem::makeAlarmReset0x24(" << resultRequest.data().toHex() << ", " << un->toString() << ");";
        }

        if(un->getDkInvolved()) {
            // обработка дк
            if(DKCiclStatus::DKDone != un->getDkStatus()) {
//                qDebug() << "PortManager::parcingStatusWord0x32 -- procDK";
                procDK(un, previousCopyUN);
                if(DKCiclStatus::DKDone == un->getDkStatus()) {
                    for(const auto &ar : as_const(getLsWaiter())) {
                         if(RequesterType::DKWaiter == ar->getRequesterType()) {
                             auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                             if(dwWaiter->removeLsTrackedUN(un)) {
                                 if(0 == dwWaiter->getLsTrackedUN().size()) {
                                     removeLsWaiter(dwWaiter);
                                     SignalSlotCommutator::getInstance()->emitStopDKWait();
                                 }
                                 qDebug() << "PortManager::removeLsTrackedUN(" << un->toString() << ")";
                                 break;
                             }
                         }
                    }
                    JourEntity msg;
                    msg.setObject(un->getName());
                    msg.setObjecttype(un->getType());
                    msg.setD1(un->getNum1());
                    msg.setD2(un->getNum2());
                    msg.setD3(un->getNum3());
                    msg.setDirection(un->getDirection());
                    msg.setComment(tr("Ком. ДК выполнена"));
                    msg.setType(3);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);

                    un->setPublishedState(-1);
                }
            }
            if(/*!un->getDkInvolved() &&*/ (
               (TypeUnitNode::RLM_C == un->getType() && 1 == un->swpRLMC().isOn() && (1 == un->swpRLMC().isInAlarm() || 1 == un->swpRLMC().isOutAlarm() || 1 == un->swpRLMC().isWasAlarm())) ||
               (TypeUnitNode::RLM_KRL == un->getType() && 1 == un->swpRLM().isOn() && (1 == un->swpRLM().isInAlarm() || 1 == un->swpRLM().isOutAlarm() || 1 == un->swpRLM().isWasAlarm())) ||
               (TypeUnitNode::TG == un->getType() && 1 == un->swpTGType0x31().isOn() && (1 == un->swpTGType0x31().isInAlarm() || 1 == un->swpTGType0x31().isOutAlarm() || 1 == un->swpTGType0x31().isWasAlarm() || 1 == un->swpTGType0x31().isInOpened() || 1 == un->swpTGType0x31().isWasOpened())))) {
                //нужен сброс
                auto alarmReset0x24 = resultRequest;
                DataQueueItem::makeAlarmReset0x24(alarmReset0x24, un);
                if(!reciver.isNull()) {
                    reciver->queueMsg.enqueue(alarmReset0x24);
//                    qDebug() << "PortManager::parcingStatusWord0x32 -- DataQueueItem::makeAlarmReset0x24(" << resultRequest.data().toHex() << ", " << un->toString() << ");";
                }
            }
        }

        bool wasDetectedNew20 = false;

        if(!un.isNull() && (currentSWP.getStateWord().getByteWord() != previousSWP.getStateWord().getByteWord()) && !un->getDkInvolved()) {

            // Первое сообщение о включении
            JourEntity msg;
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setDirection(un->getDirection());

            if(TypeUnitNode::TG != un->getType()) {
//                    previousCopyUN.clear();
//                    qDebug() << "PortManager::parcingStatusWord0x32 -- continue(3)";
                continue;
            } else if(TypeUnitNode::TG == un->getType() && (1 <= un->getNum2() && 4 >= un->getNum2())) {
                //Сообщения в журнал

                if(10 == un->getPublishedState()) {
                    un->setPublishedState(-1);
                }

                if((1 == currentSWP.C(ci).isFault()) &&
                   (currentSWP.C(ci).isFault() != previousSWP.C(ci).isFault())) {
                    //сохранение неисправность или Норма
                    msg.setComment(QObject::tr("Неисправность"));
                    msg.setType(12);
                    un->setPublishedState(12);
                } else if((1 == currentSWP.C(ci).isOpened()) &&
                    (currentSWP.C(ci).isOpened() != previousSWP.C(ci).isOpened())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-ВСКРЫТИЕ"));
                    msg.setType(21);
                    un->setPublishedState(21);
                } else if((1 == currentSWP.C(ci).isAlarm()) &&
                   (previousSWP.C(ci).isAlarm() != currentSWP.C(ci).isAlarm())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-СРАБОТКА"));
                    msg.setType(20);
                    un->setPublishedState(20);
                    wasDetectedNew20 = true;
                } else if((1 == currentSWP.C(ci).isNorm()) &&
                          (previousSWP.C(ci).isNorm() != currentSWP.C(ci).isNorm()) &&
                          1 != un->getPublishedState()) {
                    msg.setComment(QObject::tr("Норма"));
                    msg.setType(1);
                    un->setPublishedState(1);
                }
                if(un->getControl() && 1 != un->getMetaEntity() && 0 != msg.getType()) {
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    if(20 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm();
                    } else if(10 == msg.getType() || 12 == msg.getType() || 21 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm2();
                    }
                }
                msg.setType(0);
            }
        }

        un->updDoubl();
        SignalSlotCommutator::getInstance()->emitUpdUN();

        if(!un->getDkInvolved() && wasDetectedNew20) {
            //сохранение Тревога или Норма
            for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(un))) {
                SignalSlotCommutator::getInstance()->emitAutoOnOffIU(qSharedPointerCast<UnitNode>(iuun));
            }
            //нужен сброс
        }
    }

//        previousCopyUN.clear();
//        qDebug() << "PortManager::parcingStatusWord0x32 -- break(1)";
//        break;
//    qDebug() << "PortManager::parcingStatusWord0x32 <--";
    return resultRequest;
}

DataQueueItem PortManager::parcingStatusWord0x33(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "PortManager::parcingStatusWord0x33 -->";
    StateWord newStateWord(item.data().mid(5, item.data().at(3)));
    resultRequest = item;
    resultRequest.setData();

    const QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::getSetMetaRealUnitNodes().values();
    for(QSharedPointer<UnitNode>  un : tmpSet) {
        if(TypeUnitNode::TG != un->getType())
            continue;
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress())) ||
           item.port() != un->getUdpPort() ||
           static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1())) {
//            qDebug() << "PortManager::parcingStatusWord0x33 -- continue(1)";
            continue;
        }
        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
        }

        auto previousSWP = un->swpTGType0x33();
        QSharedPointer<UnitNode> previousCopyUN = UnitNodeFactory::makeShare(*un);

        un->setStateWordType0x33(newStateWord);
//        un->updDoubl();
//        SignalSlotCommutator::getInstance()->emitUpdUN();

        auto currentSWP = un->swpTGType0x33();
        int ci = un->getNum2();

        if(TypeUnitNode::TG == un->getType() && (1 == currentSWP.isAlarm() || 1 == currentSWP.isOpened() ||
                                                 1 == currentSWP.C(ci).isInAlarm() || 1 == currentSWP.C(ci).isOutAlarm() || 1 == currentSWP.C(ci).isInOpened()  || 1 == currentSWP.C(ci).isWasOpened())) {
            //нужен сброс
            auto alarmReset0x24 = resultRequest;
            DataQueueItem::makeAlarmReset0x24(alarmReset0x24, un);
            if(!reciver.isNull()) {
                reciver->queueMsg.enqueue(alarmReset0x24);
//                qDebug() << "PortManager::parcingStatusWord0x33 -- DataQueueItem::makeAlarmReset0x24(" << resultRequest.data().toHex() << ", " << un->toString() << ");";

            }
        }

        if(un->getDkInvolved()) {
            // обработка дк
            if(DKCiclStatus::DKDone != un->getDkStatus()) {
//                qDebug() << "PortManager::parcingStatusWord0x33 -- procDK";
                procDK(un, previousCopyUN);
                if(DKCiclStatus::DKDone == un->getDkStatus()) {
                    for(const auto &ar : as_const(getLsWaiter())) {
                         if(RequesterType::DKWaiter == ar->getRequesterType()) {
                             auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                             if(dwWaiter->removeLsTrackedUN(un)) {
                                 if(0 == dwWaiter->getLsTrackedUN().size()) {
                                     removeLsWaiter(dwWaiter);
                                     SignalSlotCommutator::getInstance()->emitStopDKWait();
                                 }
                                 qDebug() << "PortManager::removeLsTrackedUN(" << un->toString() << ")";
                                 break;
                             }
                         }
                    }
                    JourEntity msg;
                    msg.setObject(un->getName());
                    msg.setObjecttype(un->getType());
                    msg.setD1(un->getNum1());
                    msg.setD2(un->getNum2());
                    msg.setD3(un->getNum3());
                    msg.setDirection(un->getDirection());
                    msg.setComment(tr("Ком. ДК выполнена"));
                    msg.setType(3);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);

                    un->setPublishedState(-1);
                }
            }
            if(/*!un->getDkInvolved() &&*/ (
               (TypeUnitNode::RLM_C == un->getType() && 1 == un->swpRLMC().isOn() && (1 == un->swpRLMC().isInAlarm() || 1 == un->swpRLMC().isOutAlarm() || 1 == un->swpRLMC().isWasAlarm())) ||
               (TypeUnitNode::RLM_KRL == un->getType() && 1 == un->swpRLM().isOn() && (1 == un->swpRLM().isInAlarm() || 1 == un->swpRLM().isOutAlarm() || 1 == un->swpRLM().isWasAlarm())) ||
               (TypeUnitNode::TG == un->getType() && 1 == un->swpTGType0x31().isOn() && (1 == un->swpTGType0x31().isInAlarm() || 1 == un->swpTGType0x31().isOutAlarm() || 1 == un->swpTGType0x31().isWasAlarm() || 1 == un->swpTGType0x31().isInOpened() || 1 == un->swpTGType0x31().isWasOpened())))) {
                //нужен сброс
                auto alarmReset0x24 = resultRequest;
                DataQueueItem::makeAlarmReset0x24(alarmReset0x24, un);
                if(!reciver.isNull()) {
                    reciver->queueMsg.enqueue(alarmReset0x24);
//                    qDebug() << "PortManager::parcingStatusWord0x33 -- DataQueueItem::makeAlarmReset0x24(" << resultRequest.data().toHex() << ", " << un->toString() << ");";
                }
            }
        }

        bool wasDetectedNew20 = false;

        if(!un.isNull() && (previousSWP.getStateWord().getByteWord() != currentSWP.getStateWord().getByteWord()) && !un->getDkInvolved()) {

            // Первое сообщение о включении
            JourEntity msg;
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setDirection(un->getDirection());

            if(TypeUnitNode::TG != un->getType()) {
//                    previousCopyUN.clear();
//                    qDebug() << "PortManager::parcingStatusWord0x33 -- continue(3)";
                continue;
            } else if(TypeUnitNode::TG == un->getType() && 1 <= un->getNum2() && un->getNum2() <= 4) {
                //Сообщения в журнал

                if(10 == un->getPublishedState()) {
                    un->setPublishedState(-1);
                }

                if((1 == currentSWP.C(ci).isFault()) &&
                   (currentSWP.C(ci).isFault() != previousSWP.C(ci).isFault())) {
                    //сохранение неисправность или Норма
                    msg.setComment(QObject::tr("Неисправность"));
                    msg.setType(12);
                    un->setPublishedState(12);
                } else if((1 == currentSWP.C(ci).isOpened()) &&
                    (currentSWP.C(ci).isOpened() != previousSWP.C(ci).isOpened())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-ВСКРЫТИЕ"));
                    msg.setType(21);
                    un->setPublishedState(21);
                } else if((1 == currentSWP.C(ci).isAlarm()) &&
                          (currentSWP.C(ci).isAlarm() != previousSWP.C(ci).isAlarm())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-СРАБОТКА"));
                    msg.setType(20);
                    un->setPublishedState(20);
                    wasDetectedNew20 = true;
                } else if((1 == currentSWP.C(ci).isNorm()) &&
                          (previousSWP.C(ci).isNorm() != currentSWP.C(ci).isNorm()) &&
                          1 != un->getPublishedState()) {
                    msg.setComment(QObject::tr("Норма"));
                    msg.setType(1);
                    un->setPublishedState(1);
                }
                if(un->getControl() && 1 != un->getMetaEntity() && 0 != msg.getType()) {
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    if(20 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm();
                    } else if(10 == msg.getType() || 12 == msg.getType() || 21 == msg.getType()) {
                        SoundAdjuster::instance().playAlarm2();
                    }
                }
                msg.setType(0);
            }
        }

        un->updDoubl();
        SignalSlotCommutator::getInstance()->emitUpdUN();

        if(!un->getDkInvolved() && wasDetectedNew20) {
            //сохранение Тревога или Норма
            for(const auto& iuun : as_const(ServerSettingUtils::getLinkedUI(un))) {
                SignalSlotCommutator::getInstance()->emitAutoOnOffIU(qSharedPointerCast<UnitNode>(iuun));
            }
            //нужен сброс
        }

//        previousCopyUN.clear();
//        qDebug() << "PortManager::parcingStatusWord0x33 -- break(1)";
//        break;
    }
//    qDebug() << "PortManager::parcingStatusWord0x33 <--";
    return resultRequest;
}

DataQueueItem PortManager::parcingStatusWord0x34(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "PortManager::parcingStatusWord0x34 -->";
    StateWord newStateWord(item.data().mid(5, item.data().at(3)));
    resultRequest = item;
    resultRequest.setData();

    const QList<QSharedPointer<UnitNode> > tmpSet = ServerSettingUtils::getSetMetaRealUnitNodes().values();
    for(QSharedPointer<UnitNode>  un : tmpSet) {
        if(TypeUnitNode::TG != un->getType())
            continue;
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress())) ||
           item.port() != un->getUdpPort() ||
           static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1())) {
//            qDebug() << "PortManager::parcingStatusWord0x34 -- continue(1)";
            continue;
        }
        auto reciver = UnitNode::findReciver(un);
        if(!reciver.isNull()) {
            reciver->resetCountStatusConnectRequesterWaitAnswer();
        }

        auto previousSWP = un->swpTGType0x34();
//        QSharedPointer<UnitNode> previousCopyUN = UnitNodeFactory::makeShare(*un);

        un->setStateWordType0x34(newStateWord);
        un->updDoubl();
        SignalSlotCommutator::getInstance()->emitUpdUN();

    }
//    qDebug() << "PortManager::parcingStatusWord0x34 <--";
    return resultRequest;
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
            quint8 CMD = itm.data().at(4);
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

                QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
//                bool dkWait = false;
                for(auto ar : as_const(getLsWaiter())) {
                    if((RequesterType::DKWaiter == ar->getRequesterType()) && //(ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN)))
                        ar->getIpPort() == tmpPair) {
//                        dkWait = true;
                        break;
                    }
                }
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

                QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
//                bool dkWait = false;
                for(auto ar : as_const(getLsWaiter())) {
                    if((RequesterType::DKWaiter == ar->getRequesterType()) && //(ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN)))
                        ar->getIpPort() == tmpPair) {
//                        dkWait = true;
                        break;
                    }
                }
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

                QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
//                bool dkWait = false;
                for(auto ar : as_const(getLsWaiter())) {
                    if((RequesterType::DKWaiter == ar->getRequesterType()) && //(ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN)))
                        ar->getIpPort() == tmpPair) {
//                        dkWait = true;
                        break;
                    }
                }
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

                QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
//                bool dkWait = false;
                for(auto ar : as_const(getLsWaiter())) {
                    if((RequesterType::DKWaiter == ar->getRequesterType()) && //(ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN)))
                        ar->getIpPort() == tmpPair) {
//                        dkWait = true;
                        break;
                    }
                }
                break;
            }
            case static_cast<quint8>(0x30): {

//                qDebug() << "case static_cast<quint8>(0x30)";
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
                                SignalSlotCommutator::getInstance()->emitStartDKWait(ar->getTimeIntervalWaiteFirst());
                            } else if(RequesterType::LockRequester == ar->getRequesterType()) {
                                SignalSlotCommutator::getInstance()->emitStartLockWait(ar->getTimeIntervalWaiteFirst());
                            }

                            ar->startWaiteSecondRequest();

                        } else if(BeatStatus::RequestStep2 == ar->getBeatStatus()) { // удаляем завершившихся и переводим во второе ожидание другие

                            if(RequesterType::DKWaiter == ar->getRequesterType()) {
                                for(QSharedPointer<UnitNode>  un : ar.dynamicCast<ProcessDKWaiter>()->getLsTrackedUN()) {
                                    JourEntity msg;
                                    msg.setObject(un->getName());
                                    msg.setObjecttype(un->getType());
                                    msg.setD1(un->getNum1());
                                    msg.setD2(un->getNum2());
                                    msg.setD3(un->getNum3());
                                    msg.setDirection(un->getDirection());

                                    if(DKCiclStatus::DKDone == un->getDkStatus()) {
                                        msg.setComment(tr("Ком. ДК выполнена"));
                                        msg.setType(3);
                                        if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                                            DataBaseManager::insertJourMsg_wS(msg);
                                            GraphTerminal::sendAbonentEventsAndStates(un, msg);

                                            un->setPublishedState(-1);
                                        }
                                    } else {
                                        msg.setComment(tr("Ком. ДК не выполнена"));
                                        msg.setType(11);
                                        if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                                            DataBaseManager::insertJourMsg_wS(msg);
                                            GraphTerminal::sendAbonentEventsAndStates(un, msg);

                                            un->setPublishedState(-1);

                                            SoundAdjuster::instance().playAlarm2();
                                        }
                                    }
                                    un->setDkInvolved(false);
                                    un->setDkStatus(DKCiclStatus::DKIgnore);
                                    un->updDoubl();
                                }
//                                SignalSlotCommutator::getInstance()->emitStopDKWait();
//                                removeLsWaiter(ar);
                            } else if(RequesterType::LockRequester == ar->getRequesterType()){

                                if(RequesterType::LockRequester == ar->getRequesterType()) {
                                    SignalSlotCommutator::getInstance()->emitStartLockWait(ar->getTimeIntervalWaiteSecond());
                                }

                                ar->startWaiteEndSecondWaite();
                            }

                            if(RequesterType::LockRequester != ar->getRequesterType()) {
                                if(RequesterType::DKWaiter == ar->getRequesterType()) {
                                    SignalSlotCommutator::getInstance()->emitStopDKWait();
                                }
                                removeLsWaiter(ar);
                            }

                        } else if(BeatStatus::End == ar->getBeatStatus()) { // кончаем конценных, но такого не бывает

                            if(RequesterType::LockRequester == ar->getRequesterType()) {
                                SignalSlotCommutator::getInstance()->emitStopLockWait();
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

void PortManager::unLostedConnect(QSharedPointer<UnitNode> un) const
{
//    //qDebug() << "PortManager::unLostedConnect(" << un << ")";
    if(1 == un->isConnected()) {
        un->setStateWord(QByteArray());
        un->setStateWordType0x31(QByteArray());
        un->setStateWordType0x32(QByteArray());
        un->setStateWordType0x33(QByteArray());
        un->setStateWordType0x34(QByteArray());

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
                SoundAdjuster::instance().playAlarm();
            } else if(10 == msg.getType() || 12 == msg.getType() || 21 == msg.getType()) {
                SoundAdjuster::instance().playAlarm2();
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

    SignalSlotCommutator::getInstance()->emitUpdUN();

}
