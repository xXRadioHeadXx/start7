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
#include <StatusConnectRequester.h>
#include <LockWaiter.h>
#include <global.hpp>
#include <QMessageBox>

PortManager::PortManager(QObject *parent, DataBaseManager *dbm) : QObject(parent), MAX_COUNT_PORTS(1), m_dbm(dbm)
{
//    m_portFactorys.reserve(1);
//    m_portFactorys.insert(Protocol::UDP, new PortFactory());

    m_udpPortsVector.reserve(MAX_COUNT_PORTS);

    connect(SignalSlotCommutator::getInstance(), SIGNAL(requestOnOffCommand(bool, UnitNode *, bool)), this, SLOT(requestOnOffCommand(bool, UnitNode *, bool)));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(lockOpenCloseCommand(bool, UnitNode *, bool)), this, SLOT(lockOpenCloseCommand(bool, UnitNode *, bool)));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(requestDK(UnitNode *)), this, SLOT(requestDK(UnitNode *)));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(autoOnOffIU(bool, UnitNode *)), this, SLOT(requestAutoOnOffIUCommand(bool, UnitNode *)));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(requestDK(bool, UnitNode *)), this, SLOT(requestDK(bool, UnitNode *)));
    connect(SignalSlotCommutator::getInstance(), SIGNAL(alarmsReset(UnitNode *)), this, SLOT(requestAlarmReset(UnitNode *)));
}

QList<AbstractPort *> PortManager::m_udpPortsVector = QList<AbstractPort *>();

GraphTerminal * PortManager::graphTerminal = nullptr;


QList<StatusConnectRequester *> PortManager::lsSCR = QList<StatusConnectRequester *>();

QList<AbstractRequester *> PortManager::lsWaiter = QList<AbstractRequester *>();


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

void PortManager::retranslate() {}

void PortManager::loadConfig(QSettings *config, const int index) {
    m_udpPortsVector.at(index)->loadConfig(config);
}

void PortManager::saveConfig(QSettings *config, const int index) {
    m_udpPortsVector.at(index)->saveConfig(config);
}

void PortManager::loadSettings(QSettings */*config*/, const int /*index*/) {}

