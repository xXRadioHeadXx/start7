#include "unitwidget.h"
#include "ui_unitwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

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

    connect(comm,SIGNAL(updateIP(int)),this,SLOT(updateName_slot(int)));




}

UnitWidget::~UnitWidget()
{
//    delete ui;
}

int UnitWidget::getID()
{
    return ID;
}
/*Перебираем юниты
 * Если у нашего - RS485
 * ищем юниты с тем же типом связи портом и адресом
 * если находим - возвращаем false
 *
 *
 *
 *
 */
bool UnitWidget::free_adress(UnitNode* unit)
{

    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN
    //перебираем юниты
    foreach(UnitNode *un, List1 )
    {
         if(un->getUdpUse()==unit->getUdpUse()){

//Если  RS485
              if(unit->getUdpUse()==0){
                  if(un->getNum3()==unit->getNum3())
                  if(un->getNum1()==unit->getNum1()){

                      this->double_unit_index=modelTreeUN->findeIndexUN(un);
                      QString str="Адрес уже занят устройством ";
                      str.append(un->getName());
                      QMessageBox::critical(0,"Ошибка",str);
                  }
              }

              if(unit->getUdpUse()==1){
                  if(un->getUdpAdress()==unit->getUdpAdress())
                  if(un->getUdpPort()==unit->getUdpPort()){

                      this->double_unit_index=modelTreeUN->findeIndexUN(un);
                      QString str="Адрес уже занят устройством ";
                      str.append(un->getName());
                      QMessageBox::critical(0,"Ошибка",str);
                  }
              }
         }




    }
}

void UnitWidget::get_option(UnitNode *unit)
{
  qDebug()<<"UnitWidget::get_option";

  comm->setVisible(comm_is_needed?true:false);

  if(comm_is_needed){

      comm->setID(this->getID());
      comm->setVisible(true);

  }else{

      comm->setVisible(false);
  }



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
    qDebug()<<"set_options "<<m_TypeUnitNode_d.value(unit->getType());
    if(current){
    comm->set_options(unit);
    coord->set_options(unit);
    set_to(unit);

    if(comm_is_needed){
        if (!ip_is_valid(unit->getUdpAdress())){
            return false;
        }

    }


    if(accepted(unit,modelTreeUN,current)){

        if(comm_is_needed){
            if(!line_is_busy(unit)){

                qDebug()<<"SET TIMEOUTS";
            set_timeouts(unit);
            return true;
            }
        }
        else{
            return true;
        }

    }


    }
    return false;

}

bool UnitWidget::edit(UnitNode *unit)
{
    comm->set_options(unit);
    coord->set_options(unit);
    set_to(unit);
}

bool UnitWidget::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
    return false;
}

bool UnitWidget::no_equal_unit(UnitNode *unit)
{
    double_unit_index=QModelIndex();
    {
 qDebug()<<"---------------------";
        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN
        foreach(UnitNode *un, List1 )
        {
        //    qDebug()<<"------";
       //     qDebug()<<unit->getName();
       //     qDebug()<<un->getName();

            bool res=false;
            //Если тип связи RS-485, на одном порте не должно висеть двух юнитов с одинаковыми параметрами

           if(unit==un){


               qDebug()<<"указатели "<<unit->getName()<<" и  "<< un->getName() <<"  ссылаются на один  и тот же обьект";

           }
           else
            {
         if(unit->getUdpUse()==0){
         if((un->getUdpUse()==unit->getUdpUse()))
         if((un->getNum3()==unit->getNum3())) //ищем юниты котрые всият на одном порте с нашим
          res=true;
         }

                    //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

            if(unit->getUdpUse()==1){
         if((un->getUdpUse()==unit->getUdpUse()))
         if((un->getUdpAdress()==unit->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
         if((un->getUdpPort()==unit->getUdpPort()))
         res=true;
         }

         if(res==true)
         if(equal(unit,un))
         {
           this->double_unit_index=modelTreeUN->findeIndexUN(un);

             //this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
            qDebug()<<"Name: "<<un->getName()<<" и "<<unit->getName();un->show();unit->show();
             QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
//             emit double_unit_signal(un);
             return false;
         }
         }

        }



    }


    return true;
}

bool UnitWidget::already_on_the_branch(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
    bool res=false;
    qDebug()<<"[already_on_the_branch]";

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}
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
        if(unit==un){


            qDebug()<<"указатели "<<unit->getName()<<" и  "<< un->getName() <<"  ссылаются на один  и тот же обьект";

        }else{
                qDebug()<<"смотрим: "<<un->getName();

               QModelIndex index=modelTreeUN->findeIndexUN(un);
               QModelIndex un_parent_index= modelTreeUN->parent(index);




             if(ind==un_parent_index) //ищем юнитов с тем же родителем
              {
                 qDebug()<<"[+]";
                 if(un->getType()==unit->getType())
                 if(equal(unit,un))//проверяем не идентичны ли они
                 {
                    this->double_unit_index=modelTreeUN->findeIndexUN(un);
                //     this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
                    qDebug()<<"@@Name: "<<un->getName()<<" и "<<unit->getName();un->show();unit->show();
                     QMessageBox::critical(0,"Ошибка","Такой обьект уже существует!!");
                     res=true;

                 }
              }
        }
    }


    return res;
}

