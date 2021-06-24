#include "AbstractRequester.h"

void AbstractRequester::timerTripleStop() {
    timerFirstStop();
    timerSecondStop();
    timerEndStop();
}

AbstractRequester::AbstractRequester(QSharedPointer<UnitNode> target, RequesterType requesterType) : QObject(target.data()) {
//        //qDebug() << "AbstractRequester::AbstractRequester(" << this << ") -->";
    setUnTarget(target);
    setRequesterType(requesterType);
//        //qDebug() << "AbstractRequester::AbstractRequester(" << this << ") -- getRequesterType( " << getRequesterType() << " )";
    setBeatStatus(BeatStatus::Start);
//        //qDebug() << "AbstractRequester::AbstractRequester(" << this << ") <--";
}

AbstractRequester::~AbstractRequester() {
//        //qDebug() << "AbstractRequester::~AbstractRequester(" << this << ") -->";
    timerTripleStop();
    ptrPort = nullptr;
//        //qDebug() << "AbstractRequester::~AbstractRequester(" << this << ") <--";
}

bool AbstractRequester::isValid() {
//        //qDebug() << "AbstractRequester::isValid(" << this << ") -->";
    bool result = true;

    result = result && (nullptr != getPtrPort());
//        //qDebug() << "AbstractRequester::isValid(" << this << ") -- getPtrPort " << result;
    result = result && (!getUnTarget().isNull());
//        //qDebug() << "AbstractRequester::isValid(" << this << ") -- getUnTarget " << result;
    result = result && (!getUnReciver().isNull());
//        //qDebug() << "AbstractRequester::isValid(" << this << ") -- getUnReciver " << result;
    if(BeatStatus::Start != getBeatStatus()) {
        result = result && getFirstMsg().isValid();
//            //qDebug() << "AbstractRequester::isValid(" << this << ") -- getFirstMsg " << result;
        result = result && (0 == getTimeIntervalWaiteFirst() || getSecondMsg().isValid());
//            //qDebug() << "AbstractRequester::isValid(" << this << ") -- getSecondMsg " << result;
    }
//        //qDebug() << "AbstractRequester::isValid(" << this << ") -- result " << result;
//    //qDebug() << "AbstractRequester::isValid(" << this << ") <--";
    return result;
}

BeatStatus AbstractRequester::getBeatStatus() const {
    return beatStatus;
}

void AbstractRequester::setBeatStatus(const BeatStatus value) {
    beatStatus = value;
}

//Step#1 -->
void AbstractRequester::timerFirstStart(int interval) {
    if(timerFirst.isNull()) {
        timerFirst = QSharedPointer<QTimer>::create();
    }
    timerFirst->setInterval(interval);
    timerFirst->setSingleShot(true);
    timerFirst->connect(timerFirst.data(), SIGNAL(timeout()), this, SLOT(beatRepeatFirstRequest()));
    timerFirst->start();
}

void AbstractRequester::timerFirstStop() {
    if(!timerFirst.isNull()) {
        timerFirst->stop();
        timerFirst.clear();
    }
}

void AbstractRequester::startFirstRequest(int delay) {
//        //qDebug() << "AbstractRequester::startFirstRequest(" << this << ") -->";
    timerTripleStop();
    resetBeatCount();
    setBeatStatus(BeatStatus::RequestStep1);
    if(delay){
        if(!timerFirst.isNull()) {
            timerFirst.clear();
        }
        if(timerFirst.isNull()) {
            timerFirst = QSharedPointer<QTimer>::create();
        }
        timerFirst->setInterval(delay);
        timerFirst->setSingleShot(true);
        timerFirst->singleShot(delay, this, SLOT(beatRepeatFirstRequest()));

    } else {
        beatRepeatFirstRequest();
    }
//        //qDebug() << "AbstractRequester::startFirstRequest(" << this << ") <--";
}

