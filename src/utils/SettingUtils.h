#ifndef SETTINGUTILS_H
#define SETTINGUTILS_H

#include <QSettings>
#include <UnitNode.h>
//#include <AbstractPort.h>
//#include <PortFactory.h>



class SettingUtils
{
private:
    static QList<UnitNode *> listTreeUnitNodes;
    static QSet<UnitNode *> listMetaRealUnitNodes;

public:
    SettingUtils();
    static QList<UnitNode *> loadTreeUnitNodes(UnitNode * root, QString fileName = "rifx.ini");
    static QList<UnitNode *> getListTreeUnitNodes();
    static QSet<UnitNode *> getSetMetaRealUnitNodes();

    static QVariant getValueSettings(const QString key, const QString group, const QString fileName = "rifx.ini");
};

#endif // SETTINGUTILS_H
