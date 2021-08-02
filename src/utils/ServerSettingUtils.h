#ifndef SERVERSETTINGUTILS_H
#define SERVERSETTINGUTILS_H

#include <QCoreApplication>
#include <QSet>

class UnitNode;
class QStringList;
class ServerSettingUtils
{
private:
    static QList<QSharedPointer<UnitNode>> listTreeUnitNodes;
    static QSet<QSharedPointer<UnitNode>> listMetaRealUnitNodes;
    static QList<QSharedPointer<UnitNode>> sortedMetaRealUnitNodes;

public:
    ServerSettingUtils();

    static QList<QSharedPointer<UnitNode> > getLinkedUI(QSharedPointer<UnitNode> un);

    static int linkDoubles(QSharedPointer<UnitNode> &un);
    static QList<QSharedPointer<UnitNode> > loadTreeUnitNodes(QSharedPointer<UnitNode> root, QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static QList<QSharedPointer<UnitNode> > loadEmptyTree(QSharedPointer<UnitNode> root);

    static QList<QSharedPointer<UnitNode> > &getListTreeUnitNodes();
    static QSharedPointer<UnitNode> getTreeUnitNodes(UnitNode*);
    static const QList<QSharedPointer<UnitNode> > &sortMetaRealUnitNodes();
    static QSet<QSharedPointer<UnitNode> > &getSetMetaRealUnitNodes();
    static QSet<QSharedPointer<UnitNode> >::iterator insertMetaRealUnitNodes(const QSharedPointer<UnitNode> &value);
    static QSharedPointer<UnitNode> getMetaRealUnitNodes(UnitNode*);

    static QVariant getValueSettings(const QString key, const QString group, const QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    static bool loadTreeUnitNodes(UnitNode* root, UnitNode*unit);

    static QSet<int>  priorityJoutTyper;

    static QStringList reasonTemplate;
    static QStringList measureTemplate;

    static const QStringList &getReasonTemplate();
    static const QStringList &getMeasureTemplate();
    static const QSet<int> &getPriorityJoutTyper();
};

#endif // SERVERSETTINGUTILS_H
