#ifndef INIFILESERVICE_H
#define INIFILESERVICE_H

#include "template/SingletonTemplate.h"

#include "IniFileServiceImpl.h"

#include <QSharedPointer>
#include <UnitNode.h>
#include "SimpleIni.h"


class IniFileService : public IniFileServiceImpl, public SingletonTemplate<IniFileService>
{
private:
    virtual void afterConstructInitializationImpl() override;

public:
    virtual ~IniFileService() {}

    static QSharedPointer<UnitNode> makeSharedUnitNodeBySection(const QString section);
    static const QString getValueBySectionKey(const QString section, const QString key, const QString defaultValue = "");
};

#endif // INIFILESERVICE_H
