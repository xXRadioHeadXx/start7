#include <QVector>
#include <QSettings>
#include <QDebug>
#include <SignalSlotCommutator.h>

#include <PortFactory.h>
#include <PortManager.h>
#include <Port.h>
#include <DataQueueItem.h>
#include <Utils.h>
#include <SettingUtils.h>

PortManager::PortManager(QObject *parent, DataBaseManager *dbm) : QObject(parent), m_dbm(dbm), MAX_COUNT_PORTS(1)
{
//    m_portFactorys.reserve(1);
//    m_portFactorys.insert(Protocol::UDP, new PortFactory());

    m_udpPortsVector.reserve(MAX_COUNT_PORTS);
}

QList<AbstractPort *> PortManager::m_udpPortsVector = QList<AbstractPort *>();

Port* PortManager::createPort(QObject *parent, const int index) {
    return new Port(parent, index, m_dbm);
}


PortManager::~PortManager()
{
//    for (PortFactory *factory : m_portFactorys) {
//        delete factory;
//    }

    for (AbstractPort *port : m_udpPortsVector) {
        delete port;
    }
}

void PortManager::retranslate() {}

void PortManager::loadConfig(QSettings *config, const int index) {
    m_udpPortsVector.at(index)->loadConfig(config);
}

void PortManager::saveConfig(QSettings *config, const int index) {
    m_udpPortsVector.at(index)->saveConfig(config);
}

void PortManager::loadSettings(QSettings *config, const int index) {}

void PortManager::loadSettings() {
    m_udpPortsVector.clear();
    m_udpPortsVector = SettingUtils::loadPorts();

    for(AbstractPort * port : m_udpPortsVector) {
        switch(port->getProtocol()) {
            case AbstractPort::UDP:
                Utils::typeDefPort(port)->open();
                Utils::typeDefPort(port)->setDbm(this->m_dbm);
                setupPort(port);
                break;
            default:
                break;
        }
    }
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
            pushOverallReadQueue(Utils::typeDefPort(m_udpPortsVector.at(index))->popLocalReadQueue());
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
    for(DataQueueItem itm : data) {
        write(itm);
    }
}

void PortManager::write(const DataQueueItem &data) {
    switch (m_udpPortsVector.at(data.portIndex())->getProtocol()) {
        case AbstractPort::UDP:
            Utils::typeDefPort(m_udpPortsVector.at(data.portIndex()))->pushLocalWriteQueue(data);
            Utils::typeDefPort(m_udpPortsVector.at(data.portIndex()))->write();
            break;
        default:
            break;
    }
}

bool PortManager::portStatus(QString *string, const int index) {
    return m_udpPortsVector.at(index)->portStatus(string);
}

bool PortManager::isOpen(const int index) {
    return m_udpPortsVector.at(index)->isOpen();
}

QList<AbstractPort *> PortManager::getUdpPortsVector()
{
    return m_udpPortsVector;
}

QList<AbstractRequester *> PortManager::getLsWaiter() const
{
    return lsWaiter;
}

void PortManager::setLsWaiter(const QList<AbstractRequester *> &value)
{
    lsWaiter = value;
}

void PortManager::appLsWaiter(AbstractRequester * value) {
    if(nullptr == value)
        return;

    if(value->isValid())
        lsWaiter.append(value);
    else
        delete value;
}

void PortManager::preppLsWaiter(AbstractRequester * value) {
    if(nullptr == value)
        return;

    if(value->isValid())
        lsWaiter.prepend(value);
    else
        delete value;
}


void PortManager::removeLsWaiter(AbstractRequester *value) {

    lsWaiter.removeAll(value);
    delete value;
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

    Utils::typeDefPort(m_udpPortsVector.at(index))->prepareUdpScoket(ip, port);
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
    QList<DataQueueItem> result(getOverallReadQueue());
    for(DataQueueItem itm : result) {
        overallReadQueue.removeOne(itm);
    }
    return result;
}
void PortManager::pushOverallReadQueue(const QList<DataQueueItem> &value) {
    overallReadQueue.append(value);
//    qDebug() << "pushOverallReadQueue size(" << overallReadQueue.size() << ")";
}