void AbstractRequester::firstRequest() {
//        //qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") -->";
    timerTripleStop();
    if(0 != getMaxBeatCount() && getMaxBeatCount() <= getBeatCount()) {
        timerTripleStop();
        setBeatStatus(BeatStatus::Unsuccessful);
        emit importantBeatStatus();
        emit unsuccessful();
//            //qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") <-- Unsuccessful";
        return;
    }

//        qDebug() << "beatRepeatFirstRequest("<<this<<") -- makeFirstMsg " << getUnReciver()->toString();
    setFirstMsg(makeFirstMsg());

    if(!getFirstMsg().isValid()) {
        timerTripleStop();
        setBeatStatus(BeatStatus::Unsuccessful);
        emit importantBeatStatus();
        emit unsuccessful();
//            //qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") <-- Unsuccessful";
        return;
    }

//        qDebug() << "beatRepeatFirstRequest("<<this<<") -- write " << QTime::currentTime().toString("hh:mm:ss.zzz") << getFirstMsg().data().toHex();
    if(ConnectRequester == getRequesterType()) {
        qDebug() << "ConnectRequester beatRepeatFirstRequest() " << getFirstMsg().data().toHex();
    }

    if(DKWaiter == getRequesterType() ||
       AutoOnOffWaiter == getRequesterType() ||
       ConfirmWaiter == getRequesterType() ||
       LockRequester == getRequesterType()) {
        getUnReciver()->queueMsg.enqueue(getFirstMsg());
    } else {
        Port::typeDefPort(getPtrPort())->write(getFirstMsg(), false);
    }
//        Port::typeDefPort(getPtrPort())->write(getFirstMsg(), false);
    setBeatCount(getBeatCount() + 1);
    timerFirstStart(getTimeIntervalRequest());
//        //qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") <--";
}
//Step#1 <--

//Step#1->#2 -->
void AbstractRequester::startWaiteSecondRequest() {
//        //qDebug() << "AbstractRequester::startWaiteSecondRequest(" << this << ") -->";
    timerTripleStop();

    if(0 == getTimeIntervalWaiteFirst()) {
        timerTripleStop();
        setBeatStatus(BeatStatus::Successful);
        emit importantBeatStatus();
        emit successful();
//            //qDebug() << "AbstractRequester::startWaiteSecondRequest(" << this << ") <-- Unsuccessful";
        return;
    }

    setBeatStatus(BeatStatus::Waite);
    resetBeatCount();

    timerSecondStart(getTimeIntervalWaiteFirst());
//        //qDebug() << "AbstractRequester::startWaiteSecondRequest(" << this << ") <--";
}
//Step#1->#2 <--

//Step#2 -->

void AbstractRequester::timerSecondStart(int interval) {
    if(timerSecond.isNull()) {
        timerSecond = QSharedPointer<QTimer>::create();
    }
    timerSecond->setInterval(interval);
    timerSecond->setSingleShot(true);
    timerSecond->connect(timerSecond.data(), SIGNAL(timeout()), this, SLOT(startSecondRequest()));
    timerSecond->start();
}

void AbstractRequester::timerSecondStop() {
    if(!timerSecond.isNull()) {
        timerSecond->stop();
        timerSecond.clear();
    }
}

void AbstractRequester::startSecondRequest(int delay) {
//        //qDebug() << "AbstractRequester::startSecondRequest(" << this << ") -->";
    timerTripleStop();
    resetBeatCount();
    setBeatStatus(BeatStatus::RequestStep2);
    if(delay){
        if(!timerSecond.isNull()) {
            timerSecond.clear();
        }
        if(timerSecond.isNull()) {
            timerSecond = QSharedPointer<QTimer>::create();
        }
        timerSecond->setInterval(delay);
        timerSecond->setSingleShot(true);
        timerSecond->singleShot(delay, this, SLOT(beatRepeatSecondRequest()));

    } else {
        beatRepeatSecondRequest();
    }
//        //qDebug() << "AbstractRequester::startSecondRequest(" << this << ") <--";
}

