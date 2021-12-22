#include "widget_ssoi_ip_iu.h"
#include "ui_widget_ssoi_ip_iu.h"
#include <QMessageBox>

Widget_SSOI_IP_IU::Widget_SSOI_IP_IU(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_SSOI_IP_IU)
{
    ID=TypeUnitNode::SSOI_IP_IU;
    ui->setupUi(this);

    for (int i=1;i<100;i++)
        ui->Num1->addItem(QString::number(i));

    for (int i=1;i<4;i++)
        ui->Num2->addItem(QString::number(i));

    comm_is_needed=true;
}

Widget_SSOI_IP_IU::~Widget_SSOI_IP_IU()
{
    delete ui;
}

void Widget_SSOI_IP_IU::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
}

void Widget_SSOI_IP_IU::get_default()
{
    ui->Num1->setCurrentIndex(0);
    ui->Num2->setCurrentIndex(0);
    comm->set_udpTimeout(50*ui->Num1->currentText().toInt());
}

void Widget_SSOI_IP_IU::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
    unit->setNum2(ui->Num2->currentText().toInt());

}

void Widget_SSOI_IP_IU::update_name()
{

    QString name;

    name.append("ССОИ-IP ");


    QString ip_str=comm->get_udpAdress();

    QStringList myStringList = ip_str.split(".");

    if(myStringList.count()==4)
    {
        ip_str=myStringList[3];
        if(ip_str.toInt()<100)
            ip_str="0"+ip_str;
        if(ip_str.toInt()<10)
            ip_str="0"+ip_str;
    }
    else
        ip_str="-IP";

    //разделить на подстроки через символ точку
    //четвертая подстрока. если менше сотни - ноль; меньше десяти - два нуля

    name.append(ip_str);

    name.append("-");
    name.append(ui->Num1->currentText());

    name.append(" ИУ");
  //  name.append(" ");

    //if(this->ui->SD_BL_IP_num_combobox->currentText().toInt()<10)
    //name.append("0");

    name.append(this->ui->Num2->currentText());


  //  updater->updateName(name);
    emit updateName(name);
}

void Widget_SSOI_IP_IU::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
    comm->setEnabled(val);
}

bool Widget_SSOI_IP_IU::timeout_brother(UnitNode *unit,UnitNode *un)
{
    if(un->getType()==TypeUnitNode::SSOI_IP_IU)
        return true;
    if(un->getType()==TypeUnitNode::SSOI_IP_SD)
        return true;


    return false;
}

bool Widget_SSOI_IP_IU::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
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
       (parent->getType()==TypeUnitNode::SSOI_IP_IU)||
        (parent->getType()==TypeUnitNode::ADAM)||
            (parent->getType()==TypeUnitNode::BOD_SOTA)||
            (parent->getType()==TypeUnitNode::BOD_T4K_M)||
            (parent->getType()==TypeUnitNode::Y4_SOTA)||
            (parent->getType()==TypeUnitNode::Y4_T4K_M))
    {

        return false;

    }

    if(unit->getUdpUse()!=1){

        QMessageBox::critical(0,"Ошибка","Только UDP !!!");

        return false;
    }
/*
    if((unit->getUdpPort()!=4001)&&
            (unit->getUdpPort()!=4002)&&
            (unit->getUdpPort()!=4003)&&
            (unit->getUdpPort()!=4004))
        return false;
*/


        //Num2 от нуля до четырех
         if(unit->getNum2()<0||unit->getNum2()>4)
        return false;
//Может повторяться в дереве. Не должен повторяться у одного предка.
         return !UnitWidget::already_on_the_branch(unit,modelTreeUN,current);

}

bool Widget_SSOI_IP_IU::equal(UnitNode *origin, UnitNode *current)
{

if(origin->getType()==current->getType())
if(origin->getNum1()==current->getNum1())
if(origin->getNum2()==current->getNum2())
return true;


return false;
}

QString Widget_SSOI_IP_IU::get_string(UnitNode *unit)
{

    return " : ИУ"+QString::number(unit->getNum2());


}

void Widget_SSOI_IP_IU::on_Num1_currentTextChanged(const QString &arg1)
{
    update_name();
    comm->set_udpTimeout(50*ui->Num1->currentText().toInt());
}

void Widget_SSOI_IP_IU::on_Num2_currentTextChanged(const QString &arg1)
{
    update_name();
}