void PortManager::pushOverallReadQueue(const DataQueueItem &value){
    overallReadQueue.append(value);
//    qDebug() << "pushOverallReadQueue size(" << overallReadQueue.size() << ")";
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
    QList<DataQueueItem> result(getOverallWriteQueue());
    for(DataQueueItem itm : result) {
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

    lsStatusRequester.clear();

    for(int index = 0, n = m_udpPortsVector.size(); index < n; index++) {
        Port * tmnPort = Utils::typeDefPort(m_udpPortsVector.at(index));
        for(QPair<QString, QString> tmpIpPort : tmnPort->getStIpPort()) {
            StatusRequester * tmpSR = new StatusRequester(this);// = new StatusRequester(this);

            tmpSR->ipPort = tmpIpPort;
            tmpSR->portIndex = index;
            tmpSR->ptrPort = tmnPort;

            lsStatusRequester.append(tmpSR);
        }
    }

    for(int index = 0, n = lsStatusRequester.size(); index < n; index++) {
        lsStatusRequester[index]->startStatusRequest();
    }
}

void PortManager::requestAlarmReset(UnitNode * selUN) {
    if(nullptr == selUN) {
        QSet<UnitNode *> lsTmp = SettingUtils::getSetMetaRealUnitNodes();
        for(UnitNode * un : lsTmp) {
            if(TypeUnitNode::BL_IP == un->getType())
                selUN = un;
            if(nullptr != selUN) {
                QPair<QString, QString> tmpPair(selUN->getUdpAdress(), QVariant(selUN->getUdpPort()).toString());
                for(AbstractPort * pt : m_udpPortsVector) {
                    if(Utils::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {

                        ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(selUN);
                        tmpCAW->init();
                        DataQueueItem itm = tmpCAW->getFirstMsg();
                        itm.setData(Utils::makeAlarmReset0x24());

                        appLsWaiter(tmpCAW);
//                        tmpCAW->startFirstRequest();
                        break;
                    }
                }
            }
            selUN = nullptr;
        }
    } else {
        UnitNode * un = selUN;
        while(TypeUnitNode::BL_IP != un->getType()) {
            un = un->getParentUN();
        }
        if(TypeUnitNode::BL_IP == un->getType()) {
            selUN = un;
            ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(selUN);
            tmpCAW->init();
            DataQueueItem itm = tmpCAW->getFirstMsg();
            itm.setData(Utils::makeAlarmReset0x24());
            tmpCAW->setFirstMsg(itm);
            appLsWaiter(tmpCAW);
//            tmpCAW->startFirstRequest();
        }
    }
//    write();
}

void PortManager::requestDK(UnitNode * selUN) {
    //
    QList<UnitNode *> lsTrgtUN;
    if(nullptr == selUN) {
        QSet<UnitNode *> lsTmp = SettingUtils::getSetMetaRealUnitNodes();
        for(UnitNode * un : lsTmp)
            if(TypeUnitNode::BL_IP == un->getType() /* или датчик */)
                lsTrgtUN.append(un);
    } else if(nullptr != selUN) {
        UnitNode * un = selUN;
        while(nullptr != un) {
            if(TypeUnitNode::BL_IP == un->getType() /* или датчик */) {
                lsTrgtUN.append(un);
                break;
            }
            un = un->getParentUN();
        }
    }

    if(lsTrgtUN.isEmpty())
        return;

    if(nullptr == selUN) {
        JourEntity msg;
        msg.setObject(trUtf8("РИФ Общий"));
        msg.setComment(trUtf8("Послана ком. ДК"));
        DataBaseManager::insertJourMsg_wS(msg);
    }

    for(UnitNode * un : lsTrgtUN) {
        QPair<QString, QString> tmpPair(un->getUdpAdress(), QVariant(un->getUdpPort()).toString());
        for(AbstractPort * pt : m_udpPortsVector) {
            if(Utils::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {

                ProcessDKWaiter * tmpPDKW = new ProcessDKWaiter(un);
                tmpPDKW->init();
                appLsWaiter(tmpPDKW);
//                tmpPDKW->startFirstRequest();
                break;
            }
        }
        if(nullptr == selUN && !un->getName().isEmpty() && un->getControl()) {
            JourEntity msg;
            msg.setComment(trUtf8("Послана ком. ДК"));
            msg.setObject(un->getName());
            DataBaseManager::insertJourMsg_wS(msg);
        }
    }
    if(nullptr != selUN && selUN->getControl()) {
        JourEntity msg;
        msg.setComment(trUtf8("Послана ком. ДК"));
        msg.setObject(selUN->getName());
        DataBaseManager::insertJourMsg_wS(msg);
    }
}

void PortManager::requestAutoOnOffIUCommand(UnitNode *selUN) {
    if(TypeUnitNode::IU_BL_IP == selUN->getType()) {
        QPair<QString, QString> tmpPair(selUN->getUdpAdress(), QVariant(selUN->getUdpPort()).toString());
        for(AbstractPort * pt : m_udpPortsVector) {
            if(Utils::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {
                for(AbstractRequester * ar : getLsWaiter()) {
                    if((RequesterType::AutoOnOffWaiter == ar->getRequesterType()) && (ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN)))
                        return;
                }

                OnOffIUWaiter * tmpOOIUW = new OnOffIUWaiter(selUN);
                tmpOOIUW->init();
                appLsWaiter(tmpOOIUW);
//                tmpOOIUW->startFirstRequest();
            }
        }
    }
}


void PortManager::requestOnOffCommand(UnitNode *selUN, bool value)
{
    UnitNode * reciver = selUN;
    UnitNode * target = selUN;

    if(TypeUnitNode::SD_BL_IP != target->getType() &&
            TypeUnitNode::IU_BL_IP != target->getType())
        return;

    if(!SettingUtils::getSetMetaRealUnitNodes().contains(reciver)) {
        for(UnitNode * un : SettingUtils::getSetMetaRealUnitNodes())
            if(un->getDoubles().contains(reciver)) {
                target = reciver = un;
                break;
            }
    }

    quint8 D1 = 0x00;
    if(TypeUnitNode::SD_BL_IP == target->getType() ||
            TypeUnitNode::IU_BL_IP == target->getType()) {
        while(nullptr != reciver) {
            if(TypeUnitNode::BL_IP == reciver->getType()) {
                break;
            }
            reciver = reciver->getParentUN();
        }
    }
    int type = target->getType();

    for(UnitNode * un : reciver->getListChilde()) {
        if(type != un->getType())
            continue;
        quint8 mask = 0;
        switch (un->getNum2()) {
        case 1:
            mask = 0x01;
            break;
        case 2:
            mask = 0x02;
            break;
        case 3:
            mask = 0x04;
            break;
        case 4:
            mask = 0x08;
            break;
        case 5:
            mask = 0x10;
            break;
        case 6:
            mask = 0x20;
            break;
        case 7:
            mask = 0x40;
            break;
        case 8:
            mask = 0x80;
            break;
        default:
            mask = 0x00;
            break;
        }

        if(TypeUnitNode::SD_BL_IP == un->getType() &&
                Status::Off == un->getStatus2() &&
                Status::Uncnown == un->getStatus1())
            D1 = D1 & ~mask;
        else if(TypeUnitNode::IU_BL_IP == un->getType() &&
                Status::Off == un->getStatus1())
            D1 = D1 & ~mask;
        else
            D1 = D1 | mask;

        if(un == target && value)
            D1 = D1 | mask;
        else if(un == target && !value)
            D1 = D1 & ~mask;
    }

    if(TypeUnitNode::BL_IP == reciver->getType()) {
        ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(reciver);
        tmpCAW->init();
        DataQueueItem itm = tmpCAW->getFirstMsg();
        QByteArray data;
        if(TypeUnitNode::SD_BL_IP == target->getType())
            data = Utils::makeOnOff0x20();
        else if(TypeUnitNode::IU_BL_IP == target->getType())
            data = Utils::makeOnOff0x23();
        data[4] = D1;
        data.chop(1);
        data.append(Utils::getByteSumm(data)); //<CHKS>
        itm.setData(data);
        tmpCAW->setFirstMsg(itm);
        appLsWaiter(tmpCAW);
//        tmpCAW->startFirstRequest();

        if(target->getControl()) {
            JourEntity msg;
            msg.setObject(target->getName());
            msg.setComment(trUtf8("Послана ком. ") + (value ? trUtf8("Вкл") : trUtf8("Выкл")));
            DataBaseManager::insertJourMsg_wS(msg);
        }
    }
}

ProcessDKWaiter * PortManager::addProcessDKWaiter(QHostAddress address, int port, int index) {
//    ProcessDKWaiter * tmpPDKW = new ProcessDKWaiter(this);

//    tmpPDKW->ipPort.first = Utils::hostAddressToString(address);
//    tmpPDKW->ipPort.second = QVariant(port).toString();
//    tmpPDKW->portIndex = index;
//    tmpPDKW->ptrPort = m_udpPortsVector.at(index);

//    DataQueueItem itm1(Utils::makeDK0x21(), address, port, index);
//    tmpPDKW->sendDKMsg = itm1;

//    DataQueueItem itm2(Utils::makeAlarmReset0x24(), address, port, index);
//    tmpPDKW->sendResetAlarmMsg = itm2;

//    lsProcessDKWaiter.append(tmpPDKW);

//    return tmpPDKW;
    return 0;
}

void PortManager::manageOverallReadQueue()
{
    QList<DataQueueItem> tmpQueue = popOverallReadQueue();
    for (DataQueueItem itm : tmpQueue) {
        QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
        AbstractPort * pt = m_udpPortsVector.at(itm.portIndex());
        if(Utils::isValideDirectionI(itm)) {
            quint8 CMD = itm.data().at(4);
            switch (CMD) {
            case (quint8)0x41: {
                for(StatusRequester * sr : this->lsStatusRequester) {
                    if(sr->ipPort == tmpPair) {
                        sr->beatCount = 0;
                        break;
                    }
                }
                DataQueueItem request;
                Utils::parcingStatusWord0x41(itm, request);

                QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
                bool dkWait = false;
                for(AbstractRequester * ar : getLsWaiter()) {
                    if((RequesterType::DKWaiter == ar->getRequesterType()) && //(ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN)))
                        ar->getIpPort() == tmpPair) {
                        dkWait = true;
                        break;
                    }
                }

                if(request.isValid() && !dkWait) {
                    UnitNode * reciver = nullptr;
                    for(UnitNode * un : SettingUtils::getSetMetaRealUnitNodes()) {
                        reciver = un;
                        if(TypeUnitNode::BL_IP == reciver->getType() &&
                                reciver->getUdpAdress() == Utils::hostAddressToString(request.address()) &&
                                reciver->getUdpPort() == request.port())
                            break;

                    }

                    ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(reciver);
                    tmpCAW->init();
                    tmpCAW->setUnReciver(reciver);
                    tmpCAW->setFirstMsg(request);
                    preppLsWaiter(tmpCAW);
//                    tmpCAW->startFirstRequest();
                }
                break;
            }
            case (quint8)0x30: {

                for(AbstractRequester * ar : getLsWaiter()) {
                    if(ar->getIpPort() == tmpPair) {
                        if(BeatStatus::RequestStep1 == ar->getBeatStatus()) {

                            if(RequesterType::DKWaiter == ar->getRequesterType()) {
                                for(UnitNode * un : ((ProcessDKWaiter *)ar)->getLsTrackedUN()) {
                                    un->setDkInvolved(true);
                                    un->setDkStatus(DKCiclStatus::DKReady);
                                    un->updDoubl();
                                }
                            }

                            ar->startWaiteSecondRequest();

                            if(RequesterType::DKWaiter == ar->getRequesterType()) {
                                SignalSlotCommutator::getInstance()->emitStartDKWait(ar->getTimeIntervalWaite());
                            }
                        } else if(BeatStatus::RequestStep2 == ar->getBeatStatus() ||
                                  BeatStatus::Unsuccessful == ar->getBeatStatus()) {

                            if(RequesterType::DKWaiter == ar->getRequesterType()) {
                                for(UnitNode * un : ((ProcessDKWaiter *)ar)->getLsTrackedUN()) {
                                    JourEntity msg;
                                    msg.setObject(un->getName());
                                    if(DKCiclStatus::DKDone == un->getDkStatus()) {
                                        msg.setComment(trUtf8("Ком. ДК выполнена"));
                                    } else {
                                        msg.setComment(trUtf8("Ком. ДК не выполнена"));
                                    }
                                    un->setDkInvolved(false);
                                    un->setDkStatus(DKCiclStatus::DKIgnore);
                                    un->updDoubl();
                                    if(un->getControl())
                                        DataBaseManager::insertJourMsg_wS(msg);
                                }
                            }

                            removeLsWaiter(ar);

                            if(RequesterType::DKWaiter == ar->getRequesterType()) {
                                SignalSlotCommutator::getInstance()->emitStopDKWait();
                            }
                        }
                    }
                }
                break;
            }
            default:
                break;
            }

            bool keypass = true;
            for(AbstractRequester * ar : getLsWaiter())
                if(BeatStatus::Unsuccessful == ar->getBeatStatus()) {
                    removeLsWaiter(ar);
                } else if(true == keypass && BeatStatus::Start == ar->getBeatStatus()) {
                    keypass = false;
                    ar->startFirstRequest();
                }
        }
    }
}
