#include "widget_iu_bl_ip.h"
#include "ui_widget_iu_bl_ip.h"
#include <QDebug>

Widget_IU_BL_IP::Widget_IU_BL_IP(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_IU_BL_IP)
{
    ID=TypeUnitNode::IU_BL_IP;
    ui->setupUi(this);
    comm_is_needed=true;


}

Widget_IU_BL_IP::~Widget_IU_BL_IP()
{
    delete ui;
}

void Widget_IU_BL_IP::get_from(UnitNode *unit)
{
    qDebug()<<"Widget_IU_BL_IP::get_from";
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
}

void Widget_IU_BL_IP::get_default()
{
    qDebug()<<"Widget_IU_BL_IP::get_default";
    ui->Num2->setCurrentIndex(0);
}



void Widget_IU_BL_IP::set_to(UnitNode *unit)
{

    unit->setNum1(255);
    unit->setNum2(ui->Num2->currentText().toInt());
}

void Widget_IU_BL_IP::update_name(){

    QString name="БЛ"+UnitWidget::get_ip_str()+" ИУ"+this->ui->Num2->currentText();



    emit updateName(name);


}

void Widget_IU_BL_IP::setEnabled_option_menu(bool val)
{
    ui->Num2->setEnabled(val);
    comm->setEnabled(val);
}

bool Widget_IU_BL_IP::timeout_brother(UnitNode *unit,UnitNode *un)
{
    if(un->getType()==TypeUnitNode::SD_BL_IP)
        return true;
    if(un->getType()==TypeUnitNode::IU_BL_IP)
        return true;


    return false;
}

bool Widget_IU_BL_IP::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}

    //может быть добавлен к любому датчику группе системе сморти ссои конфигуратор
    if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP)||
       (parent->getType()==TypeUnitNode::ADAM)||

       (parent->getType()==TypeUnitNode::BOD_SOTA)||
       (parent->getType()==TypeUnitNode::BOD_T4K_M)||
       (parent->getType()==TypeUnitNode::Y4_SOTA)||
       (parent->getType()==TypeUnitNode::Y4_T4K_M))
    {

        return false;

    }



        //Num2 от нуля до четырех
         if(unit->getNum2()<0||unit->getNum2()>4)

             return false;
//Может повторяться в дереве. Не должен повторяться у одного предка.
         if(UnitWidget::already_on_the_branch(unit,modelTreeUN,current))
             return false;

         return true;

}

bool Widget_IU_BL_IP::equal(UnitNode *origin, UnitNode *current)
{
    bool res=false;
    if(current->getUdpUse()==0)
    if((origin->getUdpUse()==current->getUdpUse()))
    if((origin->getNum3()==current->getNum3())) //ищем юниты котрые всият на одном порте с нашим
    res=true;
                //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

    if(current->getUdpUse()==1)
    if((origin->getUdpUse()==current->getUdpUse()))
    if((origin->getUdpAdress()==current->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
    if((origin->getUdpPort()==current->getUdpPort()))
    res=true;

    if(res==true)
if(origin->getType()==current->getType())
if(origin->getNum2()==current->getNum2())
return true;


return false;
}

QString Widget_IU_BL_IP::get_string(UnitNode *unit){




return  " : ИУ"+QString::number(unit->getNum2());


}



void Widget_IU_BL_IP::on_Num2_currentIndexChanged(int index)
{
    update_name();
}
