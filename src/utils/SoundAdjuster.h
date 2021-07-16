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