void AbstractRequester::secondRequest() {
//        //qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") -->";
    timerTripleStop();

    if(0 != getMaxBeatCount() && getMaxBeatCount() <= getBeatCount()) {
        timerTripleStop();
        setBeatStatus(BeatStatus::Unsuccessful);
        emit importantBeatStatus();
        emit unsuccessful();
//            //qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") <-- Unsuccessful";
        return;
    }

    setSecondMsg(makeSecondMsg());

    if(!getSecondMsg().isValid()) {
        timerTripleStop();
        setBeatStatus(BeatStatus::Unsuccessful);
        emit importantBeatStatus();
        emit unsuccessful();
//            //qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") <-- Unsuccessful";
        return;
    }

    if(DKWaiter == getRequesterType() ||
       AutoOnOffWaiter == getRequesterType() ||
       ConfirmWaiter == getRequesterType() ||
       LockRequester == getRequesterType()) {
        getUnReciver()->queueMsg.enqueue(getSecondMsg());
    } else {
        Port::typeDefPort(getPtrPort())->write(getSecondMsg(), false);
    }
//        Port::typeDefPort(ptrPort)->write(getSecondMsg(), false);
    setBeatCount(getBeatCount() + 1);
    timerSecondStart(getTimeIntervalRequest());
//        //qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") <--";
}
//Step#2 <--

//Step#2->#end -->
void AbstractRequester::startWaiteEndSecondWaite() {
//        //qDebug() << "AbstractRequester::startWaiteEndSecondWaite(" << this << ") -->";
    timerTripleStop();

    if(0 == getTimeIntervalWaiteSecond()) {
        timerTripleStop();
        setBeatStatus(BeatStatus::Successful);
        emit importantBeatStatus();
        emit successful();
//            //qDebug() << "AbstractRequester::startWaiteEndSecondWaite(" << this << ") <-- Unsuccessful";
        return;
    }

    setBeatStatus(BeatStatus::WaiteEnd);
    resetBeatCount();

    timerEndStart(getTimeIntervalWaiteSecond());
//        //qDebug() << "AbstractRequester::startWaiteEndSecondWaite(" << this << ") <--";
}
//Step#2->#end <--

//Step#end -->
void AbstractRequester::timerEndStart(int interval) {
    if(timerEnd.isNull()) {
        timerEnd = QSharedPointer<QTimer>::create();
    }
    timerEnd->setInterval(interval);
    timerEnd->setSingleShot(true);
    timerEnd->connect(timerEnd.data(), SIGNAL(timeout()), this, SLOT(startEnd()));
    timerEnd->start();
}

void AbstractRequester::timerEndStop() {
    if(!timerEnd.isNull()) {
        timerEnd->stop();
        timerEnd.clear();
    }
}

void AbstractRequester::startEnd(int delay) {
//        //qDebug() << "AbstractRequester::startSecondRequest(" << this << ") -->";
    timerTripleStop();
    resetBeatCount();
    setBeatStatus(BeatStatus::End);
    if(delay){
        if(!timerEnd.isNull()) {
            timerEnd.clear();
        }
        if(timerEnd.isNull()) {
            timerEnd = QSharedPointer<QTimer>::create();
        }
        timerEnd->setInterval(delay);
        timerEnd->setSingleShot(true);
        timerEnd->singleShot(delay, this, SLOT(beatRepeatEnd()));

    } else {
        beatRepeatEnd();
    }
//        //qDebug() << "AbstractRequester::startSecondRequest(" << this << ") <--";
}

