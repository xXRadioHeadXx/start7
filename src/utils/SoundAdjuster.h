#ifndef SOUNDADJUSTER_H
#define SOUNDADJUSTER_H

#include <QObject>
#include <QSharedPointer>
#include "template/SingletonTemplate.h"
#include "QSound"

class SoundAdjuster : public QObject, public SingletonTemplate<SoundAdjuster>
{
    Q_OBJECT
    QSharedPointer<QSound> soundAlarm;
    QSharedPointer<QSound> soundAlarm2;
    QSharedPointer<QSound> soundRingin;
    QSharedPointer<QSound> soundRingout;

public:
    virtual ~SoundAdjuster() {}

    static void init();

public slots:
    static void playAlarm(const int loops = QSound::Infinite);
    static void playAlarmOneTime();
    static void playAlarm2(const int loops = QSound::Infinite);
    static void playAlarm2OneTime();
    static void playRingin(const int loops = QSound::Infinite);
    static void playRinginOneTime();
    static void playRingout(const int loops = QSound::Infinite);
    static void playRingoutOneTime();
    static void stop();
signals:

};

#endif // SOUNDADJUSTER_H
