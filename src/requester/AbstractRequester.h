#ifndef ABSTRACTREQUESTER_H
#define ABSTRACTREQUESTER_H

#include "Utils.h"
#include <Port.h>
#include <DataQueueItem.h>
#include <QTimer>
#include <QDebug>
#include <UnitNode.h>


enum BeatStatus {
    Start = 0,
    Request = 1,
    Waite = 2,
    Unsuccessful = 3,
    RequestStep1 = 4,
    RequestStep2 = 5,
    WaiteEnd = 6,
    End = 7
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
    UnitNode * unTarget = nullptr;
    UnitNode * unReciver = nullptr;
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

    AbstractRequester(UnitNode * target, RequesterType requesterType = RequesterType::ConfirmWaiter) : QObject(target) {
//        qDebug() << "AbstractRequester::AbstractRequester(" << this << ") -->";
        setUnTarget(target);
        setRequesterType(requesterType);
//        qDebug() << "AbstractRequester::AbstractRequester(" << this << ") -- getRequesterType( " << getRequesterType() << " )";
        setBeatStatus(BeatStatus::Start);
//        qDebug() << "AbstractRequester::AbstractRequester(" << this << ") <--";
    }

    virtual ~AbstractRequester() {
//        qDebug() << "AbstractRequester::~AbstractRequester(" << this << ") -->";
        timerTripleStop();
//        qDebug() << "AbstractRequester::~AbstractRequester(" << this << ") <--";
    }

    virtual void init() = 0;

    bool isValid() {
//        qDebug() << "AbstractRequester::isValid(" << this << ") -->";
        bool result = true;

        result = result && (nullptr != getPtrPort());
//        qDebug() << "AbstractRequester::isValid(" << this << ") -- getPtrPort " << result;
        result = result && (nullptr != getUnTarget());
//        qDebug() << "AbstractRequester::isValid(" << this << ") -- getUnTarget " << result;
        result = result && (nullptr != getUnReciver());
//        qDebug() << "AbstractRequester::isValid(" << this << ") -- getUnReciver " << result;
        if(BeatStatus::Start != getBeatStatus()) {
            result = result && getFirstMsg().isValid();
//            qDebug() << "AbstractRequester::isValid(" << this << ") -- getFirstMsg " << result;
            result = result && (0 == getTimeIntervalWaiteFirst() || getSecondMsg().isValid());
//            qDebug() << "AbstractRequester::isValid(" << this << ") -- getSecondMsg " << result;
        }
//        qDebug() << "AbstractRequester::isValid(" << this << ") -- result " << result;
//    qDebug() << "AbstractRequester::isValid(" << this << ") <--";
        return result;
    }

    BeatStatus getBeatStatus() const {return beatStatus;}
    void setBeatStatus(const BeatStatus value) {beatStatus = value;}

    //Step#1 -->
private:
    QTimer * timerFirst = nullptr;
protected:
    void timerFirstStart(int interval = 1000) {
        if(nullptr == timerFirst)
            timerFirst = new QTimer;

        timerFirst->setInterval(interval);
        timerFirst->setSingleShot(true);
        timerFirst->connect(timerFirst, SIGNAL(timeout()), this, SLOT(beatRepeatFirstRequest()));
        timerFirst->start();
    }
    void timerFirstStop() {
        if(nullptr != timerFirst) {
            timerFirst->stop();
            delete timerFirst;
            timerFirst = nullptr;
        }
    }
    virtual DataQueueItem makeFirstMsg() = 0;
public slots:
    void startFirstRequest() {
//        qDebug() << "AbstractRequester::startFirstRequest(" << this << ") -->";
        timerTripleStop();
        resetBeatCount();
        setBeatStatus(BeatStatus::RequestStep1);
        beatRepeatFirstRequest();
//        qDebug() << "AbstractRequester::startFirstRequest(" << this << ") <--";
    }
    void beatRepeatFirstRequest() {
//        qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") -->";
        timerTripleStop();
        if(getMaxBeatCount() <= getBeatCount()) {
            timerTripleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") <-- Unsuccessful";
            return;
        }

        setFirstMsg(makeFirstMsg());

        if(!getFirstMsg().isValid()) {
            timerTripleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") <-- Unsuccessful";
            return;
        }

        Port::typeDefPort(getPtrPort())->write(getFirstMsg(), false);
        setBeatCount(getBeatCount() + 1);
        timerFirstStart(getTimeIntervalRequest());
//        qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") <--";
    }
    //Step#1 <--

    //Step#1->#2 -->
public slots:
    void startWaiteSecondRequest() {
//        qDebug() << "AbstractRequester::startWaiteSecondRequest(" << this << ") -->";
        timerTripleStop();

        if(0 == getTimeIntervalWaiteFirst()) {
            timerTripleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::startWaiteSecondRequest(" << this << ") <-- Unsuccessful";
            return;
        }

        setBeatStatus(BeatStatus::Waite);
        resetBeatCount();

        timerSecondStart(getTimeIntervalWaiteFirst());
//        qDebug() << "AbstractRequester::startWaiteSecondRequest(" << this << ") <--";
    }
    //Step#1->#2 <--

