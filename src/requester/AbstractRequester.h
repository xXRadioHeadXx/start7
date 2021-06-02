#ifndef ABSTRACTREQUESTER_H
#define ABSTRACTREQUESTER_H

#include "Utils.h"
#include "Port.h"
#include "DataQueueItem.h"
#include <QTimer>
//#include <QDebug>
#include "UnitNode.h"


enum BeatStatus {
    Start = 0,
    Request = 1,
    Waite = 2,
    Unsuccessful = 3,
    RequestStep1 = 4,
    RequestStep2 = 5,
    WaiteEnd = 6,
    End = 7,
    Successful = 8
};

enum RequesterType {
    DKWaiter = 0,
    AutoOnOffWaiter = 1,
    ConfirmWaiter = 2,
    ConnectRequester = 3,
    LockRequester = 4
};


class AbstractRequester : public QObject
{
    Q_OBJECT
private:
    RequesterType requesterType = RequesterType::ConfirmWaiter;
    BeatStatus beatStatus = BeatStatus::Start;
    QSharedPointer<UnitNode> unTarget = nullptr;
    QSharedPointer<UnitNode> unReciver = nullptr;
    DataQueueItem firstMsg;
    DataQueueItem secondMsg;
    DataQueueItem endMsg;
    QPair<QString, QString> ipPort;
    int portIndex = -1;
    int timeIntervalRequest = 1000;
    int timeIntervalWaiteFirst = 0;
    int timeIntervalWaiteSecond = 0;
    AbstractPort * ptrPort = nullptr;

    int beatCount = 0;
    int maxBeatCount = 3;

public:

    void timerTripleStop() {
        timerFirstStop();
        timerSecondStop();
        timerEndStop();
    }

    AbstractRequester(QSharedPointer<UnitNode> target, RequesterType requesterType = RequesterType::ConfirmWaiter) : QObject(target.data()) {
//        //qDebug() << "AbstractRequester::AbstractRequester(" << this << ") -->";
        setUnTarget(target);
        setRequesterType(requesterType);
//        //qDebug() << "AbstractRequester::AbstractRequester(" << this << ") -- getRequesterType( " << getRequesterType() << " )";
        setBeatStatus(BeatStatus::Start);
//        //qDebug() << "AbstractRequester::AbstractRequester(" << this << ") <--";
    }

    virtual ~AbstractRequester() {
//        //qDebug() << "AbstractRequester::~AbstractRequester(" << this << ") -->";
        timerTripleStop();
        ptrPort = nullptr;
//        //qDebug() << "AbstractRequester::~AbstractRequester(" << this << ") <--";
    }

    virtual void init() = 0;

    bool isValid() {
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

    BeatStatus getBeatStatus() const {return beatStatus;}
    void setBeatStatus(const BeatStatus value) {beatStatus = value;}

    //Step#1 -->
private:
    QSharedPointer<QTimer> timerFirst;
protected:
    void timerFirstStart(int interval = 1000) {
        if(timerFirst.isNull()) {
            timerFirst = QSharedPointer<QTimer>::create();
        }
        timerFirst->setInterval(interval);
        timerFirst->setSingleShot(true);
        timerFirst->connect(timerFirst.data(), SIGNAL(timeout()), this, SLOT(beatRepeatFirstRequest()));
        timerFirst->start();
    }
    void timerFirstStop() {
        if(!timerFirst.isNull()) {
            timerFirst->stop();
            timerFirst.clear();
        }
    }
    virtual DataQueueItem makeFirstMsg() = 0;
public slots:
    void startFirstRequest(int delay = 0) {
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
    void beatRepeatFirstRequest() {
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
public slots:
    void startWaiteSecondRequest() {
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
private:
    QSharedPointer<QTimer> timerSecond;;
protected:
    void timerSecondStart(int interval = 1000) {
        if(timerSecond.isNull()) {
            timerSecond = QSharedPointer<QTimer>::create();
        }
        timerSecond->setInterval(interval);
        timerSecond->setSingleShot(true);
        timerSecond->connect(timerSecond.data(), SIGNAL(timeout()), this, SLOT(startSecondRequest()));
        timerSecond->start();
    }
    void timerSecondStop() {
        if(!timerSecond.isNull()) {
            timerSecond->stop();
            timerSecond.clear();
        }
    }
    virtual DataQueueItem makeSecondMsg() = 0;
public slots:
    void startSecondRequest(int delay = 0) {
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
    void beatRepeatSecondRequest() {
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
public slots:
    void startWaiteEndSecondWaite() {
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
private:
    QSharedPointer<QTimer> timerEnd;
protected:
    void timerEndStart(int interval = 1000) {
        if(timerEnd.isNull()) {
            timerEnd = QSharedPointer<QTimer>::create();
        }
        timerEnd->setInterval(interval);
        timerEnd->setSingleShot(true);
        timerEnd->connect(timerEnd.data(), SIGNAL(timeout()), this, SLOT(startEnd()));
        timerEnd->start();
    }
    void timerEndStop() {
        if(!timerEnd.isNull()) {
            timerEnd->stop();
            timerEnd.clear();
        }
    }
    virtual DataQueueItem makeEndMsg() = 0;
public slots:
    void startEnd(int delay = 0) {
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
    void beatRepeatEnd() {
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

public:
    QSharedPointer<UnitNode> getUnTarget() const { return unTarget; }
    void setUnTarget(QSharedPointer<UnitNode> value) { unTarget = value; }

    QSharedPointer<UnitNode> getUnReciver() const  { return unReciver; }
    void setUnReciver(QSharedPointer<UnitNode> value) { unReciver = value; }

    DataQueueItem getFirstMsg() const { return firstMsg; }
    void setFirstMsg(const DataQueueItem &value) {firstMsg = value;}

    DataQueueItem getSecondMsg() const { return secondMsg; }
    void setSecondMsg(const DataQueueItem &value) { secondMsg = value; }

    DataQueueItem getEndMsg() const { return endMsg; }
    void setEndMsg(const DataQueueItem &value) { endMsg = value; }

    QPair<QString, QString> getIpPort() const { return ipPort; }
    void setIpPort(const QPair<QString, QString> &value) { ipPort = value; }

    int getPortIndex() const { return portIndex; }
    void setPortIndex(int value) { portIndex = value; }

    int getTimeIntervalRequest() const { return timeIntervalRequest; }
    void setTimeIntervalRequest(int value) { timeIntervalRequest = value; }

    int getTimeIntervalWaiteFirst() const { return timeIntervalWaiteFirst; }
    void setTimeIntervalWaiteFirst(int value) { timeIntervalWaiteFirst = value; }

    AbstractPort *getPtrPort() const { return ptrPort; }
    void setPtrPort(AbstractPort *value) { ptrPort = value; }

    int getBeatCount() const { return beatCount; }
    void setBeatCount(int value) { beatCount = value; }
    void resetBeatCount() { setBeatCount(0); }

    int getMaxBeatCount() const { return maxBeatCount; }
    void setMaxBeatCount(int value) { maxBeatCount = value; }

    RequesterType getRequesterType() const {
        return requesterType;
    }

    void setRequesterType(const RequesterType &value) {
        requesterType = value;
    }
    int getTimeIntervalWaiteSecond() const { return timeIntervalWaiteSecond; }
    void setTimeIntervalWaiteSecond(int value) { timeIntervalWaiteSecond = value; }


signals:
    void importantBeatStatus();
    void successful();
    void unsuccessful();


private slots:
    virtual void specialReserveSlot() const {return;};
};

#endif // ABSTRACTREQUESTER_H
