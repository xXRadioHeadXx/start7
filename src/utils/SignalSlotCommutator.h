#ifndef SIGNALSLOTCOMMUTATOR_H
#define SIGNALSLOTCOMMUTATOR_H

#include <QObject>

class UnitNode;
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
     void emitStartLockWait(int interval) const;
     void emitStopLockWait() const;
     void emitEndLockWait() const;
     void emitAutoOnOffIU(bool, QSharedPointer<UnitNode> ) const;
     void emitAutoOnOffIU(QSharedPointer<UnitNode> ) const;
     void emitLostedConnect(QSharedPointer<UnitNode> ) const;
     void emitRequestOnOffCommand(bool, QSharedPointer<UnitNode> , bool) const;
     void emitRequestOnOffCommand(QSharedPointer<UnitNode> , bool) const;
     void emitLockOpenCloseCommand(bool, QSharedPointer<UnitNode> , bool) const;
     void emitLockOpenCloseCommand(QSharedPointer<UnitNode> , bool) const;
     void emitChangeSelectUN (QSharedPointer<UnitNode> ) const;
     void emitRequestDK (QSharedPointer<UnitNode> ) const;
     void emitRequestDK (bool, QSharedPointer<UnitNode>  un) const;
     void emitForcedNewDuty(bool out) const;
     void emitAlarmsReset(QSharedPointer<UnitNode>  un) const;
     void emitUpdateLabelOperator() const;
     void emitChangeCountIntegrationAbonent(int) const;

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
     void startLockWait(int interval) const;
     void stopLockWait() const;
     void endLockWait() const;
     void autoOnOffIU(QSharedPointer<UnitNode> ) const;
     void autoOnOffIU(bool, QSharedPointer<UnitNode> ) const;
     void lostConnect(QSharedPointer<UnitNode> ) const;
     void requestOnOffCommand(bool, QSharedPointer<UnitNode> , bool) const;
     void lockOpenCloseCommand(bool, QSharedPointer<UnitNode> , bool) const;
     void changeSelectUN (QSharedPointer<UnitNode> ) const;
     void requestDK (QSharedPointer<UnitNode> ) const;
     void requestDK (bool, QSharedPointer<UnitNode> ) const;
     void forcedNewDuty(bool out) const;
     void alarmsReset(QSharedPointer<UnitNode>  un) const;
     void updateLabelOperator() const;
     void changeCountIntegrationAbonent(int) const;

};

#endif // SIGNALSLOTCOMMUTATOR_H
