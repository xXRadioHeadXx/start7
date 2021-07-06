#ifndef SOUNDADJUSTER_H
#define SOUNDADJUSTER_H

#include <QObject>
#include "template/SingletonTemplate.h"
#include "QSound"

class SoundAdjuster : public QObject, public SingletonTemplate<SoundAdjuster>
{
    Q_OBJECT
    static QSound soundAlarm;
    static QSound soundAlarm2;
    static QSound soundRingin;
    static QSound soundRingout;
protected:
//    explicit SoundAdjuster() {}
public:
    virtual ~SoundAdjuster() {}

    void init();

public slots:
    void playAlarm(const int loops = QSound::Infinite);
    void playAlarmOneTime();
    void playAlarm2(const int loops = QSound::Infinite);
    void playAlarm2OneTime();
    void playRingin(const int loops = QSound::Infinite);
    void playRinginOneTime();
    void playRingout(const int loops = QSound::Infinite);
    void playRingoutOneTime();
    void stop();
signals:

};

#endif // SOUNDADJUSTER_H