void PortManager::loadSettings() {
    m_udpPortsVector.clear();
    m_udpPortsVector = loadPortsUdpObj();

    for(auto& port : as_const(m_udpPortsVector)) {
        switch(port->getProtocol()) {
            case AbstractPort::UDP:
                Port::typeDefPort(port)->open();
                Port::typeDefPort(port)->setDbm(this->m_dbm);
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

QList<AbstractRequester *> PortManager::getLsWaiter()
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

    value->timerTripleStop();
    lsWaiter.removeAll(value);
    value->setBeatStatus(BeatStatus::Unsuccessful);
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

    disconnect(SignalSlotCommutator::getInstance(), SIGNAL(lostConnect(UnitNode *)), this, SLOT(unLostedConnect(UnitNode *)));

    for(AbstractRequester * scr : as_const(lsSCR)) {
        scr->setBeatStatus(BeatStatus::Unsuccessful);
        delete scr;
    }
    lsSCR.clear();

    for(const auto& un : as_const(SettingUtils::getSetMetaRealUnitNodes())) {
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::RLM_C == un->getType()) {
            StatusConnectRequester * tmpSCR = new StatusConnectRequester(un);
            tmpSCR->init();
            for(const auto& p : as_const(getUdpPortsVector())) {
                if(Port::typeDefPort(p)->getStIpPort().contains(tmpSCR->getIpPort())) {
                    tmpSCR->setPtrPort(p);
                    break;
                }
            }
            lsSCR.append(tmpSCR);
        }
    }

    for(auto& scr : as_const(lsSCR)) {
        scr->startFirstRequest();
    }

    connect(SignalSlotCommutator::getInstance(), SIGNAL(lostConnect(UnitNode *)), this, SLOT(unLostedConnect(UnitNode *)));
}

void PortManager::requestAlarmReset(UnitNode * selUN) {
    if(nullptr == selUN) {
        QSet<UnitNode *> lsTmp = SettingUtils::getSetMetaRealUnitNodes();
        for(UnitNode * un : lsTmp) {
            if(TypeUnitNode::BL_IP == un->getType() || TypeUnitNode::RLM_C == un->getType())
                selUN = un;
            if(nullptr != selUN) {
                QPair<QString, QString> tmpPair(selUN->getUdpAdress(), QVariant(selUN->getUdpPort()).toString());
                for(const auto& pt : as_const(m_udpPortsVector)) {
                    if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {

                        ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(selUN);
                        tmpCAW->init();
                        DataQueueItem itm = tmpCAW->getFirstMsg();
                        itm.setData(DataQueueItem::makeAlarmReset0x24(selUN));

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
        if(TypeUnitNode::BL_IP == un->getType() || TypeUnitNode::IU_BL_IP == un->getType() || TypeUnitNode::SD_BL_IP == un->getType()) {
            while(TypeUnitNode::BL_IP != un->getType()) {
                un = un->getParentUN();
            }
        }
        if(TypeUnitNode::BL_IP == un->getType() || TypeUnitNode::RLM_C == un->getType()) {
            selUN = un;
            ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(selUN);
            tmpCAW->init();
            DataQueueItem itm = tmpCAW->getFirstMsg();
            itm.setData(DataQueueItem::makeAlarmReset0x24(selUN));
            tmpCAW->setFirstMsg(itm);
            appLsWaiter(tmpCAW);
//            tmpCAW->startFirstRequest();
        }
    }
    //    write();
}

void PortManager::requestDK(UnitNode *selUN)
{
    requestDK(false, selUN);
}

void PortManager::requestDK(bool out, UnitNode *selUN) {
    //
    QList<UnitNode *> lsTrgtUN;
    if(nullptr == selUN) {
        QSet<UnitNode *> lsTmp = SettingUtils::getSetMetaRealUnitNodes();
        for(UnitNode * un : lsTmp)
            if(TypeUnitNode::BL_IP == un->getType() || TypeUnitNode::RLM_C == un->getType()/* или датчик */)
                lsTrgtUN.append(un);
    } else if(nullptr != selUN) {
        UnitNode * un = selUN;
        while(nullptr != un) {
            if(TypeUnitNode::BL_IP == un->getType() || TypeUnitNode::RLM_C == un->getType()/* или датчик */) {
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

    for(UnitNode * un : lsTrgtUN) {
        QPair<QString, QString> tmpPair(un->getUdpAdress(), QVariant(un->getUdpPort()).toString());
        for(const auto& pt : as_const(m_udpPortsVector)) {
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
            if(out) {
                msg.setComment(tr("Удал. ком. ДК Послана ком. ДК"));
                msg.setType(1133);
            } else {
                msg.setComment(tr("Послана ком. ДК"));
                msg.setType(133);
            }
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setDirection(un->getUdpAdress());
            DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(msg);
        }
    }
    if(nullptr != selUN && selUN->getControl()) {
        JourEntity msg;
        msg.setObjecttype(selUN->getType());
        msg.setD1(selUN->getNum1());
        msg.setD2(selUN->getNum2());
        msg.setD3(selUN->getNum3());
        msg.setDirection(selUN->getUdpAdress());

        if(out) {
            msg.setComment(tr("Удал. ком. ДК Послана ком. ДК"));
            msg.setType(1133);
        } else {
            msg.setComment(tr("Послана ком. ДК"));
            msg.setType(133);
        }
        msg.setObject(selUN->getName());
        DataBaseManager::insertJourMsg_wS(msg);
        GraphTerminal::sendAbonentEventsAndStates(selUN, msg);
    }
}

void PortManager::requestAutoOnOffIUCommand(UnitNode *selUN)
{
    requestAutoOnOffIUCommand(false, selUN);
}

void PortManager::requestAutoOnOffIUCommand(bool out, UnitNode *selUN) {
    if(TypeUnitNode::IU_BL_IP == selUN->getType()) {
        QPair<QString, QString> tmpPair(selUN->getUdpAdress(), QVariant(selUN->getUdpPort()).toString());
        for(const auto& pt : as_const(m_udpPortsVector)) {
            if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {
                bool needJour = true;
                for(AbstractRequester * ar : as_const(getLsWaiter())) {
                    if((RequesterType::AutoOnOffWaiter == ar->getRequesterType()) && (ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN))) {
                        ar->timerTripleStop();
                        ar->setBeatStatus(BeatStatus::Unsuccessful);

                        needJour = false;
//                        return;
                    }
                }

                OnOffIUWaiter * tmpOOIUW = new OnOffIUWaiter(selUN);
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
                    msg.setDirection(selUN->getUdpAdress());

                    if(out)
                        msg.setComment(tr("Удал. ком. Вкл"));
                    else
                        msg.setComment(tr("Послана ком. Вкл"));
                    DataBaseManager::insertJourMsg_wS(msg);
                    GraphTerminal::sendAbonentEventsAndStates(selUN, msg);
                }

                break;
            }
        }
    }
}

void PortManager::lockOpenCloseCommand(UnitNode *selUN, bool value)
{
    lockOpenCloseCommand(false, selUN, value);
}

void PortManager::requestModeSensor(UnitNode *selUN, QByteArray stateWord)
{
    if(nullptr == selUN || stateWord.isEmpty()) {
        return;
    } else if(selUN->getStateWord().size() > stateWord.size()) {
        return;
    }

    if(TypeUnitNode::RLM_C == selUN->getType()){
        ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(selUN);
        tmpCAW->init();

        DataQueueItem itm = tmpCAW->getFirstMsg();
        auto data = DataQueueItem::makeOnOff0x20(selUN);
        data[4] = stateWord.at(2);
        data[5] = stateWord.at(3);
        data.chop(1);
        data.append(Utils::getByteSumm(data)); //<CHKS>

        data.prepend(static_cast<quint8>(0xFF)).prepend(static_cast<quint8>(0xFF)).prepend(static_cast<quint8>(0xFF));

        itm.setData(data);

        tmpCAW->setFirstMsg(itm);

        connect(tmpCAW, &AbstractRequester::successful, [](){
            QMessageBox::information(nullptr,
                                 tr("Инфо"),
                                 tr("Параметры датчика записаны успешно!"),
                                 QMessageBox::Ok);
        });

        connect(tmpCAW, &AbstractRequester::unsuccessful, [](){
            QMessageBox::warning(nullptr,
                                 tr("Ошибка"),
                                 tr("Ошибка записи параметров датчика!"),
                                 QMessageBox::Ok);
        });

        appLsWaiter(tmpCAW);
    }
}

void PortManager::lockOpenCloseCommand(bool out, UnitNode *selUN, bool value)
{

    LockWaiter * lw = new LockWaiter(selUN);

    lw->init();
    appLsWaiter(lw);

    JourEntity msg;
    msg.setObject(selUN->getName());
    msg.setObjecttype(selUN->getType());
    msg.setD1(selUN->getNum1());
    msg.setD2(selUN->getNum2());
    msg.setD3(selUN->getNum3());
    msg.setDirection(selUN->getUdpAdress());

    if(out) {
        msg.setComment(tr("Удал. ком. ") + (value ? tr("Открыть") : tr("Закрыть")));
        msg.setType((value ? 1004 : 1003));
    } else {
        msg.setType((value ? 150 : 151));
        msg.setComment(tr("Послана ком. ") + (value ? tr("Открыть") : tr("Закрыть")));
    }
    DataBaseManager::insertJourMsg_wS(msg);
    GraphTerminal::sendAbonentEventsAndStates(selUN, msg);
    lw->startFirstRequest();
}

void PortManager::requestOnOffCommand(UnitNode *selUN, bool value)
{
    requestOnOffCommand(false, selUN, value);
}

void PortManager::requestOnOffCommand(bool out, UnitNode *selUN, bool value)
{
    if(!value) {
        if(TypeUnitNode::IU_BL_IP == selUN->getType()) {
            QPair<QString, QString> tmpPair(selUN->getUdpAdress(), QVariant(selUN->getUdpPort()).toString());
            for(const auto& pt : as_const(m_udpPortsVector)) {
                if(Port::typeDefPort(pt)->getStIpPort().contains(tmpPair)) {
                    for(AbstractRequester * ar : as_const(getLsWaiter())) {
                        if((RequesterType::AutoOnOffWaiter == ar->getRequesterType()) && (ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN))) {
                            ar->timerTripleStop();
                            ar->setBeatStatus(BeatStatus::Unsuccessful);
                        }
                    }
                }
            }
        }
    }

    UnitNode * reciver = selUN;
    UnitNode * target = selUN;

    if(TypeUnitNode::SD_BL_IP != target->getType() &&
       TypeUnitNode::IU_BL_IP != target->getType() &&
       TypeUnitNode::RLM_C != target->getType())
        return;

    if(!SettingUtils::getSetMetaRealUnitNodes().contains(reciver)) {
        for(const auto& un : as_const(SettingUtils::getSetMetaRealUnitNodes()))
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
    } else if(TypeUnitNode::RLM_C == target->getType()) {
        reciver = target;
    }
    int type = target->getType();

    if(nullptr != reciver) {

        if(TypeUnitNode::SD_BL_IP == reciver->getType() || TypeUnitNode::IU_BL_IP == reciver->getType() || TypeUnitNode::BL_IP == reciver->getType()) {
            for(const auto& un : as_const(reciver->getListChilde())) {
                if(type != un->getType())
                    continue;
                quint8 mask = un->mask();

                if(TypeUnitNode::SD_BL_IP == un->getType() &&
                   1 == un->isOff())
                    D1 = D1 & ~mask;
                else if(TypeUnitNode::IU_BL_IP == un->getType() &&
                        1 == un->isOff())
                    D1 = D1 & ~mask;
                else
                    D1 = D1 | mask;

                if(un == target && value)
                    D1 = D1 | mask;
                else if(un == target && !value)
                    D1 = D1 & ~mask;
            }
        }

        if(TypeUnitNode::BL_IP == reciver->getType()) {
            ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(reciver);
            tmpCAW->init();
            DataQueueItem itm = tmpCAW->getFirstMsg();
            QByteArray data;
            if(TypeUnitNode::SD_BL_IP == target->getType())
                data = DataQueueItem::makeOnOff0x20(target);
            else if(TypeUnitNode::IU_BL_IP == target->getType())
                data = DataQueueItem::makeOnOff0x23();
            data[4] = D1;
            data.chop(1);
            data.append(Utils::getByteSumm(data)); //<CHKS>
            itm.setData(data);
            tmpCAW->setFirstMsg(itm);
            appLsWaiter(tmpCAW);
    //        tmpCAW->startFirstRequest();

        } else if(TypeUnitNode::RLM_C == reciver->getType()) {
            ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(reciver);
            tmpCAW->init();
            DataQueueItem itm = tmpCAW->getFirstMsg();
            if(value)
                itm.setData(DataQueueItem::makeOn0x26(reciver));
            else
                itm.setData(DataQueueItem::makeOff0x25(reciver));
            tmpCAW->setFirstMsg(itm);
            appLsWaiter(tmpCAW);
        }

        if(target->getControl()) {
            JourEntity msg;
            msg.setObject(target->getName());
            msg.setObjecttype(target->getType());
            msg.setD1(target->getNum1());
            msg.setD2(target->getNum2());
            msg.setD3(target->getNum3());
            msg.setDirection(target->getUdpAdress());

            if(out) {
                msg.setComment(tr("Удал. ком. ") + (value ? tr("Вкл") : tr("Выкл")));
                msg.setType((value ? 1000 : 1001));
            } else {
                msg.setComment(tr("Послана ком. ") + (value ? tr("Вкл") : tr("Выкл")));
                msg.setType((value ? 130 : 131));
            }
            DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(target, msg);
        }
    }
}

GraphTerminal * PortManager::loadPortsTcpGraphTerminal(QString fileName) {

    QSettings settings(fileName, QSettings::IniFormat);
#if (defined (_WIN32) || defined (_WIN64))
    settings.setIniCodec( "Windows-1251" );
#else
    settings.setIniCodec( "UTF-8" );
#endif

    settings.beginGroup("INTEGRATION");
    int nPort = settings.value( "Port", -1 ).toInt();
    settings.endGroup();

    if(-1 != nPort)
        return new GraphTerminal(nPort);

    return nullptr;
}

QList<AbstractPort *> PortManager::loadPortsUdpObj(QString fileName) {
    QList<AbstractPort *> result;

    QSettings settings(fileName, QSettings::IniFormat);

    settings.beginGroup("TREE");
    int cntTrItm = settings.value( "Count", -1 ).toInt();
    settings.endGroup();

    qDebug() << "cntTrItm" << cntTrItm;
    if(0 >= cntTrItm)
        return result;

#if (defined (_WIN32) || defined (_WIN64))
    settings.setIniCodec( "Windows-1251" );
#else
    settings.setIniCodec( "UTF-8" );
#endif

    QSet<QPair<QString, QString> > stIpPort;
    QSet<QString> stPort;

    for(int index = 0; index < cntTrItm; index++)
    {
        QString strGroup("Obj_%1");
        strGroup = strGroup.arg(index + 1);
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
//    qDebug() << "Utils::parcingStatusWord0x41 -->";
    QByteArray newStateWord = item.data().mid(5, 4);
    resultRequest = item;
    resultRequest.setData();

    QSet<UnitNode *> tmpSet = SettingUtils::getSetMetaRealUnitNodes();
    for(UnitNode * un : tmpSet) {
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress())) || item.port() != un->getUdpPort() || static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1()))
            continue;
        QPointer<UnitNode> previousCopyUNLockSdBlIp = nullptr, previousCopyUNLockIuBlIp = nullptr;
        UnitNode * unLockSdBlIp = nullptr, * unLockIuBlIp = nullptr;
        bool isLockPair = false;
        if(1 <= un->getNum2() && 4 >= un->getNum2()) {
            UnitNode * reciver = un;
            while(nullptr != reciver) {
                if(TypeUnitNode::BL_IP == reciver->getType()) {
                    break;
                }
                reciver = reciver->getParentUN();
            }
            if(nullptr != reciver) {
                for(const auto& tmpUN : as_const(reciver->getListChilde())) {
                    if(TypeUnitNode::IU_BL_IP == tmpUN->getType() && tmpUN->getNum2() == un->getNum2()) {
                        previousCopyUNLockIuBlIp = UnitNodeFactory::make(*tmpUN);
                        unLockIuBlIp = tmpUN;
                        break;
                    }
                }

                for(const auto& tmpUN : as_const(reciver->getListChilde())) {
                    if(TypeUnitNode::SD_BL_IP == tmpUN->getType() && tmpUN->getNum2() == un->getNum2() && 0 != un->getBazalt()) {
                        previousCopyUNLockSdBlIp = UnitNodeFactory::make(*tmpUN);
                        unLockSdBlIp = tmpUN;
                        break;
                    }
                }
            }

            if(nullptr == unLockSdBlIp || nullptr == unLockIuBlIp) {
                if(nullptr != previousCopyUNLockIuBlIp.data()) {
                    delete previousCopyUNLockIuBlIp.data();
                    previousCopyUNLockIuBlIp = nullptr;
                }
                unLockIuBlIp = nullptr;
                if(nullptr != previousCopyUNLockSdBlIp.data()) {
                    delete previousCopyUNLockSdBlIp.data();
                    previousCopyUNLockSdBlIp = nullptr;
                }
                unLockSdBlIp = nullptr;
                isLockPair = false;
            } else if(0 != unLockSdBlIp->getBazalt()) {
                isLockPair = true;
            }
        }
        QPointer<UnitNode> previousCopyUN = UnitNodeFactory::make(*un);
        un->setStateWord(newStateWord);
        un->updDoubl();

        if(isLockPair) {
            unLockSdBlIp->setStateWord(newStateWord);
            unLockIuBlIp->setStateWord(newStateWord);
        }

        if(TypeUnitNode::BL_IP == un->getType()) {
            if((un->isWasDK() != previousCopyUN->isWasDK()) ||
               (un->isExistDK() != previousCopyUN->isExistDK())) {
                un->setStateWord(newStateWord);
                un->updDoubl();
                SignalSlotCommutator::getInstance()->emitUpdUN();
            }
        }

        if(0 != un->getDK() &&
           DKCiclStatus::DKIgnore != previousCopyUN->getDkStatus() &&
           DKCiclStatus::DKWrong != previousCopyUN->getDkStatus() &&
           DKCiclStatus::DKDone != previousCopyUN->getDkStatus() &&
           un->getDkInvolved()) {
//            qDebug() << "DkStatus --> " << un->toString();
            int unCalcDkStatus = un->calcDKStatus();
//            qDebug() << "DkStatus -- unCalcDkStatus " << unCalcDkStatus;
//            qDebug() << "DkStatus -- unDkStatus " << un->getDkStatus();
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
            un->updDoubl();
//            qDebug() << "DkStatus -- unNewDkStatus " << un->getDkStatus();
//            qDebug() << "DkStatus <--";
        }

        if((!previousCopyUN.isNull() && nullptr != un && (previousCopyUN->getStateWord() != un->getStateWord())) ||
           (!previousCopyUNLockSdBlIp.isNull() && nullptr != unLockSdBlIp && (previousCopyUNLockSdBlIp->getStateWord() != unLockSdBlIp->getStateWord())) ||
           (!previousCopyUNLockIuBlIp.isNull() && nullptr != unLockIuBlIp && (previousCopyUNLockIuBlIp->getStateWord() != unLockIuBlIp->getStateWord()))) {
            un->setStateWord(newStateWord);
            if(nullptr != unLockIuBlIp && nullptr != unLockSdBlIp && isLockPair) {
                unLockSdBlIp->setStateWord(newStateWord);
                unLockIuBlIp->setStateWord(newStateWord);
            }

            un->updDoubl();
            SignalSlotCommutator::getInstance()->emitUpdUN();

            if(!un->getDkInvolved()) {

                JourEntity msg;
                msg.setObject(un->getName());
                msg.setObjecttype(un->getType());
                msg.setD1(un->getNum1());
                msg.setD2(un->getNum2());
                msg.setD3(un->getNum3());
                msg.setDirection(un->getUdpAdress());

                if((un->getControl() && !isLockPair && 1 != previousCopyUN->isConnected() && 1 != previousCopyUN->isOn() && 1 == un->isOn())) {
                    JourEntity msgOn;
                    msgOn.setObject(un->getName());
                    msgOn.setObjecttype(un->getType());
                    msgOn.setD1(un->getNum1());
                    msgOn.setD2(un->getNum2());
                    msgOn.setD3(un->getNum3());
                    msgOn.setType(101);
                    msgOn.setDirection(un->getUdpAdress());
                    msgOn.setComment(QObject::tr("Вкл"));
                    DataBaseManager::insertJourMsg_wS(msgOn);
                    GraphTerminal::sendAbonentEventsAndStates(un, msgOn);
                }

                if(isLockPair) {
                    if(
                            (1 == previousCopyUNLockSdBlIp->isAlarm() &&
                             1 == previousCopyUNLockIuBlIp->isOff() && //Открыто
                             1 == unLockSdBlIp->isAlarm() &&
                             1 == unLockIuBlIp->isOn()) || //Открыто ключом

                            (1 == previousCopyUNLockSdBlIp->isNorm() &&
                             1 == previousCopyUNLockIuBlIp->isOn() && //Закрыто
                             1 == unLockSdBlIp->isNorm() &&
                             1 == unLockIuBlIp->isOff())) //Закрыто ключом
                    {
                        qDebug() << "isLockPair continue " << un->toString();
                        if(nullptr != previousCopyUNLockSdBlIp.data()) {
                            delete previousCopyUNLockSdBlIp.data();
                            previousCopyUNLockSdBlIp = nullptr;
                        }
                        if(nullptr != previousCopyUNLockIuBlIp.data()) {
                            delete previousCopyUNLockIuBlIp.data();
                            previousCopyUNLockIuBlIp = nullptr;
                        }
                        if(nullptr != previousCopyUN.data()) {
                            delete previousCopyUN.data();
                            previousCopyUN = nullptr;
                        }
                        continue;
                    }

/*                    if(1 == previousCopyUNLockSdBlIp->isAlarm() &&
                       1 == previousCopyUNLockIuBlIp->isOff()) {
                        //Открыто
//                        qDebug() << "isLockPair Old O " << un->toString();
                    } else if(1 == previousCopyUNLockSdBlIp->isNorm() &&
                              1 == previousCopyUNLockIuBlIp->isOn()) {
                        //Закрыто
//                        qDebug() << "isLockPair Old L " << un->toString();
                    } else if(1 == previousCopyUNLockSdBlIp->isAlarm() &&
                              1 == previousCopyUNLockIuBlIp->isOn()) {
                        //Открыто ключом
//                        qDebug() << "isLockPair Old OK " << un->toString();
                    } else if(1 == previousCopyUNLockSdBlIp->isNorm() &&
                              1 == previousCopyUNLockIuBlIp->isOff()) {
                        //Закрыто ключом
//                        qDebug() << "isLockPair Old LK " << un->toString();
                    }

                    if(1 == unLockSdBlIp->isAlarm() &&
                       1 == unLockIuBlIp->isOff()) {
                        //Открыто
//                        qDebug() << "isLockPair New O " << un->toString();
                    } else if(1 == unLockSdBlIp->isNorm() &&
                              1 == unLockIuBlIp->isOn()) {
                        //Закрыто
//                        qDebug() << "isLockPair New L " << un->toString();
                    } else if(1 == unLockSdBlIp->isAlarm() &&
                              1 == unLockIuBlIp->isOn()) {
                        //Открыто ключом
//                        qDebug() << "isLockPair New OK " << un->toString();
                    } else if(1 == unLockSdBlIp->isNorm() &&
                              1 == unLockIuBlIp->isOff()) {
                        //Закрыто ключом
//                        qDebug() << "isLockPair New LK " << un->toString();
                    }*/

                    msg.setObject(unLockSdBlIp->getName());
//                    qDebug() << "isLockPair " << un->getName();
                    if(1 == unLockSdBlIp->isAlarm() &&
                       1 == unLockIuBlIp->isOff()) {
                        //Открыто
                        msg.setComment(QObject::tr("Открыто"));
                        msg.setType(111);
                    } else if(1 == unLockSdBlIp->isNorm() &&
                              1 == unLockIuBlIp->isOn()) {
                        //Закрыто
                        msg.setComment(QObject::tr("Закрыто"));
                        msg.setType(110);
                    } else if(1 == unLockSdBlIp->isAlarm() &&
                              1 == unLockIuBlIp->isOn()) {
                        //Открыто ключом
                        msg.setComment(QObject::tr("Открыто ключом"));
                        msg.setType(113);
                    } else if(1 == unLockSdBlIp->isNorm() &&
                              1 == unLockIuBlIp->isOff()) {
                        //Закрыто ключом
                        msg.setComment(QObject::tr("Закрыто ключом"));
                        msg.setType(112);
                    }

                    if(
                    (1 == previousCopyUNLockSdBlIp->isAlarm() &&
                     1 == previousCopyUNLockIuBlIp->isOn() &&  //Открыто ключом
                     1 == unLockSdBlIp->isAlarm() &&
                     1 == unLockIuBlIp->isOff()) ||//Открыто

                    (1 == previousCopyUNLockSdBlIp->isNorm() &&
                     1 == previousCopyUNLockIuBlIp->isOff() && //Закрыто ключом
                     1 == unLockSdBlIp->isNorm() &&
                     1 == unLockIuBlIp->isOn()) || //Закрыто

                    (1 == previousCopyUNLockSdBlIp->isAlarm() &&
                     1 == previousCopyUNLockIuBlIp->isOff() && //Открыто
                     1 == unLockSdBlIp->isAlarm() &&
                     1 == unLockIuBlIp->isOn()) || //Открыто ключом

                     (1 == previousCopyUNLockSdBlIp->isNorm() &&
                      1 == previousCopyUNLockIuBlIp->isOn() && //Закрыто
                      1 == unLockSdBlIp->isNorm() &&
                      1 == unLockIuBlIp->isOff())) //Закрыто ключом
                    {
                        qDebug() << "isLockPair not jour " << un->toString();
                    } else {
                        SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    }

                    QPair<QString, QString> tmpPair(Utils::hostAddressToString(item.address()), QVariant(item.port()).toString());

                    for(AbstractRequester * ar : as_const(getLsWaiter())) {
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

                } else if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (1 == un->isAlarm()) && (1 == un->isWasAlarm()) && (previousCopyUN->isAlarm() != un->isAlarm() || previousCopyUN->isWasAlarm() != un->isWasAlarm())) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::tr("Тревога-СРАБОТКА"));
                    msg.setType(20);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    //нужен сброс
                    resultRequest.setData(DataQueueItem::makeAlarmReset0x24(un));
                } else if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (1 == un->isNorm()) && (previousCopyUN->isNorm() != un->isNorm())) {
                    msg.setComment(QObject::tr("Норма"));
                    msg.setType(1);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                } else if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (1 == un->isOff()) && (previousCopyUN->isOff() != un->isOff())) {
                    msg.setComment(QObject::tr("Выкл"));
                    msg.setType(100);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                } if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (1 == un->isOn()) && (previousCopyUN->isOn() != un->isOn())) {
                    msg.setComment(QObject::tr("Вкл"));
                    msg.setType(101);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                } else if(un->getControl() && (TypeUnitNode::IU_BL_IP == un->getType()) && (1 == un->isOff()) && (previousCopyUN->isOff() != un->isOff())) {
                    msg.setComment(QObject::tr("Выкл"));
                    msg.setType(100);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                } else if(un->getControl() && (TypeUnitNode::IU_BL_IP == un->getType()) && (1 == un->isOn()) && (previousCopyUN->isOn() != un->isOn())) {
                    msg.setComment(QObject::tr("Вкл"));
                    msg.setType(101);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                }
            }

            if(!un->getDkInvolved() && (TypeUnitNode::SD_BL_IP == un->getType() /*&& 0 != un->getBazalt()*/) && (1 == un->isAlarm()) && (1 == un->isWasAlarm()) && (previousCopyUN->isAlarm() != un->isAlarm() || previousCopyUN->isWasAlarm() != un->isWasAlarm())) {
                //сохранение Тревога или Норма
                if(0 != un->treeChildCount()) {
                    for(const auto& iuun : as_const(un->treeChild())) {
                        if(TypeUnitNode::IU_BL_IP == iuun->getType()) {
                            qDebug() << "Utils::parcingStatusWord0x41 emitAutoOnOffIU";
                            SignalSlotCommutator::getInstance()->emitAutoOnOffIU(iuun);
                        }
                    }
                }

                //нужен сброс
            }
        }

        if(nullptr != previousCopyUNLockSdBlIp.data()) {
            delete previousCopyUNLockSdBlIp.data();
            previousCopyUNLockSdBlIp = nullptr;
        }
        if(nullptr != previousCopyUNLockIuBlIp.data()) {
            delete previousCopyUNLockIuBlIp.data();
            previousCopyUNLockIuBlIp = nullptr;
        }
        if(nullptr != previousCopyUN.data()) {
            delete previousCopyUN.data();
            previousCopyUN = nullptr;
        }
    }
