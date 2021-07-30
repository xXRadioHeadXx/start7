#ifndef SERVERSETTINGUTILS_H
#define SERVERSETTINGUTILS_H

#include <QCoreApplication>
#include <set>

class UnitNode;
class std::list<QString>;
class ServerSettingUtils
{
private:
    static std::list<QSharedPointer<UnitNode> > listTreeUnitNodes;
    static std::set<QSharedPointer<UnitNode> > listMetaRealUnitNodes;

public:
    ServerSettingUtils();

    static std::list<QSharedPointer<UnitNode> > getLinkedUI(QSharedPointer<UnitNode> un);

    static int linkDoubles(QSharedPointer<UnitNode> un);
    static std::list<QSharedPointer<UnitNode> > loadTreeUnitNodes(QSharedPointer<UnitNode> root, QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static std::list<QSharedPointer<UnitNode> > loadEmptyTree(QSharedPointer<UnitNode> root);

    static std::list<QSharedPointer<UnitNode> > &getListTreeUnitNodes();
    static QSharedPointer<UnitNode> getTreeUnitNodes(UnitNode*);
    static std::set<QSharedPointer<UnitNode> > &getSetMetaRealUnitNodes();
    static QSharedPointer<UnitNode> getMetaRealUnitNodes(UnitNode*);

    static QVariant getValueSettings(const QString key, const QString group, const QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    static bool loadTreeUnitNodes(UnitNode* root, UnitNode*unit);

    static std::set<int>  priorityJoutTyper;

    static QList<QString> reasonTemplate;
    static QList<QString> measureTemplate;

    static QList<QString> getReasonTemplate();
    static QList<QString> getMeasureTemplate();
    static const std::set<int> &getPriorityJoutTyper();
};

#endif // SERVERSETTINGUTILS_H
