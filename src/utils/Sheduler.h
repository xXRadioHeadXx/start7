#ifndef SHEDULER_H
#define SHEDULER_H

#include <QObject>
#include <QTime>
#include <QTimer>

class Sheduler : public QObject
{
    Q_OBJECT

    QTimer timer;
    QTime runTime;

//    virtual void firstRun() const = 0;
private:
    virtual void regularRun() const = 0;

public:
    Sheduler(const QTime time);


public slots:
    void start() const;
    void stop();

private slots:
//    void firstRunSlot() const;
    void regularRunSlot() const;

};

#endif // SHEDULER_H
