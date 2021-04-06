#ifndef CONTROL_UNIT_MANAGER_H
#define CONTROL_UNIT_MANAGER_H

#include <QObject>
#include<UnitNode.h>
#include <TreeModelUnitNode.h>
class Control_Unit_Manager : public QObject
{
    Q_OBJECT
public:
    explicit Control_Unit_Manager(QObject *parent = nullptr);

    //Проверка юнита на валидарность
    //По значениям полей юнита
    //К тому ли родителю добавлен юнит
    //Отсутсвие двойников в дереве (по необходимости) и у одного родителя
            bool  pass_to_add(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);

    //Проверка каждого из типов юнитов
            bool  pass_to_add_GROUP(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_SD_BL_IP(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_IU_BL_IP(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_TG(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_RLM_KRL(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_RLM_C(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_BOD_T4K_M(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_Y4_T4K_M(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_DD_T4K_M(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_BOD_SOTA(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_Y4_SOTA(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_DD_SOTA(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_KL(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_ONVIF(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_STRAZH_IP(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_NET_DEV(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_SSOI_SD(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_SSOI_IU(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_ADAM(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_TOROS(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_DEVLINE(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_RASTRMTV(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);
            bool  pass_to_add_INFO_TABLO(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN);

            bool correct_UDP_parametres(UnitNode *unit);


           QModelIndex double_unit_index;
    //проверка на отсутствие двойников во всем дереве
            bool no_equal_unit(TreeModelUnitNode *modelTreeUN,UnitNode *unit,UnitNode *supreme,bool (*is_equal)(UnitNode* unit,UnitNode* un));
    //проверка на отсутствие двойников у одного родителя
            bool no_equal_unit_from_one_parent(TreeModelUnitNode *modelTreeUN, UnitNode *unit, UnitNode *parent, bool (*is_equal)(UnitNode *, UnitNode *));

            QModelIndex  getDouble_unit_index() const;

signals:

};

#endif // CONTROL_UNIT_MANAGER_H
