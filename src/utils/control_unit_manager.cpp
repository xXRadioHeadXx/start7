#include "control_unit_manager.h"
#include <QMessageBox>
#include <QHostAddress>
#include <TreeModelUnitNode.h>

Control_Unit_Manager::Control_Unit_Manager(QObject *parent) : QObject(parent)
{

}



bool Control_Unit_Manager::pass_to_add(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN)
{
    double_unit_index=QModelIndex();
     unit->setTreeParentUN(parrent);
qDebug()<<"проверяю "<<unit->getName()<<" родитель "<<unit->getTreeParentUN()->getName();

if(unit->getName()=="")
{
    QMessageBox::critical(0,"Ошибка","Введите имя устройства");

    return false;

}

if (!correct_UDP_parametres(unit))
    return false;



if(unit->getType()==TypeUnitNode::BOD_SOTA)
{
if(false==pass_to_add_BOD_SOTA(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::Y4_SOTA)
{
if(false==pass_to_add_Y4_SOTA(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::DD_SOTA)
{
if(false==pass_to_add_DD_SOTA(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::SD_BL_IP)
{
if(false==pass_to_add_SD_BL_IP(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::IU_BL_IP)
{
if(false==pass_to_add_IU_BL_IP(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::BOD_T4K_M)
{
if(false==pass_to_add_BOD_T4K_M(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::Y4_T4K_M)
{
if(false==pass_to_add_Y4_T4K_M(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::DD_T4K_M)
{
if(false==pass_to_add_DD_T4K_M(unit,parrent,modelTreeUN))
    return false;
}


if(unit->getType()==TypeUnitNode::TG)
{
if(false==pass_to_add_TG(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::RLM_KRL)
{
if(false==pass_to_add_RLM_KRL(unit,parrent,modelTreeUN))
    return false;
}


if(unit->getType()==TypeUnitNode::RLM_C)
{
if(false==pass_to_add_RLM_C(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::KL)
{
if(false==pass_to_add_KL(unit,parrent,modelTreeUN))
{
    qDebug()<<"[false]";
    return false;
}
}

if(unit->getType()==TypeUnitNode::NET_DEV)
{
if(false==pass_to_add_NET_DEV(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::ONVIF)
{
if(false==pass_to_add_ONVIF(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::STRAZH_IP)
{
if(false==pass_to_add_STRAZH_IP(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::DEVLINE)
{
if(false==pass_to_add_DEVLINE(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::INFO_TABLO)
{
if(false==pass_to_add_INFO_TABLO(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::SSOI_IU)
{
if(false==pass_to_add_SSOI_IU(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::SSOI_SD)
{
if(false==pass_to_add_SSOI_SD(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::RASTRMTV)
{
if(false==pass_to_add_RASTRMTV(unit,parrent,modelTreeUN))
    return false;
}

if(unit->getType()==TypeUnitNode::TOROS)
{
if(false==pass_to_add_TOROS(unit,parrent,modelTreeUN))
    return false;
}


if(unit->getType()==TypeUnitNode::GROUP)
{
if(false==pass_to_add_GROUP(unit,parrent,modelTreeUN))
    return false;
}

return true;
}

bool Control_Unit_Manager::pass_to_add_GROUP(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN)
{
//группа может быть добавлена только к системе
    if((parrent->getType()!=TypeUnitNode::SYSTEM))
    {
//        QMessageBox::critical(0,"Ошибка",("Груп к системе");
//        dialog.exec();
        return false;

    }
return true;
}
bool Control_Unit_Manager::pass_to_add_SD_BL_IP(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN)
{
qDebug()<<"СД БЛ-IP";
    //СД BL_IP может быть добавлен только к группе или к системе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&(parrent->getType()!=TypeUnitNode::SYSTEM))
        {

            QMessageBox::critical(0,"Ошибка","СД может быть добавлен только к группе или к системе");

            return false;

        }
   //Num2 от нуля до восьми
    if(unit->getNum2()<0||unit->getNum2()>8)
        return false;

//Не должен повторяться в дереве
    return no_equal_unit(modelTreeUN,unit,modelTreeUN->rootItemUN,[](UnitNode *unit, UnitNode *un)->bool
                         {return ((un->getNum2()==unit->getNum2()));});





        //Находим все СД с таким же UdpAdress
        //Контролируем отсутствие юнита с таким же Num2 и UdpAdress
        return true;
}

bool Control_Unit_Manager::pass_to_add_IU_BL_IP(UnitNode *unit, UnitNode *parent,TreeModelUnitNode *modelTreeUN)
{


    //может быть добавлен к любому датчику группе системе сморти ссои конфигуратор
    if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }



        //Num2 от нуля до четырех
         if(unit->getNum2()<0||unit->getNum2()>4)

             return false;
//Может повторяться в дереве. Не должен повторяться у одного предка.
         return no_equal_unit_from_one_parent(modelTreeUN,unit,parent,[](UnitNode *unit, UnitNode *un)->bool
                              {



                       if(un->getType()==unit->getType())
                       if(un->getUdpUse()==unit->getUdpUse())

                       if(un->getNum2()==unit->getNum2())
                       {
                     //      m_cfg->ui->treeView->setCurrentIndex(m_cfg->modelTreeUN->findeIndexUN(un));

                           return true;
                       }


        return false;
                    });
}

bool Control_Unit_Manager::pass_to_add_BOD_SOTA(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN)
{
    //БОД может быть добавлен только к группе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&
           (parrent->getType()!=TypeUnitNode::SYSTEM)
                )
        {
            QMessageBox::critical(0,"Ошибка","БОД может быть добавлен только к группе");

            return false;

        }

    //    Если связь по RS485 - контроль по RS485 порту
    //    Если связь по UDP - контроль по IP адресу

     //     //qDebug()<<"[BOD_SOTA]";


       return no_equal_unit(modelTreeUN,unit,modelTreeUN->rootItemUN,[](UnitNode *unit, UnitNode *un)->bool
       {
           if(unit->getUdpUse()==0)//нельзя добавлять больше одного БОДа на RS 485
           {
               if(un->getType()==TypeUnitNode::BOD_SOTA)
                   return true;
               if(un->getType()==TypeUnitNode::BOD_T4K_M)
                   return true;

           }
       });







}

bool Control_Unit_Manager::pass_to_add_Y4_SOTA(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN)
{
    //qDebug()<<"[pass_to_add_Y4_SOTA]";
    //Участок может быть добавлен только к БОД Сота/Сота-М
    if(parrent->getType()!=TypeUnitNode::BOD_SOTA)
    {
        QMessageBox::critical(0,"Ошибка","Участок может быть добавлен только к БОД Сота/Сота-М!");

        return false;

    }

    //В одном БОД Сота/Сота-М не должно быть "участков" с двумя одинаковыми участками

    //Составить лист участков этого БОДА
    QList<UnitNode*> List;

    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
    foreach(UnitNode *un, List1 )
    {
       //qDebug()<<".";
//     //qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
       QModelIndex index=modelTreeUN->findeIndexUN(un);
       QModelIndex parent_index= modelTreeUN->parent(index);


     if(modelTreeUN->findeIndexUN(parrent)==parent_index)
      {
 //       //qDebug()<<"Name: "<<un->getName();
        List.append(un);
      }
    }

    foreach(UnitNode *un, List )
    {
     //qDebug()<<"Name: "<<un->getName();
     if(un->getNum2()==unit->getNum2())
     {
      //   this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
         QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
         return false;
     }
    }
    //проконтролировать в нем отсутствие добавляемого участка

    return true;
}

bool Control_Unit_Manager::pass_to_add_DD_SOTA(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN) //номера ДД можно добавлять только один раз в участки 1-2 и 3-4
{
    //добавлять только к участку Сота
    if(parrent->getType()!=TypeUnitNode::Y4_SOTA)
    {
        QMessageBox::critical(0,"Ошибка","ДД может быть добавлен только к участку !");
        return false;

    }

    //В одном боде нет 2х одинаковых ДД

    //Формируем список всех ДД этого БОДа

    //Сравниваем ДД с добавляемым

    QList<UnitNode*> List;

    //Ищем нужный БОД. Это родитель родителя.

    QModelIndex ind = modelTreeUN->findeIndexUN(parrent);
    QModelIndex BOD_ind = modelTreeUN->parent(ind);
//    UnitNode* BOD=static_cast<UnitNode*>(BOD_ind.internalPointer());



    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);

    foreach(UnitNode *un, List1 )
    {

       //qDebug()<<".";
//     //qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
       QModelIndex index=modelTreeUN->findeIndexUN(un);
       QModelIndex parent_index= modelTreeUN->parent(index);

       QModelIndex BOD_index= modelTreeUN->parent(parent_index);

//если юнит является ДД и принадлежит к одномцу из участков того БОДа что и участок к которому добавляем


     if(BOD_index==BOD_ind)
      {
 //       //qDebug()<<"Name: "<<un->getName();
        List.append(un);
      }
    }

    //номер ДД

    //его индекс


    int m_val = unit->getNum2()-parrent->getNum2();

    //qDebug()<<QString::number(m_val);

    foreach(UnitNode *un, List )
    {
    //qDebug()<<"Name: "<<un->getName();

    //номер ДД

    //его индекс
    QModelIndex ind = modelTreeUN->findeIndexUN(un);
    //индекс его родителя
    QModelIndex parent_ind =  modelTreeUN->parent(ind);
    //юнит его родителя
    UnitNode *parent = static_cast<UnitNode*>(parent_ind.internalPointer());

    //qDebug()<<"Name: "<<un->getName()<<" участок "<<QString::number(parent->getNum2());

    if((100==parrent->getNum2())||((200==parrent->getNum2())))
        {
            if((100==parent->getNum2())||((200==parent->getNum2())))
            {
                int val = un->getNum2()-parent->getNum2();
                 //qDebug()<<QString::number(m_val)<<" "<<QString::number(val);
                if(m_val==val)
                {


                //    this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
                    QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

                    return false;
                }
            }
        }
    if((300==parrent->getNum2())||((400==parrent->getNum2())))
        {
            if((300==parent->getNum2())||((400==parent->getNum2())))
            {
                int val = un->getNum2()-parent->getNum2();
                 //qDebug()<<QString::number(m_val)<<" "<<QString::number(val);
                if(m_val==val)
                {


                //    this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
                    QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                    return false;
                }
            }
        }

    }



    return true;
}

bool Control_Unit_Manager::pass_to_add_BOD_T4K_M(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN)
{
    //БОД может быть добавлен только к группе
    if((parrent->getType()!=TypeUnitNode::GROUP)&&
       (parrent->getType()!=TypeUnitNode::SYSTEM)
            )
        {
            QMessageBox::critical(0,"Ошибка","БОД может быть добавлен только к группе");
            return false;

        }

    //    Если связь по RS485 - контроль по RS485 порту
    //    Если связь по UDP - контроль по IP адресу


    return no_equal_unit(modelTreeUN,unit,modelTreeUN->rootItemUN,[](UnitNode *unit, UnitNode *un)->bool
                {
                if(unit->getUdpUse()==0)//нельзя добавлять больше одного БОДа на RS 485
                {
                    if(un->getType()==TypeUnitNode::BOD_SOTA)
                        return true;
                    if(un->getType()==TypeUnitNode::BOD_T4K_M)
                        return true;

                }
                return (un->getNum1()==unit->getNum1());


                ;});


}

bool Control_Unit_Manager::pass_to_add_Y4_T4K_M(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN)
{

    //Участок может быть добавлен только к БОД
    if(parrent->getType()!=TypeUnitNode::BOD_T4K_M)
    {
        QMessageBox::critical(0,"Ошибка","Участок может быть добавлен только к БОД Точка-М/Гарда-М !");
        return false;

    }

    //В одном БОД  не должно быть "участков" с двумя одинаковыми участками

    //Составить лист участков этого БОДА
    QList<UnitNode*> List;

    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
    foreach(UnitNode *un, List1 )
    {
       //qDebug()<<".";
//     //qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
       QModelIndex index=modelTreeUN->findeIndexUN(un);
       QModelIndex parent_index= modelTreeUN->parent(index);


     if(modelTreeUN->findeIndexUN(parrent)==parent_index)
      {
 //       //qDebug()<<"Name: "<<un->getName();
        List.append(un);
      }
    }

    foreach(UnitNode *un, List )
    {
     //qDebug()<<"Name: "<<un->getName();
     if(un->getNum2()==unit->getNum2())
     {
    //     this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
         QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

         return false;
     }
    }
    //проконтролировать в нем отсутствие добавляемого участка

    return true;

}

bool Control_Unit_Manager::pass_to_add_DD_T4K_M(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN)//номера ДД можно добавлять только один раз в участки 1-2 и 3-4
{
    //добавлять только к участку Сота
    if(parrent->getType()!=TypeUnitNode::Y4_T4K_M)
    {
        QMessageBox::critical(0,"Ошибка","ДД может быть добавлен только к участку !");
        return false;

    }

    //В одном боде нет 2х одинаковых ДД

    //Формируем список всех ДД этого БОДа

    //Сравниваем ДД с добавляемым

    QList<UnitNode*> List;

    //Ищем нужный БОД. Это родитель родителя.

    QModelIndex ind = modelTreeUN->findeIndexUN(parrent);
    QModelIndex BOD_ind = modelTreeUN->parent(ind);
//    UnitNode* BOD=static_cast<UnitNode*>(BOD_ind.internalPointer());



    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);

    foreach(UnitNode *un, List1 )
    {

       //qDebug()<<".";
//     //qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
       QModelIndex index=modelTreeUN->findeIndexUN(un);
       QModelIndex parent_index= modelTreeUN->parent(index);

       QModelIndex BOD_index= modelTreeUN->parent(parent_index);

//если юнит является ДД и принадлежит к одномцу из участков того БОДа что и участок к которому добавляем


     if(BOD_index==BOD_ind)
      {
 //       //qDebug()<<"Name: "<<un->getName();
        List.append(un);
      }
    }

    int m_val = unit->getNum2()-parrent->getNum2();

    //qDebug()<<QString::number(m_val);

    foreach(UnitNode *un, List )
    {
    //qDebug()<<"Name: "<<un->getName();

    //номер ДД

    //его индекс
    QModelIndex ind = modelTreeUN->findeIndexUN(un);
    //индекс его родителя
    QModelIndex parent_ind =  modelTreeUN->parent(ind);
    //юнит его родителя
    UnitNode *parent = static_cast<UnitNode*>(parent_ind.internalPointer());

    //qDebug()<<"Name: "<<un->getName()<<" участок "<<QString::number(parent->getNum2());

    if((100==parrent->getNum2())||((200==parrent->getNum2())))
        {
            if((100==parent->getNum2())||((200==parent->getNum2())))
            {
                int val = un->getNum2()-parent->getNum2();
                 //qDebug()<<QString::number(m_val)<<" "<<QString::number(val);
                if(m_val==val)
                {


           //         this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
                    QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                    return false;
                }
            }
        }
    if((300==parrent->getNum2())||((400==parrent->getNum2())))
        {
            if((300==parent->getNum2())||((400==parent->getNum2())))
            {
                int val = un->getNum2()-parent->getNum2();
                 //qDebug()<<QString::number(m_val)<<" "<<QString::number(val);
                if(m_val==val)
                {


                 //   this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
                    QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                    return false;
                }
            }
        }

    }
    return true;
}

bool Control_Unit_Manager::pass_to_add_TG(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN)
{

   //ЧЭ от одного до четырех
     if(unit->getNum2()<0||unit->getNum2()>4)
     {
         QMessageBox::critical(0,"Ошибка","ЧЭ от одного до четырех !");
         return false;

     }
   //только к группе
    if(parrent->getType()!=TypeUnitNode::GROUP)
    {
        QMessageBox::critical(0,"Ошибка","устройство Точка/Гарда может быть добавлено только к группе !");
        return false;

    }

    return no_equal_unit(modelTreeUN,unit,modelTreeUN->rootItemUN,[](UnitNode *unit, UnitNode *un)->bool
                         {

             if((un->getNum1()==unit->getNum1()))
             {
                 if(un->getType()!=unit->getType())//если другое устройство (не ЧЭ) на этом адресе этого порта
                  {
                //     m_cfg->ui->treeView->setCurrentIndex(m_cfg->modelTreeUN->findeIndexUN(un));
                     QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                     return false;
                  }
                 if(un->getType()==unit->getType()) //если на этом адресе этого порта есть ЧЭ - проверить на номер ЧЭ
                  {
                     if(un->getNum2()==unit->getNum2())
                     {
                    //     m_cfg->ui->treeView->setCurrentIndex(m_cfg->modelTreeUN->findeIndexUN(un));
                         QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                         return false;
                     }
                  }
             }
                     });


}

bool Control_Unit_Manager::pass_to_add_RLM_KRL(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN)
{
    // может быть добавлен только к группе
        if(parrent->getType()!=TypeUnitNode::GROUP)
        if(parrent->getType()!=TypeUnitNode::SYSTEM)
        {
            QMessageBox::critical(0,"Ошибка"," может быть добавлен только к группе");
            return false;

        }

    //    Если связь по RS485 - контроль по RS485 порту
    //    Если связь по UDP - контроль по IP адресу



        return no_equal_unit(modelTreeUN,unit,modelTreeUN->rootItemUN,[](UnitNode *unit, UnitNode *un)->bool
                             {return ((un->getNum1()==unit->getNum1()));});

}

bool Control_Unit_Manager::pass_to_add_RLM_C(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN)
{
    if(parrent->getType()!=TypeUnitNode::GROUP)
    if(parrent->getType()!=TypeUnitNode::SYSTEM)
    {
        QMessageBox::critical(0,"Ошибка"," может быть добавлен только к группе");
        return false;

    }

//    Если связь по RS485 - контроль по RS485 порту
//    Если связь по UDP - контроль по IP адресу


    return no_equal_unit(modelTreeUN,unit,modelTreeUN->rootItemUN,[](UnitNode *unit, UnitNode *un)->bool
                         {return ((un->getNum1()==unit->getNum1()));});
}

bool Control_Unit_Manager::pass_to_add_KL(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN)
{
      //qDebug()<<"[----------------------------------------------]";
    //СД от одного до четырех
      if(unit->getNum2()<0||unit->getNum2()>4)
      {
          QMessageBox::critical(0,"Ошибка","СД от одного до четырех !");
          return false;

      }


    // может быть добавлен только к группе
        if(parrent->getType()!=TypeUnitNode::GROUP)
        if(parrent->getType()!=TypeUnitNode::SYSTEM)
        {
            QMessageBox::critical(0,"Ошибка"," может быть добавлен только к группе");
            return false;
        }

        return no_equal_unit(modelTreeUN,unit,modelTreeUN->rootItemUN,[](UnitNode *unit, UnitNode *un)->bool
                             {
                 if((un->getNum1()==unit->getNum1()))
                 {
                       qDebug()<<"[2]";
                     if(un->getType()!=unit->getType())//если другое устройство  на этом адресе этого порта
                      {
                           qDebug()<<"[3]";

                       //  m_cfg->ui->treeView->setCurrentIndex(m_cfg->modelTreeUN->findeIndexUN(un));
                                                return true;
                      }
                     if(un->getType()==unit->getType()) //если на этом адресе этого порта есть СД - проверить на номер СД
                      {
                           qDebug()<<"[4]";
                         if(un->getNum2()==unit->getNum2())
                         {
                               qDebug()<<"[5]";
                        //     m_cfg->ui->treeView->setCurrentIndex(m_cfg->modelTreeUN->findeIndexUN(un));
                               return true;

                         }

                      }

                 }
                 return false;
});
}

bool Control_Unit_Manager::pass_to_add_ONVIF(UnitNode *unit, UnitNode *parent,TreeModelUnitNode *modelTreeUN)
{
//добавляется в системе группе и любому датчику - у одной точке
//не более одной камеры с одним айпишником

    //qDebug()<<"onvif";
    if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }




return no_equal_unit_from_one_parent(modelTreeUN,unit,parent,[](UnitNode *unit, UnitNode *un)->bool{
             return(un->getIcon1Path()==unit->getIcon1Path());}
);
/*
     if(un->getParentUN()==unit->getParentUN())
     if(un->getType()==unit->getType())
     if(un->getIcon1Path()==unit->getIcon1Path())
     {
         this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));QMessageBox::critical(0,"Ошибка",("Такой обьект уже существует");
         dialog.exec();
         return false;

     }
*/

        return true;
}

bool Control_Unit_Manager::pass_to_add_STRAZH_IP(UnitNode *unit, UnitNode* parrent,TreeModelUnitNode *modelTreeUN)
{
    //может быть добавлен к любому датчику группе системе сморти ссои конфигуратор
    if((parrent->getType()==TypeUnitNode::STRAZH_IP)||
       (parrent->getType()==TypeUnitNode::ONVIF)||
       (parrent->getType()==TypeUnitNode::DEVLINE)||
       (parrent->getType()==TypeUnitNode::RASTRMTV)||
       (parrent->getType()==TypeUnitNode::INFO_TABLO)||
       (parrent->getType()==TypeUnitNode::SSOI_IU) ||
       (parrent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }



    QModelIndex ind = modelTreeUN->findeIndexUN(parrent);


    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);

    foreach(UnitNode *un, List1 )
    {

       //qDebug()<<".";
//     //qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
       QModelIndex index=modelTreeUN->findeIndexUN(un);
       QModelIndex un_parent_index= modelTreeUN->parent(index);

     if(ind==un_parent_index)
      {
         //qDebug()<<"[+]";
         if(un->getType()==unit->getType())
             if((un->getIcon1Path()==unit->getIcon1Path())||
             (un->getIcon4Path()==unit->getIcon4Path()))
         {
         //    this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
                 QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

             return false;

         }
      }
    }

 /*
    foreach(UnitNode *un, List1 )
    {

     if(un->getType()==unit->getType())

     if((un->getIcon1Path()==unit->getIcon1Path())||
        (un->getIcon4Path()==unit->getIcon4Path()))
     {
         this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));QMessageBox::critical(0,"Ошибка",("Такой обьект уже существует");
         dialog.exec();
         return false;

     }

    }
*/
        return true;
}

bool  Control_Unit_Manager::pass_to_add_NET_DEV(UnitNode */*unit*/, UnitNode *parrent,TreeModelUnitNode *modelTreeUN)
{
    if(parrent->getType()!=TypeUnitNode::GROUP)
    if(parrent->getType()!=TypeUnitNode::SYSTEM)
    {
        QMessageBox::critical(0,"Ошибка","БОД может быть добавлен только к группе");
        return false;

    }

    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
 /*   foreach(UnitNode *un, List1 )
    {
     if(un->getType()==unit->getType())
     if(un->getIcon1Path()==unit->getIcon1Path())
     {
         QMessageBox::critical(0,"Ошибка",("Такой обьект уже есть");
         dialog.exec();
         return false;

     }

    }*/
    return true;
}

bool Control_Unit_Manager::pass_to_add_SSOI_SD(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN)
{
    //СД может быть добавлен только к группе или к системе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&(parrent->getType()!=TypeUnitNode::SYSTEM))
        {
            QMessageBox::critical(0,"Ошибка","СД может быть добавлен только к группе или к системе");
            return false;

        }
   //Num2 от нуля до 99
    if(unit->getNum2()<0||unit->getNum2()>99)
        return false;


        //qDebug()<<"[RS485]";
        //Контролируем отсутствие юнита с таким же Num1 Num2 и Num3

           QList<UnitNode *> List1;
           modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
           foreach(UnitNode *un, List1 )
           {
            if(un->getType()==unit->getType())
            if(un->getNum1()==unit->getNum1())
            if(un->getNum2()==unit->getNum2())
            if(un->getNum3()==unit->getNum3())
            {
                double_unit_index=modelTreeUN->findeIndexUN(un);
            //    this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                return false;
            }
           }
           return true;




}

bool Control_Unit_Manager::pass_to_add_SSOI_IU(UnitNode *unit, UnitNode *parent,TreeModelUnitNode *modelTreeUN)
{
    //может быть добавлен к любому датчику группе системе сморти ссои конфигуратор
    if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP))

    {

        return false;

    }

    return true;

    //
}

bool Control_Unit_Manager::pass_to_add_TOROS(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN)
{
    //может быть добавлен только к группе или к системе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&(parrent->getType()!=TypeUnitNode::SYSTEM))
        {
            QMessageBox::critical(0,"Ошибка",("может быть добавлен только к группе или к системе"));
//            dialog.exec();
            return false;

        }

        return no_equal_unit(modelTreeUN,unit,modelTreeUN->rootItemUN,[](UnitNode *unit, UnitNode *un)->bool
                             {return ((un->getNum1()==unit->getNum1()));});





}

bool Control_Unit_Manager::pass_to_add_DEVLINE(UnitNode *unit, UnitNode *parent,TreeModelUnitNode *modelTreeUN)
{
    //Не может быть добавлен к юнитам следующего типа
    if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }

//не должен повторяться у одного родителя
    return no_equal_unit_from_one_parent(modelTreeUN,unit,parent,[](UnitNode *unit, UnitNode *un)->bool{
        //сравнение провожу по актуальным для того типа устройства параметрам
        return((un->getNum1()==unit->getNum1())&&(un->getOutType()==unit->getOutType()));}
);

}

bool Control_Unit_Manager::pass_to_add_RASTRMTV(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN)
{
    //qDebug()<<"RASTRMTV";
    if((parrent->getType()==TypeUnitNode::STRAZH_IP)||
       (parrent->getType()==TypeUnitNode::ONVIF)||
       (parrent->getType()==TypeUnitNode::DEVLINE)||
       (parrent->getType()==TypeUnitNode::RASTRMTV)||
       (parrent->getType()==TypeUnitNode::INFO_TABLO)||
       (parrent->getType()==TypeUnitNode::SSOI_IU) ||
       (parrent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }
/*
    if(this->ui->RASTRMTV_Name_SerNum->currentText()=="не определено")
    {
        QMessageBox::critical(0,"Ошибка","Устройство не определено");
        return false;

    }
*/



    return true;
}

bool Control_Unit_Manager::pass_to_add_INFO_TABLO(UnitNode *unit, UnitNode *parrent,TreeModelUnitNode *modelTreeUN)
{
    if(parrent->getType()!=TypeUnitNode::GROUP)
    if(parrent->getType()!=TypeUnitNode::SYSTEM)
    {
        QMessageBox::critical(0,"Ошибка"," может быть добавлен только к группе");
        return false;

    }
    //проверка по участку (Num2)
    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
    foreach(UnitNode *un, List1 )
    {

     if((un->getNum2()==unit->getNum2()))
     {

       //  this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
         QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
         return false;
     }


    }
}

bool Control_Unit_Manager::correct_UDP_parametres(UnitNode *unit)
{
    //qDebug()<<"UdpUse "<<unit->getUdpUse();
    //qDebug()<<"UdpAdress "<<unit->getUdpAdress();
    if(unit->getUdpUse()==1)
    {
        QHostAddress myIP;
           if(myIP.setAddress( unit->getUdpAdress()))
           {
           //qDebug()<<"Valid IP Address";
           unit->setUdpAdress(myIP.toString());
           }
           else
           {
           qDebug()<<"Invalid IP address";

        QMessageBox::critical(0,"Ошибка","Не заданы пармаетры UDP протокола (IP адрес или порт)");

        return false;
           }
    }
    return true;
}

QModelIndex Control_Unit_Manager::getDouble_unit_index() const
{
    return double_unit_index;
}

// Здесь
// bool (*is_equal)(UnitNode *unit, UnitNode *un)
// сравнивает юниты по параметрам
// определенным образом в зависимости от типа
//
bool Control_Unit_Manager::no_equal_unit(TreeModelUnitNode *modelTreeUN,UnitNode *unit,UnitNode *supreme, bool (*is_equal)(UnitNode *unit, UnitNode *un))
{
    //Если тип связи RS-485, на одном порте не должно висеть двух юнитов с одинаковыми параметрами
    if(unit->getUdpUse()==0)
    {
 qDebug()<<"---------------------";
        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,supreme);//modelTreeUN->rootItemUN
        foreach(UnitNode *un, List1 )
        {
            qDebug()<<"------";
            qDebug()<<unit->getName();
            qDebug()<<un->getName();

         if((un->getNum3()==unit->getNum3())) //ищем юниты котрые всият на одном порте с нашим
         if(is_equal(unit,un))//проверяем не идентичны ли они
         {
            double_unit_index=modelTreeUN->findeIndexUN(un);
             //this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
             QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
             return false;
         }


        }


    }
    //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

    if(unit->getUdpUse()==1)
    {

        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
        foreach(UnitNode *un, List1 )
        {

         if((un->getUdpAdress()==unit->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
         if((un->getUdpPort()==unit->getUdpPort()))
         if(is_equal(unit,un))//проверяем не идентичны ли они
          {
            double_unit_index=modelTreeUN->findeIndexUN(un);
             QMessageBox::critical(0,"Ошибка","Объект с такими параметрами уже существует");
             return false;
          }
        }
    }
    return true;
}


// Здесь
// bool (*is_equal)(UnitNode *unit, UnitNode *un)
// сравнивает юниты по параметрам
// определенным образом в зависимости от типа
//
//Для тех юнитов которые можно несколько раз размещать в дереве, но не нет смысла более одного раза указаывать у одного родителя
bool Control_Unit_Manager::no_equal_unit_from_one_parent(TreeModelUnitNode *modelTreeUN,UnitNode *unit, UnitNode *parent, bool (*is_equal)(UnitNode *, UnitNode *))
{
    //Если общий родитель
    QModelIndex ind = modelTreeUN->findeIndexUN(parent);


    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,parent);

    foreach(UnitNode *un, List1 )
    {


       QModelIndex index=modelTreeUN->findeIndexUN(un);
       QModelIndex un_parent_index= modelTreeUN->parent(index);

     if(ind==un_parent_index) //ищем юнитов с тем же родителем
      {
         //qDebug()<<"[+]";
         if(un->getType()==unit->getType())
         if(is_equal(unit,un))//проверяем не идентичны ли они
         {
        //     this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
             QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
             return false;

         }
      }
    }
    return true;
}
