#ifndef STATUSREQUESTER_H
#define STATUSREQUESTER_H

#include "AbstractRequester.h"

#include <QObject>
#include <Utils.h>

class StatusRequester : public QObject//, public AbstractRequester
{
    Q_OBJECT
private:
    BeatStatus beatStatus = BeatStatus::Start;
public:
    BeatStatus getBeatStatus() const {return beatStatus;}
    void setBeatStatus(const BeatStatus value) {beatStatus = value;}
public:
    QTimer timerStatusRequest;
    UnitNode * unStatusRequest = nullptr;
    const QByteArray msg = Utils::makeStatusRequest0x22();
    QPair<QString, QString> ipPort;
    int portIndex;
    int timeIntervalStatusRequest = 100;
    AbstractPort * ptrPort = nullptr;

    int beatCount = 0;
    int maxBeatCount = 20;

public:
    explicit StatusRequester(QObject * parent = nullptr);
    virtual ~StatusRequester();

public slots:
    void startStatusRequest();
    void beatStatusRequest();
signals:

};

#endif // STATUSREQUESTER_H
