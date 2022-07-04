#ifndef CONTEXTARGMAP_H
#define CONTEXTARGMAP_H

#include <QMap>
#include <QObject>
#include "../src/template/SingletonTemplate.h"

class ContextArgMap : public QObject, public SingletonTemplate<ContextArgMap>
{
    Q_OBJECT

    QMap<QString, QString> map;

public:
    virtual ~ContextArgMap() {};
    static QMap<QString, QString> &argMap();
};

#endif // CONTEXTARGMAP_H
