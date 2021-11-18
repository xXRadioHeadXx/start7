#include "widget_y4_t4k_m.h"
#include "ui_widget_y4_t4k_m.h"

Widget_Y4_T4K_M::Widget_Y4_T4K_M(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current ) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_Y4_T4K_M)
{
    ID=TypeUnitNode::Y4_T4K_M;
    ui->setupUi(this);

    for(int i=1;i<5;i++){
        ui->Num2->addItem(QString::number(i));
    }
}

Widget_Y4_T4K_M::~Widget_Y4_T4K_M()
{
    delete ui;
}

void Widget_Y4_T4K_M::get_from(UnitNode *unit)
{
    ui->Num2->setCurrentText(QString::number(unit->getNum2()/100));
}

void Widget_Y4_T4K_M::get_default()
{
    ui->Num2->setCurrentIndex(0);
}



void Widget_Y4_T4K_M::set_to(UnitNode *unit)
{
    if(modelTreeUN){
        qDebug()<<"[PROFIT]";

  //      QModelIndex ind=modelTreeUN->findeIndexUN(unit);
  //      QModelIndex parent_ind=modelTreeUN->parent(ind);
  //  UnitNode* parent= static_cast<UnitNode*>(parent_ind.internalPointer());

     if(current->isValid()){

        qDebug()<<"[current->isValid]";

      UnitNode* parent;
      parent = static_cast<UnitNode*>(current->internalPointer());

      if(parent){

        qDebug()<<"[parent->isValid]";
      qDebug()<<parent->getName();


      unit->setNum2(this->ui->Num2->currentText().toInt()*100);

      unit->setNum1(parent->getNum1());
      unit->setNum3(parent->getNum3());

      unit->setUdpUse(parent->getUdpUse());
      unit->setUdpPort(parent->getUdpPort());
      unit->setUdpAdress(parent->getUdpAdress());
      unit->setUdpTimeout(parent->getUdpTimeout());
      }
      }







    }else{
        qDebug()<<"[NULLPTR]";
    }
}

void Widget_Y4_T4K_M::update_name()
{
  QString Name;
Name.clear();

UnitNode* parent;
parent = static_cast<UnitNode*>(current->internalPointer());

    if(parent){
        Name.append("БОД");
        if(parent->getNum1()<100)
        Name.append("0");
        Name.append(QString::number(parent->getNum1()));
                    Name.append(" ");
    }
Name.append("Участок ");
Name.append(ui->Num2->currentText());
    emit updateName(Name);

}

void Widget_Y4_T4K_M::setEnabled_option_menu(bool val)
{
    ui->Num2->setEnabled(val);
}

bool Widget_Y4_T4K_M::accepted(UnitNode *unit)
{
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());
    //Участок может быть добавлен только к БОД Сота/Сота-М
    if(parent->getType()!=TypeUnitNode::BOD_SOTA)
    {
    //    QMessageBox::critical(0,"Ошибка","Участок может быть добавлен только к БОД Сота/Сота-М!");

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


     if(modelTreeUN->findeIndexUN(parent)==parent_index)
      {
 //       //qDebug()<<"Name: "<<un->getName();
        List.append(un);
      }
    }

    foreach(UnitNode *un, List )
    {
     qDebug()<<"Name: "<<un->getName()<<" и "<<unit->getName();un->show();unit->show();
     if(un->getNum2()==unit->getNum2())
     {
      //   this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));
qDebug()<<"Name: "<<un->getName()<<" и "<<unit->getName();un->show();unit->show();
      //   QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
         return false;
     }
    }
    //проконтролировать в нем отсутствие добавляемого участка

    return true;
}

bool Widget_Y4_T4K_M::equal(UnitNode *unit, UnitNode *un)
{
    bool res=false;
    if(unit->getUdpUse()==0)
    if((un->getUdpUse()==unit->getUdpUse()))
    if((un->getNum3()==unit->getNum3())) //ищем юниты котрые всият на одном порте с нашим
    res=true;
                //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

    if(unit->getUdpUse()==1)
    if((un->getUdpUse()==unit->getUdpUse()))
    if((un->getUdpAdress()==unit->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
    if((un->getUdpPort()==unit->getUdpPort()))
    res=true;

    if(res==true)
    {
           if(un->getType()==unit->getType())
           if(un->getNum1()==unit->getNum1())
           if(un->getNum2()==unit->getNum2())
           if(un->getNum3()==unit->getNum3())
               return true;
    }
    return false;
}

QString Widget_Y4_T4K_M::get_string(UnitNode *unit)
{
    QString string1;
    QModelIndex ind = this->modelTreeUN->findeIndexUN(unit);
    QModelIndex ind_BOD = this->modelTreeUN->parent(ind);
    UnitNode* BOD= static_cast<UnitNode*>(ind_BOD.internalPointer());



    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Сота/Сота-М</b> ");

    string1.append("Кан:");

    string1.append(QString::number(BOD->getNum3()));

    string1.append(" БОД:");

    string1.append(QString::number(BOD->getNum1()));

    string1.append(" Участок:");

    string1.append(QString::number(unit->getNum2()/100));


   return string1;
}

void Widget_Y4_T4K_M::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}
