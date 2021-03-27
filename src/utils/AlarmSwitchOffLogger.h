#ifndef ALARMSWITCHOFFLOGGER_H
#define ALARMSWITCHOFFLOGGER_H

#include <QThread>

class AlarmSwitchOffLogger : public QThread
{
    Q_OBJECT
    bool runing = false;

public:
    AlarmSwitchOffLogger(QObject * parent = nullptr);
    virtual ~AlarmSwitchOffLogger();

    void run();

    bool isRuning() const;
    void setRuning(bool value);
};

#endif // ALARMSWITCHOFFLOGGER_H
