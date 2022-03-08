#ifndef CONTAINERREQUESTERS_H
#define CONTAINERREQUESTERS_H

#include <QSharedPointer>


class AbstractRequester;
class ContainerRequesters
{
    static QList<QSharedPointer<AbstractRequester> > lsSCR;
    static QList<QSharedPointer<AbstractRequester> > lsWaiter;

public:
    ContainerRequesters();

    static QList<QSharedPointer<AbstractRequester> > getLsSCR();
    static void setLsSCR(const QList<QSharedPointer<AbstractRequester> > &value);
    static void appLsSCR(QSharedPointer<AbstractRequester> value);
    static void prependLsSCR(QSharedPointer<AbstractRequester> value);
    static void removeLsSCR(QSharedPointer<AbstractRequester> value);
    static void clearLsSCR();

    static QList<QSharedPointer<AbstractRequester> > getLsWaiter();
    static void setLsWaiter(const QList<QSharedPointer<AbstractRequester> > &value);
    static void appLsWaiter(QSharedPointer<AbstractRequester> value);
    static void prependLsWaiter(QSharedPointer<AbstractRequester> value);
    static void removeLsWaiter(QSharedPointer<AbstractRequester> value);
    static void clearLsWaiter();


};

#endif // CONTAINERREQUESTERS_H