bool UnitWidget::already_in_the_tree(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
    double_unit_index=QModelIndex();
    {

        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
        foreach(UnitNode *un, List1 )
        {

         if(unit!=un)
         if(equal(unit,un))
         {
           this->double_unit_index=modelTreeUN->findeIndexUN(un);

             //this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
            qDebug()<<"Name: "<<un->getName()<<" и "<<unit->getName();un->show();unit->show();
             QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
//             emit double_unit_signal(un);
             return true;
         }
         }

        }






    return false;
}

bool UnitWidget::line_is_busy(UnitNode *unit)
{
    double_unit_index=QModelIndex();
    {
 qDebug()<<"---------------------";
        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN
        foreach(UnitNode *un, List1 )
        {
        //    qDebug()<<"------";
       //     qDebug()<<unit->getName();
       //     qDebug()<<un->getName();

            bool res=false;
            //Если тип связи RS-485, на одном порте не должно висеть двух юнитов с одинаковыми параметрами

           if(unit==un){


               qDebug()<<"указатели "<<unit->getName()<<" и  "<< un->getName() <<"  ссылаются на один  и тот же обьект";

           }
           else

            {
         if(unit->getUdpUse()==0){
             if(neigbors(unit,un))
             if((un->getUdpUse()==unit->getUdpUse()))
             if((un->getNum3()==unit->getNum3())){


                 if((un->getType()==TypeUnitNode::BOD_SOTA)||((un->getType()==TypeUnitNode::BOD_T4K_M)))
                 if((unit->getType()==TypeUnitNode::BOD_SOTA)||((unit->getType()==TypeUnitNode::BOD_T4K_M))){
                     QMessageBox::critical(0,"Ошибка","На линии уже есть БОД ");
                     this->double_unit_index=modelTreeUN->findeIndexUN(un);
                     return true;
                 }

                 if((un->getNum1()==unit->getNum1())){



                     this->double_unit_index=modelTreeUN->findeIndexUN(un);
                     QMessageBox::critical(0,"Ошибка","Адрес занят");
                     return true;

                 }
             }

         }

                    //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

            if(unit->getUdpUse()==1){
                 if(neigbors(unit,un))
                 if((un->getUdpUse()==unit->getUdpUse()))
                 if((un->getUdpAdress()==unit->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
                 if((un->getUdpPort()==unit->getUdpPort())){


                     if((un->getType()==TypeUnitNode::BOD_SOTA)||((un->getType()==TypeUnitNode::BOD_T4K_M)))
                     if((unit->getType()==TypeUnitNode::BOD_SOTA)||((unit->getType()==TypeUnitNode::BOD_T4K_M))){
                         QMessageBox::critical(0,"Ошибка","На линии уже есть БОД ");
                         this->double_unit_index=modelTreeUN->findeIndexUN(un);
                         return true;
                     }

                     if((un->getNum1()==unit->getNum1())){
                         QMessageBox::critical(0,"Ошибка","Адрес занят");
                         this->double_unit_index=modelTreeUN->findeIndexUN(un);
                         return true;

                    }

                 }
         }


         }

        }



    }


    return false;
}

bool UnitWidget::neigbors(UnitNode *unit_one, UnitNode *unit_second)
{
    int one=unit_one->getType();
    int second=unit_second->getType();

    if((one==TypeUnitNode::SD_BL_IP)||(one==TypeUnitNode::IU_BL_IP)){

        if(second==TypeUnitNode::SD_BL_IP)
            return false;

        if(second==TypeUnitNode::IU_BL_IP)
            return false;


    }

    if((one==TypeUnitNode::SSOI_IP_IU)||(one==TypeUnitNode::SSOI_IP_SD)){

        if(second==TypeUnitNode::SSOI_IP_IU)
            return false;

        if(second==TypeUnitNode::SSOI_IP_SD)
            return false;
    }


    if(one==TypeUnitNode::TG){

        if(second==TypeUnitNode::TG)
            return false;



    }

    if(second==TypeUnitNode::SYSTEM)
        return false;

    return true;
}

QString UnitWidget::get_dd(UnitNode *unit)
{
    QModelIndex ind = modelTreeUN->findeIndexUN(unit);
    QModelIndex ind_Y4 = modelTreeUN->parent(ind);
    UnitNode* Y4= static_cast<UnitNode*>(ind_Y4.internalPointer());




    QString str;
    str.clear();
    str.append(QString::number(unit->getNum2()-Y4->getNum2()));
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
         if(timeout_brother(unit,un))//проверяем не идентичны ли они
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
         if(timeout_brother(unit,un))//проверяем не идентичны ли они
          {

             un->setUdpTimeout(val);
          }
        }
    }
}