void AbstractRequester::endRequest() {
//        //qDebug() << "AbstractRequester::beatRepeatEnd(" << this << ") -->";
    timerTripleStop();

    if(0 != getMaxBeatCount() && getMaxBeatCount() <= getBeatCount()) {
        timerTripleStop();
        setBeatStatus(BeatStatus::Unsuccessful);
        emit importantBeatStatus();
        emit unsuccessful();
//            //qDebug() << "AbstractRequester::beatRepeatEnd(" << this << ") <-- Unsuccessful";
        return;
    }

    setEndMsg(makeEndMsg());

    if(!getEndMsg().isValid()) {
        timerTripleStop();
        setBeatStatus(BeatStatus::Unsuccessful);
        emit importantBeatStatus();
        emit unsuccessful();
//            //qDebug() << "AbstractRequester::beatRepeatEnd(" << this << ") <-- Unsuccessful";
        return;
    }

    if(DKWaiter == getRequesterType() ||
       AutoOnOffWaiter == getRequesterType() ||
       ConfirmWaiter == getRequesterType() ||
       LockRequester == getRequesterType()) {
        getUnReciver()->queueMsg.enqueue(getEndMsg());
    } else {
        Port::typeDefPort(getPtrPort())->write(getEndMsg(), false);
    }
//        Port::typeDefPort(ptrPort)->write(getEndMsg(), false);
    setBeatCount(getBeatCount() + 1);
    timerEndStart(getTimeIntervalRequest());
//        //qDebug() << "AbstractRequester::beatRepeatEnd(" << this << ") <--";
}
//Step#end <--

QSharedPointer<UnitNode> AbstractRequester::getUnTarget() const { return unTarget; }
void AbstractRequester::setUnTarget(QSharedPointer<UnitNode> value) { unTarget = value; }

QSharedPointer<UnitNode> AbstractRequester::getUnReciver() const  { return unReciver; }
void AbstractRequester::setUnReciver(QSharedPointer<UnitNode> value) { unReciver = value; }

DataQueueItem AbstractRequester::getFirstMsg() const { return firstMsg; }
void AbstractRequester::setFirstMsg(const DataQueueItem &value) {firstMsg = value;}

DataQueueItem AbstractRequester::getSecondMsg() const { return secondMsg; }
void AbstractRequester::setSecondMsg(const DataQueueItem &value) { secondMsg = value; }

DataQueueItem AbstractRequester::getEndMsg() const { return endMsg; }
void AbstractRequester::setEndMsg(const DataQueueItem &value) { endMsg = value; }

QPair<QString, QString> AbstractRequester::getIpPort() const { return ipPort; }
void AbstractRequester::setIpPort(const QPair<QString, QString> &value) { ipPort = value; }

int AbstractRequester::getPortIndex() const { return portIndex; }
void AbstractRequester::setPortIndex(int value) { portIndex = value; }

int AbstractRequester::getTimeIntervalRequest() const { return timeIntervalRequest; }
void AbstractRequester::setTimeIntervalRequest(int value) { timeIntervalRequest = value; }

int AbstractRequester::getTimeIntervalWaiteFirst() const { return timeIntervalWaiteFirst; }
void AbstractRequester::setTimeIntervalWaiteFirst(int value) { timeIntervalWaiteFirst = value; }

AbstractPort * AbstractRequester::getPtrPort() const { return ptrPort; }
void AbstractRequester::setPtrPort(AbstractPort *value) { ptrPort = value; }

int AbstractRequester::getBeatCount() const { return beatCount; }
void AbstractRequester::setBeatCount(int value) { beatCount = value; }
void AbstractRequester::resetBeatCount() { setBeatCount(0); }

int AbstractRequester::getMaxBeatCount() const { return maxBeatCount; }
void AbstractRequester::setMaxBeatCount(int value) { maxBeatCount = value; }

RequesterType AbstractRequester::getRequesterType() const {
    return requesterType;
}

void AbstractRequester::setRequesterType(const RequesterType &value) {
    requesterType = value;
}
int AbstractRequester::getTimeIntervalWaiteSecond() const { return timeIntervalWaiteSecond; }
void AbstractRequester::setTimeIntervalWaiteSecond(int value) { timeIntervalWaiteSecond = value; }

void AbstractRequester::specialReserveSlot() const {return;};
