#ifndef SETTINGUTILS_H
#define SETTINGUTILS_H

#include <QCoreApplication>

class QSettings;
class UnitNode;
class SettingUtils
{
private:
    static QList<UnitNode *> listTreeUnitNodes;
    static QSet<UnitNode *> listMetaRealUnitNodes;

public:
    SettingUtils();
    static QList<UnitNode *> loadTreeUnitNodes(UnitNode * root, QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static QList<UnitNode *> loadEmptyTree(UnitNode * root);

    static QList<UnitNode *> &getListTreeUnitNodes();
    static QSet<UnitNode *> &getSetMetaRealUnitNodes();

    static QVariant getValueSettings(const QString key, const QString group, const QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    static bool loadTreeUnitNodes(UnitNode * root, UnitNode *unit);
};

#endif // SETTINGUTILS_H
