#include "../src/utils/IniFileService.h"

#include <QCoreApplication>
#include <QTextCodec>
#include "../src/utils/SimpleIni.h"
#include "../src/entity/UnitNodeFactory.h"

void IniFileService::afterConstructInitializationImpl()
{
    codec = QTextCodec::codecForName("Windows-1251");

    QString filePath = QCoreApplication::applicationDirPath() + "/rifx.ini";
    ini.LoadFile(filePath.toStdString().c_str());
}

QSharedPointer<UnitNode> IniFileService::makeSharedUnitNodeBySection(const QString section)
{
    auto self = dynamic_cast<IniFileServiceImpl *>(&IniFileService::instance());
    return self->makeSharedUnitNodeBySection(section);
}

const QString IniFileService::getValueBySectionKey(const QString section, const QString key, const QString defaultValue)
{
    auto self = dynamic_cast<IniFileServiceImpl *>(&IniFileService::instance());
    return self->getValueBySectionKey(section, key, defaultValue);
}
