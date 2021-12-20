#include "widget_bod_sota.h"
#include "ui_widget_bod_sota.h"

Widget_BOD_SOTA::Widget_BOD_SOTA(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current):
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_BOD_SOTA)
{
    ID=TypeUnitNode::BOD_SOTA;
    ui->setupUi(this);

    comm_is_needed=true;
    coord_mode=coordinateWigget_mode::for_all;

    for(int i=1;i<100;i++){
    ui->Num1->addItem(QString::number(i));
    }

}

Widget_BOD_SOTA::~Widget_BOD_SOTA()
{
    delete ui;
}

void Widget_BOD_SOTA::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
}

void Widget_BOD_SOTA::get_default()
{
    ui->Num1->setCurrentIndex(0);
}



void Widget_BOD_SOTA::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());




}

void Widget_BOD_SOTA::update_name()
{
    QString Name;
    Name.append("Сота: БОД-");
    if(ui->Num1->currentText().toInt()<10)
    Name.append("0");
    Name.append(ui->Num1->currentText());

    emit updateName(Name);

}

void Widget_BOD_SOTA::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
}

bool Widget_BOD_SOTA::timeout_brother(UnitNode *unit,UnitNode *un)
{
    if(un->getType()==TypeUnitNode::Y4_SOTA)
        return true;
    if(un->getType()==TypeUnitNode::DD_SOTA)
        return true;


    return false;
}

bool Widget_BOD_SOTA::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());
    if(!parent){return false;}

    //БОД может быть добавлен только к группе
    if((parent->getType()!=TypeUnitNode::GROUP)&&
       (parent->getType()!=TypeUnitNode::SYSTEM)
      )
           {
          //     QMessageBox::critical(0,"Ошибка","БОД может быть добавлен только к группе");
               return false;
           }
       //    Если связь по RS485 - контроль по RS485 порту
       //    Если связь по UDP - контроль по IP адресу

    if(already_in_the_tree(unit,modelTreeUN,current))
        return false;

    return true;



}

bool Widget_BOD_SOTA::equal(UnitNode *unit, UnitNode *un)
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
return ((un->getNum1()==unit->getNum1()));

    }

    return false;

}



void Widget_BOD_SOTA::on_Num1_currentTextChanged(const QString &arg1)
{
    update_name();
}


