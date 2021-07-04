#ifndef SOUNDADJUSTER_H
#define SOUNDADJUSTER_H

#include <QObject>
#include "template/SingletonTemplate.h"
#include "QSound"

class SoundAdjuster : public QObject, public SingletonTemplate<SoundAdjuster>
{
    Q_OBJECT
    static QSound sound;
protected:
//    explicit SoundAdjuster() {}
public:
    virtual ~SoundAdjuster() {}

    void init();

public slots:
    void playAlarm();
    void playAlarmOneTime();
    void stop();
signals:

};

#endif // SOUNDADJUSTER_H
