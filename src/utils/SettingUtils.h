#ifndef SETTINGUTILS_H
#define SETTINGUTILS_H

#include <QCoreApplication>

class QSettings;
class UnitNode_CFG;
class SettingUtils
{
private:
    static QList<UnitNode_CFG *> listTreeUnitNodes;

public:
    SettingUtils();
    static QList<UnitNode_CFG *> loadTreeUnitNodes(UnitNode_CFG * root, QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static QList<UnitNode_CFG *> loadEmptyTree(UnitNode_CFG * root);

    static QList<UnitNode_CFG *> &getListTreeUnitNodes();

    static QVariant getValueSettings(const QString key, const QString group, const QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    static bool loadTreeUnitNodes(UnitNode_CFG * root, UnitNode_CFG *unit);
};

#endif // SETTINGUTILS_H
