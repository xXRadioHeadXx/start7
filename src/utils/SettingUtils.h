#ifndef SETTINGUTILS_H
#define SETTINGUTILS_H

#include <QCoreApplication>
#include <QSettings>
#include <UnitNodeFactory.h>
//#include <AbstractPort.h>
//#include <PortFactory.h>
#include <TreeModelUnitNode.h>



class SettingUtils
{
private:
    static QList<UnitNode *> listTreeUnitNodes;
    static QSet<UnitNode *> listMetaRealUnitNodes;

public:
    SettingUtils();
    static QList<UnitNode *> loadTreeUnitNodes(TreeModelUnitNode *model,UnitNode * root, QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static QList<UnitNode *> loadEmptyTree(UnitNode * root);

    static QList<UnitNode *> &getListTreeUnitNodes();
    static QSet<UnitNode *> &getSetMetaRealUnitNodes();

    static QVariant getValueSettings(const QString key, const QString group, const QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    static bool loadTreeUnitNodes(UnitNode * root, UnitNode *unit);
};

#endif // SETTINGUTILS_H
