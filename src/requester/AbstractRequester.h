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
    RequestStep2 = 5
};

enum RequesterType {
    DKWaiter = 0,
    AutoOnOffWaiter = 1,
    ConfirmWaiter = 2,
    ConnectRequester = 3
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
    DataQueueItem SecondMsg;
    QPair<QString, QString> ipPort;
    int portIndex = -1;
    int timeIntervalRequest = 1000;
    int timeIntervalWaite = 0;
    AbstractPort * ptrPort = nullptr;

    int beatCount = 0;
    int maxBeatCount = 3;

    void timerDoubleStop() {
        timerFirstStop();
        timerSecondStop();
    }

public:

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
        timerDoubleStop();
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
            result = result && (0 == getTimeIntervalWaite() || getSecondMsg().isValid());
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
        timerDoubleStop();
        resetBeatCount();
        setBeatStatus(BeatStatus::RequestStep1);
        beatRepeatFirstRequest();
//        qDebug() << "AbstractRequester::startFirstRequest(" << this << ") <--";
    }
    void beatRepeatFirstRequest() {
//        qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") -->";
        timerDoubleStop();
        if(getMaxBeatCount() <= getBeatCount()) {
            timerDoubleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::beatRepeatFirstRequest(" << this << ") <-- Unsuccessful";
            return;
        }

        setFirstMsg(makeFirstMsg());

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
        timerDoubleStop();

        if(0 == getTimeIntervalWaite()) {
            timerDoubleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::startWaiteSecondRequest(" << this << ") <-- Unsuccessful";
            return;
        }

        setBeatStatus(BeatStatus::Waite);
        resetBeatCount();

        timerSecondStart(getTimeIntervalWaite());
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
        timerDoubleStop();
        resetBeatCount();
        setBeatStatus(BeatStatus::RequestStep2);
        beatRepeatSecondRequest();
//        qDebug() << "AbstractRequester::startSecondRequest(" << this << ") <--";
    }
    void beatRepeatSecondRequest() {
//        qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") -->";
        timerDoubleStop();

        if(getMaxBeatCount() <= getBeatCount()) {
            timerDoubleStop();
            setBeatStatus(BeatStatus::Unsuccessful);
            emit unsuccessful();
//            qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") <-- Unsuccessful";
            return;
        }

        setSecondMsg(makeSecondMsg());

        Port::typeDefPort(ptrPort)->write(getSecondMsg(), false);
        setBeatCount(getBeatCount() + 1);
        timerSecondStart(getTimeIntervalRequest());
//        qDebug() << "AbstractRequester::beatRepeatSecondRequest(" << this << ") <--";
    }
    //Step#2 <--

public:
    UnitNode * getUnTarget() const { return unTarget; }
    void setUnTarget(UnitNode *value) { unTarget = value; }

    UnitNode *getUnReciver() const  { return unReciver; }
    void setUnReciver(UnitNode *value) { unReciver = value; }

    DataQueueItem getFirstMsg() const { return firstMsg; }
    void setFirstMsg(const DataQueueItem &value) {firstMsg = value;}

    DataQueueItem getSecondMsg() const { return SecondMsg; }
    void setSecondMsg(const DataQueueItem &value) { SecondMsg = value; }

    QPair<QString, QString> getIpPort() const { return ipPort; }
    void setIpPort(const QPair<QString, QString> &value) { ipPort = value; }

    int getPortIndex() const { return portIndex; }
    void setPortIndex(int value) { portIndex = value; }

    int getTimeIntervalRequest() const { return timeIntervalRequest; }
    void setTimeIntervalRequest(int value) { timeIntervalRequest = value; }

    int getTimeIntervalWaite() const { return timeIntervalWaite; }
    void setTimeIntervalWaite(int value) { timeIntervalWaite = value; }

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
signals:
    void unsuccessful();
};

#endif // ABSTRACTREQUESTER_H


