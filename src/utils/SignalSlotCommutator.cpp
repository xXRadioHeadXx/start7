#include <SignalSlotCommutator.h>
#include <QDebug>

SignalSlotCommutator * SignalSlotCommutator::instance = nullptr;

SignalSlotCommutator * SignalSlotCommutator::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SignalSlotCommutator();
    }

    return instance;
}

SignalSlotCommutator::SignalSlotCommutator(QObject *parent) : QObject(parent)
{
    //qDebug() << "SignalSlotCommutator::SignalSlotCommutator(" << parent << ") -- first call";
}

void SignalSlotCommutator::emitInsNewCommandMSG(const quint32 id) const {
    emit this->insNewCommandMSG(id);
}

void SignalSlotCommutator::emitInsNewCommandMSG() const {
    emit this->insNewCommandMSG();
}

void SignalSlotCommutator::emitInsNewJourMSG(const quint32 id) const {
    emit this->insNewJourMSG(id);
}

void SignalSlotCommutator::emitInsNewJourMSG() const {
    emit this->insNewJourMSG();
}

void SignalSlotCommutator::emitUpdAllJourMSG() const
{
    emit this->updAllJourMSG();
}

void SignalSlotCommutator::emitUpdJourMSG(const quint32 id) const {
    emit this->updJourMSG(id);
}

void SignalSlotCommutator::emitUpdJourMSG() const {
    emit this->updJourMSG();
}

void SignalSlotCommutator::emitUpdUN() const
{
    emit this->updUN();
}

void SignalSlotCommutator::emitUpdDataTreeUN() const
{
    emit this->updDataTreeUN();
}

void SignalSlotCommutator::emitStartDKWait(int interval) const
{
    emit this->startDKWait(interval);
}

void SignalSlotCommutator::emitStopDKWait() const
{
    emit this->stopDKWait();
}

void SignalSlotCommutator::emitEndDKWait() const
{
    emit this->endDKWait();
}

void SignalSlotCommutator::emitStartLockWait(int interval) const
{
    emit this->startLockWait(interval);
}

void SignalSlotCommutator::emitStopLockWait() const
{
    emit this->stopLockWait();
}

void SignalSlotCommutator::emitEndLockWait() const
{
    emit this->endLockWait();
}

void SignalSlotCommutator::emitAutoOnOffIU(bool out, QSharedPointer<UnitNode>  un) const
{
    emit this->autoOnOffIU(out , un);
}

void SignalSlotCommutator::emitAutoOnOffIU(QSharedPointer<UnitNode>  un) const
{
    emit this->autoOnOffIU(false, un);
}

void SignalSlotCommutator::emitLostedConnect(QSharedPointer<UnitNode>  un) const
{
    emit this->lostConnect(un);
}

void SignalSlotCommutator::emitRequestOnOffCommand(QSharedPointer<UnitNode>  un, bool value) const
{
    emit this->requestOnOffCommand(false, un, value);
}

void SignalSlotCommutator::emitRequestOnOffCommand(bool out, QSharedPointer<UnitNode>  un, bool value) const
{
    emit this->requestOnOffCommand(out, un, value);
}

void SignalSlotCommutator::emitLockOpenCloseCommand(bool out, QSharedPointer<UnitNode>  un, bool value) const
{
    emit this->lockOpenCloseCommand(out, un, value);
}

void SignalSlotCommutator::emitLockOpenCloseCommand(QSharedPointer<UnitNode>  un, bool value) const
{
    emit this->lockOpenCloseCommand(false, un, value);
}

void SignalSlotCommutator::emitChangeSelectUN(QSharedPointer<UnitNode>  un) const
{
    emit this->changeSelectUN(un);
}

void SignalSlotCommutator::emitRequestDK(QSharedPointer<UnitNode>  un) const
{
    emit this->requestDK(un);
}

void SignalSlotCommutator::emitRequestDK(bool out, QSharedPointer<UnitNode> un) const
{
    emit this->requestDK(out, un);
}

void SignalSlotCommutator::emitForcedNewDuty(bool out) const
{
    emit this->forcedNewDuty(out);
}

void SignalSlotCommutator::emitAlarmsReset(QSharedPointer<UnitNode> un) const
{
    emit this->alarmsReset(un);
}

void SignalSlotCommutator::emitUpdateLabelOperator() const
{
    emit this->updateLabelOperator();
}
