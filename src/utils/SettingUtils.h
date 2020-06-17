#ifndef SETTINGUTILS_H
#define SETTINGUTILS_H

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
//    static QList<AbstractPort *> loadPorts(QString fileName = "rifx.ini");
    static QList<UnitNode *> getListTreeUnitNodes();
    static QSet<UnitNode *> getSetMetaRealUnitNodes();
};

#endif // SETTINGUTILS_H
