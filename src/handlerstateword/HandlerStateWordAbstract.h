#ifndef HANDLERSTATEWORDABSTRACT_H
#define HANDLERSTATEWORDABSTRACT_H

#include <DataQueueItem.h>
#include <QSharedPointer>

class DataQueueItem;
class UnitNode;
class StateWord;
class HandlerStateWordAbstract : public QObject
{
    Q_OBJECT
    DataQueueItem dataItem;
public:
    HandlerStateWordAbstract(const DataQueueItem & dataItem);
//    HandlerStateWordAbstract(const HandlerStateWordAbstract&) = default;
//    HandlerStateWordAbstract(HandlerStateWordAbstract&&) = default;
//    HandlerStateWordAbstract & operator=(const HandlerStateWordAbstract&) = default;
//    HandlerStateWordAbstract& operator=(HandlerStateWordAbstract&&) = default;


    virtual ~HandlerStateWordAbstract();

    const DataQueueItem &getDataItem() const;

    void handl(const DataQueueItem &data) const;
    virtual void onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const = 0;

public slots:
    void handl();

};

#endif // HANDLERSTATEWORDABSTRACT_H
