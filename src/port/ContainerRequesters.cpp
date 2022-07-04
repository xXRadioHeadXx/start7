#include "../src/port/ContainerRequesters.h"
#include "../src/requester/AbstractRequester.h"

ContainerRequesters::ContainerRequesters()
{

}

QList<QSharedPointer<AbstractRequester> > ContainerRequesters::lsSCR = QList<QSharedPointer<AbstractRequester> >();

QList<QSharedPointer<AbstractRequester> > ContainerRequesters::lsWaiter = QList<QSharedPointer<AbstractRequester> >();


QList<QSharedPointer<AbstractRequester> > ContainerRequesters::getLsSCR()
{
    return lsSCR;
}

void ContainerRequesters::setLsSCR(const QList<QSharedPointer<AbstractRequester> > &value)
{
    lsSCR = value;
}

void ContainerRequesters::appLsSCR(QSharedPointer<AbstractRequester> value) {
    if(value.isNull())
        return;

    if(value->isValid())
        lsSCR.append(value);
}

void ContainerRequesters::prependLsSCR(QSharedPointer<AbstractRequester> value) {
    if(value.isNull())
        return;

    if(value->isValid())
        lsSCR.prepend(value);
}


void ContainerRequesters::removeLsSCR(QSharedPointer<AbstractRequester> value) {

    value->timerTripleStop();
    lsSCR.removeAll(value);
    value->setBeatStatus(BeatStatus::Unsuccessful);
}

void ContainerRequesters::clearLsSCR()
{
    for(int i = 0, n = lsSCR.size(); i < n; i++) {
        QSharedPointer<AbstractRequester>  value = lsSCR.at(i);
        value->timerTripleStop();
        value->setBeatStatus(BeatStatus::Unsuccessful);
    }
    lsSCR.clear();
}

QList<QSharedPointer<AbstractRequester> > ContainerRequesters::getLsWaiter()
{
    return lsWaiter;
}

void ContainerRequesters::setLsWaiter(const QList<QSharedPointer<AbstractRequester> > &value)
{
    lsWaiter = value;
}

void ContainerRequesters::appLsWaiter(QSharedPointer<AbstractRequester> value) {
    if(value.isNull())
        return;

    if(value->isValid())
        lsWaiter.append(value);
}

void ContainerRequesters::prependLsWaiter(QSharedPointer<AbstractRequester> value) {
    if(value.isNull())
        return;

    if(value->isValid())
        lsWaiter.prepend(value);
}


void ContainerRequesters::removeLsWaiter(QSharedPointer<AbstractRequester> value) {

    value->timerTripleStop();
    lsWaiter.removeAll(value);
    value->setBeatStatus(BeatStatus::Unsuccessful);
}

void ContainerRequesters::clearLsWaiter()
{
    for(int i = 0, n = lsWaiter.size(); i < n; i++) {
        QSharedPointer<AbstractRequester> value = lsWaiter.at(i);
        value->timerTripleStop();
        value->setBeatStatus(BeatStatus::Unsuccessful);
    }
    lsWaiter.clear();
}
