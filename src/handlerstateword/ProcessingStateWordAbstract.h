#ifndef PROCESSINGSTATEWORDABSTRACT_H
#define PROCESSINGSTATEWORDABSTRACT_H

#include "SWP.h"
#include <QSharedPointer>

class UnitNode;
class ProcessingStateWordAbstract : public QObject
{
    Q_OBJECT
    StateWord data;
    QSharedPointer<UnitNode> un;
public:
//    ProcessingStateWordAbstract(const ProcessingStateWordAbstract&) = default;
//    ProcessingStateWordAbstract(ProcessingStateWordAbstract&&) = default;
//    ProcessingStateWordAbstract & operator=(const ProcessingStateWordAbstract&) = default;
//    ProcessingStateWordAbstract& operator=(ProcessingStateWordAbstract&&) = default;

    ProcessingStateWordAbstract(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWordAbstract();
    const StateWord &getData() const;
    const QSharedPointer<UnitNode> &getUn() const;

    virtual bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const = 0;
public slots:
    bool processing();
};

#endif // PROCESSINGSTATEWORDABSTRACT_H
