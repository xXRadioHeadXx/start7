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
    m_udpPortsVector = loadPorts();

    for(AbstractPort * port : m_udpPortsVector) {
        switch(port->getProtocol()) {
            case AbstractPort::UDP:
                Port::typeDefPort(port)->open();
                Port::typeDefPort(port)->setDbm(this->m_dbm);
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
    for(DataQueueItem itm : data) {
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

    Port::typeDefPort(m_udpPortsVector.at(index))->prepareUdpScoket(ip, port);
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
        Port * tmnPort = Port::typeDefPort(m_udpPortsVector.at(index));
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
                    if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {

                        ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(selUN);
                        tmpCAW->init();
                        DataQueueItem itm = tmpCAW->getFirstMsg();
                        itm.setData(DataQueueItem::makeAlarmReset0x24());

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
            itm.setData(DataQueueItem::makeAlarmReset0x24());
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
        msg.setType(133);
        msg.setComment(trUtf8("Послана ком. ДК"));
        DataBaseManager::insertJourMsg_wS(msg);
    }

    for(UnitNode * un : lsTrgtUN) {
        QPair<QString, QString> tmpPair(un->getUdpAdress(), QVariant(un->getUdpPort()).toString());
        for(AbstractPort * pt : m_udpPortsVector) {
            if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {

                ProcessDKWaiter * tmpPDKW = new ProcessDKWaiter(un);
                tmpPDKW->init();
                appLsWaiter(tmpPDKW);
//                tmpPDKW->startFirstRequest();
                break;
            }
        }
        if(nullptr == selUN && !un->getName().isEmpty() && un->getControl()) {
            JourEntity msg;
            msg.setType(133);
            msg.setComment(trUtf8("Послана ком. ДК"));
            msg.setObject(un->getName());
            DataBaseManager::insertJourMsg_wS(msg);
        }
    }
    if(nullptr != selUN && selUN->getControl()) {
        JourEntity msg;
        msg.setType(133);
        msg.setComment(trUtf8("Послана ком. ДК"));
        msg.setObject(selUN->getName());
        DataBaseManager::insertJourMsg_wS(msg);
    }
}

void PortManager::requestAutoOnOffIUCommand(UnitNode *selUN) {
    if(TypeUnitNode::IU_BL_IP == selUN->getType()) {
        QPair<QString, QString> tmpPair(selUN->getUdpAdress(), QVariant(selUN->getUdpPort()).toString());
        for(AbstractPort * pt : m_udpPortsVector) {
            if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {
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
            data = DataQueueItem::makeOnOff0x20();
        else if(TypeUnitNode::IU_BL_IP == target->getType())
            data = DataQueueItem::makeOnOff0x23();
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
            msg.setType((value ? 130 : 131));
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

QList<AbstractPort *> PortManager::loadPorts(QString fileName) {
    QList<AbstractPort *> result;

    QSettings settings(fileName, QSettings::IniFormat);

    settings.beginGroup("TREE");
    int cntTrItm = settings.value( "Count", -1 ).toInt();
    settings.endGroup();

    qDebug() << "cntTrItm" << cntTrItm;
    if(0 >= cntTrItm)
        return result;

    settings.setIniCodec( "Windows-1251" );

    QSet<QPair<QString, QString> > stIpPort;
    QSet<QString> stPort;

    for(int index = 0; stIpPort.size() < cntTrItm && index < (100 + cntTrItm); index++)
    {
        QString strGroup("Obj_%1");
        strGroup = strGroup.arg(index);
        if(settings.childGroups().contains(strGroup))
        {
            settings.beginGroup(strGroup);
            int udpUse = settings.value( "UdpUse" , -1 ).toInt();
            QString udpAdress = settings.value( "UdpAdress" , -1 ).toString();
            QString updPort = settings.value( "UpdPort" , -1 ).toString();
            settings.endGroup();

            if (1 == udpUse && !udpAdress.isEmpty() && !updPort.isEmpty()){
                QPair<QString, QString> tmp(udpAdress, updPort);
                stIpPort.insert(tmp);
                stPort.insert(updPort);
            }
        }
    }

    for(QString prt : stPort) {
        result.append(PortFactory::create(AbstractPort::UDP, result.size()));
        Port::typeDefPort(result.last())->setStrPort(prt);
        for(QPair<QString, QString> tmp : stIpPort) {
            if(prt == tmp.second)
                Port::typeDefPort(result.last())->addToSetIpPort(tmp);
        }
    }

    return result;
}


DataQueueItem PortManager::parcingStatusWord0x41(DataQueueItem &item, DataQueueItem & resultRequest)
{
//    qDebug() << "Utils::parcingStatusWord0x41 -->";
    resultRequest = item;
    resultRequest.setData();

    QSet<UnitNode *> tmpSet = SettingUtils::getSetMetaRealUnitNodes();
    for(UnitNode * un : tmpSet) {
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress())) || item.port() != un->getUdpPort())
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

        quint8 newStatus1 = Status::Uncnown, newStatus2 = Status::Uncnown; // un->getStatus();
        if(TypeUnitNode::BL_IP == un->getType()) {
            if((quint8)item.data().at(6) & 0x40)
                newStatus2 = (newStatus2 | Status::Was);
            else
                newStatus2 = (newStatus2 | Status::Not);

            if((quint8)item.data().at(6) & 0x80)
                newStatus1 = (newStatus1 | Status::Exists);
            else
                newStatus1 = (newStatus1 | Status::Not);

            if(newStatus1 != un->getStatus1() || newStatus2 != un->getStatus2()) {
                un->setStatus1(newStatus1);
                un->setStatus2(newStatus2);
                un->updDoubl();
                SignalSlotCommutator::getInstance()->emitUpdUN();
            }

        } else if(TypeUnitNode::SD_BL_IP == un->getType()) {
            if((quint8)item.data().at(5) & mask)
                newStatus1 = (newStatus1 | Status::Alarm);
            else
                newStatus1 = (newStatus1 | Status::Norm);

            if((quint8)item.data().at(7) & mask)
                newStatus2 = (newStatus2 | Status::Was);
            else
                newStatus2 = (newStatus2 | Status::Not);

            if(((quint8)item.data().at(8) & mask) == 0) {
                newStatus1 = Status::Uncnown;
                newStatus2 = Status::Off;
            }
        } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
            if((quint8)item.data().at(6) & mask)
                newStatus1 = (newStatus1 | Status::On);
            else
                newStatus1 = Status::Off;
        }

        if(0 != un->getDK() && DKCiclStatus::DKIgnore != un->getDkStatus() && DKCiclStatus::DKWrong != un->getDkStatus() && DKCiclStatus::DKDone != un->getDkStatus() && un->getDkInvolved()) {
//            qDebug() << "DkStatus --> " << un->getName();
            int unCalcDkStatus = Utils::calcDkStatus(un->getType(), un->getStatus1(), un->getStatus2());
//            qDebug() << "DkStatus -- unCalcDkStatus " << unCalcDkStatus;
//            qDebug() << "DkStatus -- unDkStatus " << un->getDkStatus();
            if(DKCiclStatus::DKReady == un->getDkStatus() &&
                    DKCiclStatus::DKNorm == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKNorm);
            else if((DKCiclStatus::DKNorm == un->getDkStatus() || DKCiclStatus::DKReady == un->getDkStatus())&&
                    DKCiclStatus::DKWasAlarn == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKWasAlarn);
            else if(DKCiclStatus::DKWasAlarn == un->getDkStatus() &&
                    DKCiclStatus::DKNorm == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKDone);
            else if(DKCiclStatus::DKWasAlarn == un->getDkStatus() &&
                    DKCiclStatus::DKWas == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKDone);
            else if((DKCiclStatus::DKNorm == un->getDkStatus() &&
                     DKCiclStatus::DKNorm == unCalcDkStatus) ||
                    (DKCiclStatus::DKWasAlarn == un->getDkStatus() &&
                     DKCiclStatus::DKWasAlarn == unCalcDkStatus))
                un->setDkStatus(un->getDkStatus());
            else
                un->setDkStatus(DKCiclStatus::DKWrong);
            un->updDoubl();
//            qDebug() << "DkStatus -- unNewDkStatus " << un->getDkStatus();
//            qDebug() << "DkStatus <--";
        }

        if(newStatus1 != un->getStatus1() || newStatus2 != un->getStatus2()) {
            quint8 oldStatus1 = un->getStatus1(), oldStatus2 = un->getStatus2();
            un->setStatus1(newStatus1);
            un->setStatus2(newStatus2);
            un->updDoubl();
            SignalSlotCommutator::getInstance()->emitUpdUN();

            if(!un->getDkInvolved()) {

                JourEntity msg;
                msg.setObject(un->getName());

                if((TypeUnitNode::SD_BL_IP == un->getType() &&
                    Status::Uncnown == oldStatus1 &&
                    Status::Off == oldStatus2 &&
                    Status::Uncnown != newStatus1 &&
                    Status::Uncnown != newStatus2 &&
                    un->getControl()) ||
                   (TypeUnitNode::IU_BL_IP == un->getType() &&
                    Status::Off == oldStatus1 &&
                    Status::Uncnown != newStatus1 &&
                    un->getControl())) {
                    JourEntity msgOn;
                    msgOn.setObject(un->getName());
                    msgOn.setType(101);
                    msgOn.setComment(QObject::trUtf8("Вкл"));
                    DataBaseManager::insertJourMsg_wS(msgOn);
                  }

                if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (un->getStatus1() & Status::Alarm) && (un->getStatus2() & Status::Was)) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::trUtf8("Тревога-СРАБОТКА"));
                    msg.setType(20);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    //нужен сброс
                    resultRequest.setData(DataQueueItem::makeAlarmReset0x24());
                } else if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (un->getStatus1() & Status::Norm)) {
                    msg.setComment(QObject::trUtf8("Норма"));
                    msg.setType(1);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                } else if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (un->getStatus2() & Status::Off)) {
                    msg.setComment(QObject::trUtf8("Выкл"));
                    msg.setType(100);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                } else if(un->getControl() && (TypeUnitNode::IU_BL_IP == un->getType()) && (un->getStatus1() & Status::Off)) {
                    msg.setComment(QObject::trUtf8("Выкл"));
                    msg.setType(100);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                }
            }

            if(!un->getDkInvolved() && (TypeUnitNode::SD_BL_IP == un->getType()) && (un->getStatus1() & Status::Alarm) && (un->getStatus2() & Status::Was)) {
                //сохранение Тревога или Норма
                if(0 != un->treeChildCount()) {
                    for(UnitNode * iuun : un->treeChild()) {
                        if(TypeUnitNode::IU_BL_IP == iuun->getType()) {
                            qDebug() << "Utils::parcingStatusWord0x41 emitAutoOnOffIU";
                            SignalSlotCommutator::getInstance()->emitAutoOnOffIU(iuun);
                        }
                    }
                }

                //нужен сброс
            }
        }


    }
//    qDebug() << "Utils::parcingStatusWord0x41 <--";
    return resultRequest;
}

void PortManager::manageOverallReadQueue()
{
    QList<DataQueueItem> tmpQueue = popOverallReadQueue();
    for (DataQueueItem itm : tmpQueue) {
        QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
        AbstractPort * pt = m_udpPortsVector.at(itm.portIndex());
        if(DataQueueItem::isValideDirectionI(itm)) {
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
                parcingStatusWord0x41(itm, request);

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
                                        msg.setType(3);
                                    } else {
                                        msg.setComment(trUtf8("Ком. ДК не выполнена"));
                                        msg.setType(11);
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