    //Step#2 -->
private:
    QTimer * timerSecond = nullptr;
protected:
    void timerSecondStart(int interval = 1000) {
        if(nullptr == timerSecond)
            timerSecond = new QTimer;

        timerSecond->setInterval(interval);
        timerSecond->setSingleShot(true);
        timerSecond->connect(timerSecond, SIGNAL(timeout()), this, SLOT(startSecondRequest()));
        timerSecond->start();
    }
    void timerSecondStop() {
        if(nullptr != timerSecond) {
            timerSecond->stop();
            delete timerSecond;
            timerSecond = nullptr;
        }
    }
    virtual DataQueueItem makeSecondMsg() = 0;
public slots:
    void startSecondRequest() {
//        qDebug() << "AbstractRequester::startSecondRequest(" << this << ") -->";
        timerTripleStop();
        resetBeatCount();
        setBeatStatus(BeatStatus::RequestStep2);
        beatRepeatSecondRequest();
//        qDebug() << "AbstractRequester::startSecondRequest(" << this << ") <--";
    }
    void beatRepeatSecondRequest() {
//        qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") -->";
        timerTripleStop();

        if(getMaxBeatCount() <= getBeatCount()) {
            timerTripleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") <-- Unsuccessful";
            return;
        }

        setSecondMsg(makeSecondMsg());

        if(!getSecondMsg().isValid()) {
            timerTripleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") <-- Unsuccessful";
            return;
        }

        Port::typeDefPort(ptrPort)->write(getSecondMsg(), false);
        setBeatCount(getBeatCount() + 1);
        timerSecondStart(getTimeIntervalRequest());
//        qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") <--";
    }
    //Step#2 <--

    //Step#2->#end -->
public slots:
    void startWaiteEndSecondWaite() {
//        qDebug() << "AbstractRequester::startWaiteEndSecondWaite(" << this << ") -->";
        timerTripleStop();

        if(0 == getTimeIntervalWaiteSecond()) {
            timerTripleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::startWaiteEndSecondWaite(" << this << ") <-- Unsuccessful";
            return;
        }

        setBeatStatus(BeatStatus::WaiteEnd);
        resetBeatCount();

        timerEndStart(getTimeIntervalWaiteSecond());
//        qDebug() << "AbstractRequester::startWaiteEndSecondWaite(" << this << ") <--";
    }
    //Step#2->#end <--

    //Step#end -->
private:
    QTimer * timerEnd = nullptr;
protected:
    void timerEndStart(int interval = 1000) {
        if(nullptr == timerEnd)
            timerEnd = new QTimer;

        timerEnd->setInterval(interval);
        timerEnd->setSingleShot(true);
        timerEnd->connect(timerEnd, SIGNAL(timeout()), this, SLOT(startEnd()));
        timerEnd->start();
    }
    void timerEndStop() {
        if(nullptr != timerEnd) {
            timerEnd->stop();
            delete timerEnd;
            timerEnd = nullptr;
        }
    }
    virtual DataQueueItem makeEndMsg() = 0;
public slots:
    void startEnd() {
//        qDebug() << "AbstractRequester::startSecondRequest(" << this << ") -->";
        timerTripleStop();
        resetBeatCount();
        setBeatStatus(BeatStatus::RequestStep2);
        beatRepeatSecondRequest();
//        qDebug() << "AbstractRequester::startSecondRequest(" << this << ") <--";
    }
    void beatRepeatEnd() {
//        qDebug() << "AbstractRequester::beatRepeatEnd(" << this << ") -->";
        timerTripleStop();

        if(getMaxBeatCount() <= getBeatCount()) {
            timerTripleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::beatRepeatEnd(" << this << ") <-- Unsuccessful";
            return;
        }

        setEndMsg(makeEndMsg());

        if(!getEndMsg().isValid()) {
            timerTripleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::beatRepeatEnd(" << this << ") <-- Unsuccessful";
            return;
        }

        Port::typeDefPort(ptrPort)->write(getEndMsg(), false);
        setBeatCount(getBeatCount() + 1);
        timerEndStart(getTimeIntervalRequest());
//        qDebug() << "AbstractRequester::beatRepeatEnd(" << this << ") <--";
    }
    //Step#end <--

public:
    UnitNode * getUnTarget() const { return unTarget; }
    void setUnTarget(UnitNode *value) { unTarget = value; }

    UnitNode *getUnReciver() const  { return unReciver; }
    void setUnReciver(UnitNode *value) { unReciver = value; }

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
    void unsuccessful();

private slots:
    virtual void specialReserveSlot() const {return;};
};

#endif // ABSTRACTREQUESTER_H
