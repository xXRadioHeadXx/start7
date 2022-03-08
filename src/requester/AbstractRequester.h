#ifndef ABSTRACTREQUESTER_H
#define ABSTRACTREQUESTER_H

#include "Port.h"
//#include <QDebug>

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

class DataQueueItem;
class UnitNode;
class QTimer;
class AbstractPort;
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

    QSharedPointer<ManagerSingleMsg> managerFirstMsg;
    QSharedPointer<ManagerSingleMsg> managerSecondMsg;
    QSharedPointer<ManagerSingleMsg> managerEndMsg;


    QPair<QString, QString> ipPort;
    int portIndex = -1;
    int timeIntervalRequest = 1'000;
    int timeIntervalWaiteFirst = 0;
    int timeIntervalWaiteSecond = 0;
    int timeIntervalPauseFromFirstToSecond = 0;
    int timeIntervalPauseFromSecondToEnd = 0;

    AbstractPort * ptrPort = nullptr;

    int beatCount = 0;
    int maxBeatCount = 3;

    QTime lastPushTime;
protected:
    std::function<void()> updateStateConditionReactor;

public:

    void timerTripleStop();

    AbstractRequester(QSharedPointer<UnitNode> target, RequesterType requesterType = RequesterType::ConfirmWaiter);

    virtual ~AbstractRequester();

    virtual void init() = 0;

    bool isValid();

    BeatStatus getBeatStatus() const;
    void setBeatStatus(const BeatStatus value);

    //Step#1 -->
private:
    QSharedPointer<QTimer> timerFirst;
protected:
    void timerFirstStart(int interval = 1'000);
    void timerFirstStop();
    virtual DataQueueItem makeFirstMsg() = 0;
public slots:
    void startFirstRequest(int delay = 0);
    void beatRepeatFirstRequest() {
        aspectBeforeFirstRequest();
        firstRequest();
        aspectAfterFirstRequest();
    }

public:
    virtual void aspectBeforeFirstRequest() {};
private:
    void firstRequest();
public:
    virtual void aspectAfterFirstRequest() {};
    //Step#1 <--

    //Step#1->#2 -->
public slots:
    void startWaiteSecondRequest();
    //Step#1->#2 <--

    //Step#2 -->
private:
    QSharedPointer<QTimer> timerSecond;;
protected:
    void timerSecondStart(int interval = 1'000);
    void timerSecondStop();
    virtual DataQueueItem makeSecondMsg() = 0;
public slots:
    void startSecondRequest(int delay = 0);
    void beatRepeatSecondRequest() {
        aspectBeforeSecondRequest();
        secondRequest();
        aspectAfterSecondRequest();
    }
public:
    virtual void aspectBeforeSecondRequest() {};
private:
    void secondRequest();
public:
    virtual void aspectAfterSecondRequest() {};
    //Step#2 <--

    //Step#2->#end -->
public slots:
    void startWaiteEndSecondWaite();
    //Step#2->#end <--

    //Step#end -->
private:
    QSharedPointer<QTimer> timerEnd;
protected:
    void timerEndStart(int interval = 1'000);
    void timerEndStop();
    virtual DataQueueItem makeEndMsg() = 0;
public slots:
    void startEnd(int delay = 0);
    void beatRepeatEnd() {
        aspectBeforeEndRequest();
        endRequest();
        aspectAfterEndRequest();
    }
public:
    virtual void aspectBeforeEndRequest() {};
private:
    void endRequest();
public:
    virtual void aspectAfterEndRequest() {};
    //Step#end <--

public:
    QSharedPointer<UnitNode> getUnTarget() const;
    void setUnTarget(QSharedPointer<UnitNode> value);

    QSharedPointer<UnitNode> getUnReciver() const;
    void setUnReciver(QSharedPointer<UnitNode> value);

    DataQueueItem getFirstMsg() const;
    void setFirstMsg(const DataQueueItem &value);

    DataQueueItem getSecondMsg() const;
    void setSecondMsg(const DataQueueItem &value);

    DataQueueItem getEndMsg() const;
    void setEndMsg(const DataQueueItem &value);

    QSharedPointer<ManagerSingleMsg> getManagerFirstMsg() const;
    void setManagerFirstMsg(const QSharedPointer<ManagerSingleMsg> &value);

    QSharedPointer<ManagerSingleMsg> getManagerSecondMsg() const;
    void setManagerSecondMsg(const QSharedPointer<ManagerSingleMsg> &value);

    QSharedPointer<ManagerSingleMsg> getManagerEndMsg() const;
    void setManagerEndMsg(const QSharedPointer<ManagerSingleMsg> &value);

    QPair<QString, QString> getIpPort() const;
    void setIpPort(const QPair<QString, QString> &value);

    int getPortIndex() const;
    void setPortIndex(int value);

    int getTimeIntervalRequest() const;
    void setTimeIntervalRequest(int value);

    int getTimeIntervalWaiteFirst() const;
    void setTimeIntervalWaiteFirst(int value);

    AbstractPort *getPtrPort() const;
    void setPtrPort(AbstractPort *value);

    int getBeatCount() const;
    void setBeatCount(int value);
    void resetBeatCount();

    int getMaxBeatCount() const;
    void setMaxBeatCount(int value);

    RequesterType getRequesterType() const;

    void setRequesterType(const RequesterType &value);
    int getTimeIntervalWaiteSecond() const;
    void setTimeIntervalWaiteSecond(int value);


    QTime getLastPushTime() const;
    QTime updLastPushTime();

    int getTimeIntervalPauseFromFirstToSecond() const;
    void setTimeIntervalPauseFromFirstToSecond(int value);

    int getTimeIntervalPauseFromSecondToEnd() const;
    void setTimeIntervalPauseFromSecondToEnd(int value);

    const std::function<void()> &getUpdateStateConditionReactor() const;
    void setUpdateStateConditionReactor(const std::function<void()> &newUpdateStateConditionReactor);

signals:
    void importantBeatStatus();
    void successful();
    void unsuccessful();


private slots:
    virtual void specialReserveSlot() const;
};

#endif // ABSTRACTREQUESTER_H
