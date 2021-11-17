#include "unitwidget.h"
#include "ui_unitwidget.h"
#include <QDebug>
#include <QMessageBox>

UnitWidget::UnitWidget(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN, QModelIndex* current)
{
    ID=0;

    this->modelTreeUN=modelTreeUN;
    this->current=current;

    if(current->isValid()){
        qDebug()<<"+";
    }else{
        qDebug()<<"-";
    }

    this->comm=comm;
    this->coord=coord;
    coord_mode=coordinateWigget_mode::nothing;
    comm_is_needed=false;

    ui->setupUi(this);






}

UnitWidget::~UnitWidget()
{
    delete ui;
}

int UnitWidget::getID()
{
    return ID;
}

void UnitWidget::get_option(UnitNode *unit)
{
  qDebug()<<"UnitWidget::get_option";

  comm->setVisible(comm_is_needed?true:false);
  comm->get_options(unit,getID());

 // coord->setVisible(false);
  coord->set_mode(coord_mode);

  coord->get_options(unit);


 if(unit){
        get_from(unit);
        setEnabled(false);

  }else{
        get_default();
        setEnabled(true);
  }
 update_name();

}

bool UnitWidget::set_option(UnitNode *unit)
{

    comm->set_options(unit);
    coord->set_options(unit);
    set_to(unit);
    if(accepted(unit)){
    set_timeouts(unit);
    return true;
    }

    return false;

}

bool UnitWidget::accepted(UnitNode *unit)
{
    return false;
}

bool UnitWidget::no_equal_unit_from_one_parent(UnitNode *unit)
{
    bool res=true;
    qDebug()<<"[no_equal_unit_from_one_parent]";
    QModelIndex double_unit_index;
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());
    //Если общий родитель
    int cnt=0;
    qDebug()<<"["<<cnt<<"]";cnt++;
    QModelIndex ind = modelTreeUN->findeIndexUN(parent);

qDebug()<<"["<<cnt<<"]";cnt++;
    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,parent);
qDebug()<<"["<<cnt<<"]";cnt++;
    foreach(UnitNode *un, List1 )
    {

        qDebug()<<"смотрим: "<<un->getName();

       QModelIndex index=modelTreeUN->findeIndexUN(un);
       QModelIndex un_parent_index= modelTreeUN->parent(index);

     if(ind==un_parent_index) //ищем юнитов с тем же родителем
      {
         qDebug()<<"[+]";
         if(un->getType()==unit->getType())
         if(equal(unit,un))//проверяем не идентичны ли они
         {
            double_unit_index=modelTreeUN->findeIndexUN(un);
        //     this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
            qDebug()<<"@@Name: "<<un->getName()<<" и "<<unit->getName();un->show();unit->show();
            // QMessageBox::critical(0,"Ошибка","Такой обьект уже существует!!");
             res=false;

         }
      }
    }


    return res;
}
QString UnitWidget::get_dd(UnitNode *unit)
{
    QModelIndex ind = modelTreeUN->findeIndexUN(unit);
    QModelIndex ind_Y4 = modelTreeUN->parent(ind);
    UnitNode* Y4= static_cast<UnitNode*>(ind_Y4.internalPointer());




    QString str;
    str.clear();
    str.append(QString::number(unit->getNum2()-Y4->getNum2()+1));
    return str;
}

void UnitWidget::set_timeouts(UnitNode *unit)
{


    int val=unit->getUdpTimeout();

    qDebug()<<"Set timeouts value "<<val<<" for "<<m_TypeUnitNode_d.value(unit->getType());



    QList<UnitNode *>  list;
    modelTreeUN->getListFromModel(list,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN


    if(unit->getUdpUse()==0)
    {
 qDebug()<<"---------------------";
        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN
        foreach(UnitNode *un, List1 )
        {
      //      qDebug()<<"------";
      //    qDebug()<<unit->getName();


         if((un->getNum3()==unit->getNum3())) //ищем юниты котрые всият на одном порте с нашим
         if(timeout_brother(un))//проверяем не идентичны ли они
         {
            qDebug()<<un->getName();
            un->setUdpTimeout(val);
             //this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));


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
         if(timeout_brother(un))//проверяем не идентичны ли они
          {

             un->setUdpTimeout(val);
          }
        }
    }
}

void UnitWidget::set_to(UnitNode *unit)
{
  qDebug()<<"UnitWidget::set_option";

}

void UnitWidget::setEnabled(bool val)
{
   comm->setEnabled(val);

   setEnabled_option_menu(val);
}