bool UnitWidget::ip_is_valid(QString ip)
{
    QHostAddress myIP;
       if(myIP.setAddress( ip))
       {
      qDebug()<<"Valid IP Address";
       }
       else
       {
       qDebug()<<"Invalid IP address";

    QMessageBox::critical(0,"Ошибка","Не заданы параметры UDP протокола (IP адрес или порт)");

    return false;
       }
       return true;
}

QString UnitWidget::get_ip_str()
{
    QString ip_str=comm->get_udpAdress();

    QStringList myStringList = ip_str.split(".");

    if(myStringList.count()==4)
    {
        ip_str=myStringList[3];

        if(ip_str.length()<3)
            ip_str="0"+ip_str;

        if(ip_str.length()<3)
            ip_str="0"+ip_str;

        if(ip_str.length()<3)
            ip_str="0"+ip_str;

    }
    else
        ip_str="-IP";

    return ip_str;
}

QModelIndex UnitWidget::getDouble_unit_index()
{
    return this->double_unit_index;
}

void UnitWidget::updateName_slot(int ID)
{
    if(ID==this->ID){
    qDebug()<<m_TypeUnitNode.value(this->getID());
    update_name();
    }
}

void UnitWidget::set_to(UnitNode *unit)
{
  qDebug()<<"UnitWidget::set_option";

}

QString UnitWidget::get_full_string(UnitNode *unit){
    QString str;
    str+="<b>";

    if(unit->getType()==TypeUnitNode::RLM_KRL){
        if(0==unit->getAdamOff()){
        str+=str_RIF_RLM;str.remove(3,1);
        }
        if(1==unit->getAdamOff()){
        str+=str_RIF_RLM_24;str.remove(3,1);
        }
        if(2==unit->getAdamOff()){
        str+=str_RIF_RLM_B;str.remove(3,1);
        }
        if(3==unit->getAdamOff()){
        str+=str_RIF_KRL;str.remove(3,1);
        }
        if(4==unit->getAdamOff()){
        str+=str_Razriv;str.remove(3,1);
        }
        if(5==unit->getAdamOff()){
        str+=str_trassa1l;str.remove(3,1);
        }


    }else{
    str+=m_TypeUnitNode.value(unit->getType());
    }
    str+="</b>";

    if(comm_is_needed){
         if(unit->getUdpUse()){

            str+=" : ";
            str+=unit->getUdpAdress();
            str+="::";
            str+=QString::number(unit->getUdpPort());

            if(unit->getNum1()!=255){
                str+=" : Адрес ";
                int adress=unit->getNum1();
                if(adress<10)
                str+="0";
                str+=QString::number(unit->getNum1());
            }

        }else{


            str+=" : COM"+QString::number(unit->getNum3());


            if(unit->getNum1()!=255){
                str+=" : Адрес ";
                int adress=unit->getNum1();
                if(adress<10)
                str+="0";
                str+=QString::number(unit->getNum1());
            }

            if(unit->getUdpAdress()!=""){
             str+=" ("+ unit->getUdpAdress()+ ")";
            }
        }



    }



    str+=get_string(unit);

 if(comm_is_needed)
     str+=" : Таймаут "+QString::number(unit->getUdpTimeout());


   return str;
}

void UnitWidget::setEnabled(bool val)
{
   comm->setEnabled(val);

   setEnabled_option_menu(val);
}


