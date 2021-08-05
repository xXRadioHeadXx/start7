#ifndef INTERVALSHEDULER_H
#define INTERVALSHEDULER_H

#include <QObject>
#include <QTime>
#include <QTimer>

class IntervalSheduler : public QObject
{
    Q_OBJECT

    QTimer timer;
    const int runInterval;
    const double mean;


//    virtual void firstRun() const = 0;
private:
    virtual void regularRun() const = 0;

public:
    explicit IntervalSheduler(const QTime time, const double mean);

public slots:
    void start() const;
    void stop();

private slots:
//    void firstRunSlot() const;
    void regularRunSlot() const;

};

#endif // INTERVALSHEDULER_H
