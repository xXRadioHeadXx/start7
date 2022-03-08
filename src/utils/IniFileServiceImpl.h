#ifndef INIFILESERVICEIMPL_H
#define INIFILESERVICEIMPL_H
#include "SimpleIni.h"

#include <QSharedPointer>

#include <template/AfterConstructInitialization.h>

class QTextCodec;
class UnitNode;
class QString;
class IniFileServiceImpl : public AfterConstructInitialization
{
protected:
    const QTextCodec *codec;
    CSimpleIniA ini;

private:

public:
    virtual ~IniFileServiceImpl() {}

    QSharedPointer<UnitNode> makeSharedUnitNodeBySection(const QString section);
    const QString getValueBySectionKey(const QString section, const QString key, const QString defaultValue);

};

#endif // INIFILESERVICEIMPL_H
