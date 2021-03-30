#ifndef SERVERSETTINGUTILS_H
#define SERVERSETTINGUTILS_H

#include <QCoreApplication>

class QSettings;
class UnitNode;
class ServerSettingUtils
{
private:
    static QList<QSharedPointer<UnitNode> > listTreeUnitNodes;
    static QSet<QSharedPointer<UnitNode> > listMetaRealUnitNodes;

public:
    ServerSettingUtils();
    static QList<QSharedPointer<UnitNode> > loadTreeUnitNodes(QSharedPointer<UnitNode> root, QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static QList<QSharedPointer<UnitNode> > loadEmptyTree(QSharedPointer<UnitNode> root);

    static QList<QSharedPointer<UnitNode> > &getListTreeUnitNodes();
    static QSharedPointer<UnitNode> getTreeUnitNodes(UnitNode*);
    static QSet<QSharedPointer<UnitNode> > &getSetMetaRealUnitNodes();
    static QSharedPointer<UnitNode> getMetaRealUnitNodes(UnitNode*);

    static QVariant getValueSettings(const QString key, const QString group, const QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    static bool loadTreeUnitNodes(UnitNode* root, UnitNode*unit);
};

#endif // SERVERSETTINGUTILS_H