//    qDebug() << "Utils::parcingStatusWord0x41 <--";
    return resultRequest;
}

DataQueueItem PortManager::parcingStatusWord0x31(DataQueueItem &item, DataQueueItem &resultRequest)
{
//    qDebug() << "Utils::parcingStatusWord0x31 -->";
    QByteArray newStateWord = item.data().mid(5, 4);
    resultRequest = item;
    resultRequest.setData();

    QSet<UnitNode *> tmpSet = SettingUtils::getSetMetaRealUnitNodes();
    for(UnitNode * un : tmpSet) {
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress())) || item.port() != un->getUdpPort() || static_cast<quint8>(item.data().at(2)) != static_cast<quint8>(un->getNum1()))
            continue;

        QPointer<UnitNode> previousCopyUN = UnitNodeFactory::make(*un);

        if(nullptr == un || previousCopyUN.isNull()) {
            if(!previousCopyUN.isNull()) {
                delete previousCopyUN.data();
                previousCopyUN = nullptr;
            }
            continue;
        }

        un->setStateWord(newStateWord);
        un->updDoubl();
        SignalSlotCommutator::getInstance()->emitUpdUN();


        if(!previousCopyUN.isNull() && nullptr != un && (previousCopyUN->getStateWord() != un->getStateWord())) {
            if(un->getDkInvolved()) {
                procDK(un, previousCopyUN);
            } else if(!un->getDkInvolved()) {

                JourEntity msg;
                msg.setObject(un->getName());
                msg.setObjecttype(un->getType());
                msg.setD1(un->getNum1());
                msg.setD2(un->getNum2());
                msg.setD3(un->getNum3());
                msg.setDirection(un->getUdpAdress());

                if((un->getControl() && 1 != previousCopyUN->isConnected() && 1 != previousCopyUN->isOn() && 1 == un->isOn())) {
                    JourEntity msgOn;
                    msgOn.setObject(un->getName());
                    msgOn.setObjecttype(un->getType());
                    msgOn.setD1(un->getNum1());
                    msgOn.setD2(un->getNum2());
                    msgOn.setD3(un->getNum3());
                    msgOn.setType(101);
                    msgOn.setDirection(un->getUdpAdress());
                    msgOn.setComment(QObject::tr("Вкл"));
                    DataBaseManager::insertJourMsg_wS(msgOn);
                    GraphTerminal::sendAbonentEventsAndStates(un, msgOn);
                }

                if(un->getControl() && (TypeUnitNode::RLM_C == un->getType()) && (1 == un->isAlarm()) && (1 == un->isWasAlarm()) && (previousCopyUN->isAlarm() != un->isAlarm() || previousCopyUN->isWasAlarm() != un->isWasAlarm())) {
                    //сохранение Тревога или Норма
                    if(1 == un->isOn()) {
                        msg.setComment(QObject::tr("Тревога-СРАБОТКА"));
                        msg.setType(20);
                        SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                        //нужен сброс
                        resultRequest.setData(DataQueueItem::makeAlarmReset0x24(un));
                    }
                } else if(un->getControl() && (TypeUnitNode::RLM_C == un->getType()) && (1 == un->isNorm()) && (previousCopyUN->isNorm() != un->isNorm())) {
                    msg.setComment(QObject::tr("Норма"));
                    msg.setType(1);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                } else if(un->getControl() && (TypeUnitNode::RLM_C == un->getType()) && (1 == un->isOff()) && (previousCopyUN->isOff() != un->isOff())) {
                    msg.setComment(QObject::tr("Выкл"));
                    msg.setType(100);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                } else if(un->getControl() && (TypeUnitNode::RLM_C == un->getType()) && (1 == un->isOn()) && (previousCopyUN->isOn() != un->isOn())) {
                    msg.setComment(QObject::tr("Вкл"));
                    msg.setType(101);
                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                }
            }

            if(!un->getDkInvolved() && (TypeUnitNode::RLM_C == un->getType() /*&& 0 != un->getBazalt()*/) && (1 == un->isAlarm()) && (1 == un->isWasAlarm()) && (previousCopyUN->isAlarm() != un->isAlarm() || previousCopyUN->isWasAlarm() != un->isWasAlarm())) {
                //сохранение Тревога или Норма
                qDebug() << "need reset alarm " << un->toString();
                if(0 != un->treeChildCount()) {
                    for(const auto& iuun : as_const(un->treeChild())) {
                        if(TypeUnitNode::SYSTEM == iuun->getType()) {
//                            qDebug() << "Utils::parcingStatusWord0x31 emitAutoOnOffIU";
                            SignalSlotCommutator::getInstance()->emitAutoOnOffIU(iuun);
                        }
                    }
                }

                //нужен сброс
            }

        }

        if(!previousCopyUN.isNull()) {
            delete previousCopyUN.data();
            previousCopyUN = nullptr;
        }
    }
