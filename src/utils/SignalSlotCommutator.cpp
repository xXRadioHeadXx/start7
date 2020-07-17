#include <SignalSlotCommutator.h>

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

void SignalSlotCommutator::emitAutoOnOffIU(UnitNode * un) const
{
    emit this->autoOnOffIU(un);
}
