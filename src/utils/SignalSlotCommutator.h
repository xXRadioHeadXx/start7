#ifndef SIGNALSLOTCOMMUTATOR_H
#define SIGNALSLOTCOMMUTATOR_H

#include <QObject>
#include <UnitNode.h>

class SignalSlotCommutator : public QObject
{
    Q_OBJECT
public:
    static SignalSlotCommutator * getInstance();
private:
     static SignalSlotCommutator * instance;
     explicit SignalSlotCommutator(QObject *parent = nullptr);

public slots:
     void emitInsNewCommandMSG(const quint32 id) const;
     void emitInsNewCommandMSG() const;
     void emitInsNewJourMSG(const quint32 id) const;
     void emitInsNewJourMSG() const;
     void emitUpdAllJourMSG() const;
     void emitUpdJourMSG(const quint32 id) const;
     void emitUpdJourMSG() const;
     void emitUpdUN() const;
     void emitUpdDataTreeUN() const;
     void emitStartDKWait(int interval) const;
     void emitStopDKWait() const;
     void emitEndDKWait() const;
     void emitAutoOnOffIU(UnitNode *) const;
     void emitLostedConnect(UnitNode *) const;

signals:
     void insNewCommandMSG(const quint32 id) const;
     void insNewCommandMSG() const;
     void insNewJourMSG(const quint32 id) const;
     void insNewJourMSG() const;
     void updAllJourMSG() const;
     void updJourMSG(const quint32 id) const;
     void updJourMSG() const;
     void updUN() const;
     void updDataTreeUN() const;
     void startDKWait(int interval) const;
     void stopDKWait() const;
     void endDKWait() const;
     void autoOnOffIU(UnitNode *) const;
     void lostConnect(UnitNode *) const;

};

#endif // SIGNALSLOTCOMMUTATOR_H