//    qDebug() << "Utils::parcingStatusWord0x31 -->";
    return resultRequest;
}

void PortManager::procDK(UnitNode * current, UnitNode * previous) {
    if(nullptr == current || nullptr == previous)
        return;
    if(0 != current->getDK() &&
       DKCiclStatus::DKIgnore != previous->getDkStatus() &&
       DKCiclStatus::DKWrong != previous->getDkStatus() &&
       DKCiclStatus::DKDone != previous->getDkStatus() &&
       current->getDkInvolved()) {
//            qDebug() << "DkStatus --> " << current->toString();
        int unCalcDkStatus = current->calcDKStatus();
//            qDebug() << "DkStatus -- unCalcDkStatus " << unCalcDkStatus;
//            qDebug() << "DkStatus -- unDkStatus " << current->getDkStatus();
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
//            qDebug() << "DkStatus -- unNewDkStatus " << current->getDkStatus();
//            qDebug() << "DkStatus <--";
    }
}


void PortManager::manageOverallReadQueue()
{
    QList<DataQueueItem> tmpQueue = popOverallReadQueue();
    for (DataQueueItem itm : tmpQueue) {
        QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
//        AbstractPort * pt = m_udpPortsVector.value(itm.portIndex(), nullptr);
        if(DataQueueItem::isValideDirectionI(itm)) {
            quint8 CMD = itm.data().at(4);
            switch (CMD) {
            case static_cast<quint8>(0x41): {
                for(AbstractRequester * scr : as_const(this->lsSCR)) {
                    if(scr->getIpPort() == tmpPair && TypeUnitNode::BL_IP == static_cast<quint8>(scr->getUnReciver()->getType())) {
                        scr->resetBeatCount();
                        break;
                    }
                }
                DataQueueItem request;
                parcingStatusWord0x41(itm, request);

                QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
                bool dkWait = false;
                for(const AbstractRequester * ar : as_const(getLsWaiter())) {
                    if((RequesterType::DKWaiter == ar->getRequesterType()) && //(ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN)))
                        ar->getIpPort() == tmpPair) {
                        dkWait = true;
                        break;
                    }
                }

                if(request.isValid() && !dkWait) {
                    UnitNode * reciver = nullptr;
                    for(const auto& un : as_const(SettingUtils::getSetMetaRealUnitNodes())) {
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
            case static_cast<quint8>(0x31): {
                for(AbstractRequester * scr : as_const(this->lsSCR)) {
                    if(scr->getIpPort() == tmpPair && TypeUnitNode::RLM_C == static_cast<quint8>(scr->getUnReciver()->getType()) && static_cast<quint8>(scr->getUnReciver()->getNum1()) == static_cast<quint8>(itm.data().at(2))) {
                        scr->resetBeatCount();
                        break;
                    }
                }
                DataQueueItem request;
                parcingStatusWord0x31(itm, request);

                QPair<QString, QString> tmpPair(Utils::hostAddressToString(itm.address()), QVariant(itm.port()).toString());
                bool dkWait = false;
                for(const AbstractRequester * ar : as_const(getLsWaiter())) {
                    if((RequesterType::DKWaiter == ar->getRequesterType()) && //(ar->getUnTarget() == selUN || ar->getUnTarget()->getDoubles().contains(selUN)))
                        ar->getIpPort() == tmpPair) {
                        dkWait = true;
                        break;
                    }
                }

                if(request.isValid() && !dkWait) {
                    UnitNode * reciver = nullptr;
                    for(const auto& un : as_const(SettingUtils::getSetMetaRealUnitNodes())) {
                        reciver = un;
                        if(TypeUnitNode::RLM_C == reciver->getType() &&
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
                } else if(dkWait) {
                    UnitNode * reciver = nullptr;
                    for(const auto& un : as_const(SettingUtils::getSetMetaRealUnitNodes())) {
                        reciver = un;
                        if(TypeUnitNode::RLM_C == reciver->getType() &&
                                reciver->getUdpAdress() == Utils::hostAddressToString(request.address()) &&
                                reciver->getUdpPort() == request.port()) {

                            if(reciver->getDkInvolved() && DKCiclStatus::DKWasAlarn == reciver->getDkStatus()) {
                                ConfirmationAdmissionWaiter * tmpCAW = new ConfirmationAdmissionWaiter(reciver);
                                tmpCAW->init();
                                tmpCAW->setUnReciver(reciver);
                                DataQueueItem request24 = itm;
                                request24.setData(DataQueueItem::makeAlarmReset0x24(reciver));
                                tmpCAW->setFirstMsg(request24);
                                preppLsWaiter(tmpCAW);
                            }
                        }

                    }
                }
                break;
            }
            case static_cast<quint8>(0x30): {

                for(AbstractRequester * ar : as_const(getLsWaiter())) {
                    if(ar->getIpPort() == tmpPair ) {

                        if(BeatStatus::RequestStep1 == ar->getBeatStatus()) { // переводим в первое ожидание

                            if(RequesterType::DKWaiter == ar->getRequesterType() && static_cast<quint8>(ar->getUnReciver()->getNum1()) == static_cast<quint8>(itm.data().at(2))) {
                                for(UnitNode * un : as_const(((ProcessDKWaiter *)ar)->getLsTrackedUN())) {
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
                                for(UnitNode * un : as_const(((ProcessDKWaiter *)ar)->getLsTrackedUN())) {
                                    JourEntity msg;
                                    msg.setObject(un->getName());
                                    msg.setObjecttype(un->getType());
                                    msg.setD1(un->getNum1());
                                    msg.setD2(un->getNum2());
                                    msg.setD3(un->getNum3());
                                    msg.setDirection(un->getUdpAdress());

                                    if(DKCiclStatus::DKDone == un->getDkStatus()) {
                                        msg.setComment(tr("Ком. ДК выполнена"));
                                        msg.setType(3);
                                    } else {
                                        msg.setComment(tr("Ком. ДК не выполнена"));
                                        msg.setType(11);
                                    }
                                    un->setDkInvolved(false);
                                    un->setDkStatus(DKCiclStatus::DKIgnore);
                                    un->updDoubl();
                                    if(un->getControl()) {
                                        DataBaseManager::insertJourMsg_wS(msg);
                                        GraphTerminal::sendAbonentEventsAndStates(un, msg);
                                    }
                                }
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
            for(AbstractRequester * ar : as_const(getLsWaiter())) {
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

void PortManager::unLostedConnect(UnitNode *un) const
{
//    qDebug() << "PortManager::unLostedConnect(" << un << ")";
    if(1 == un->isConnected()) {
        un->setStateWord(QByteArray());

        if(un->getControl() && !un->getName().isEmpty()) {
            JourEntity msg;
            msg.setObject(un->getName());
            msg.setType(10);
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setDirection(un->getUdpAdress());
            msg.setComment(tr("Нет связи"));
            DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(un, msg);
        }
    }


    for(const auto& uncld : as_const(un->getListChilde())) {
        if(TypeUnitNode::IU_BL_IP == uncld->getType() || TypeUnitNode::SD_BL_IP == uncld->getType() /* или датчик */) {
            unLostedConnect(uncld);
        }
    }

    for(AbstractRequester * scr : as_const(lsSCR)) {
        if(scr->getUnReciver() == un && BeatStatus::Unsuccessful == scr->getBeatStatus()) {
            scr->startFirstRequest();
            break;
        }
    }

    SignalSlotCommutator::getInstance()->emitUpdUN();

}
