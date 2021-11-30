#include "widget_sd_bl_ip.h"
#include "ui_widget_sd_bl_ip.h"
#include <QDebug>
#include <QMessageBox>

Widget_SD_BL_IP::Widget_SD_BL_IP(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_SD_BL_IP)
{
    ID=TypeUnitNode::SD_BL_IP;
    ui->setupUi(this);
    comm_is_needed=true;
    coord_mode=coordinateWigget_mode::for_all;
    for(int i=0;i<m_SD_BL_IP_OutType.size();i++)
    {
        this->ui->OutType->insertItem(i,m_SD_BL_IP_OutType.value(i));
    }

}

Widget_SD_BL_IP::~Widget_SD_BL_IP()
{
    delete ui;
}

void Widget_SD_BL_IP::get_from(UnitNode *unit)
{
    qDebug()<<"Widget_SD_BL_IP::get_from";
    ui->OutType->setCurrentText(m_SSOI_SD_OutType.value(unit->getOutType()));
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
}

void Widget_SD_BL_IP::get_default()
{
    qDebug()<<"Widget_SD_BL_IP::get_default";
    ui->OutType->setCurrentText(m_SD_BL_IP_OutType.value(0));
    ui->Num2->setCurrentIndex(0);
}



void Widget_SD_BL_IP::set_to(UnitNode *unit)
{




    unit->setNum1(255);
    unit->setNum2(ui->Num2->currentText().toInt());
    //Set OutType
    int key=m_SD_BL_IP_OutType.key(ui->OutType->currentText());

        unit->setOutType(key);
    if(key<8)
    {

        unit->setBazalt(0);
        unit->setConnectBlock(0);
    }
    else if(key==8)
    {

        unit->setBazalt(1);
        unit->setConnectBlock(0);
        unit->setDK(0);
    }


}

void Widget_SD_BL_IP::update_name()
{
    QString name;

    name.append("БЛ");



    //разделить на подстроки через символ точку
    //четвертая подстрока. если менше сотни - ноль; меньше десяти - два нуля

    name.append(UnitWidget::get_ip_str());


    name.append(" СД");
    name.append("-");

    //if(this->ui->SD_BL_IP_num_combobox->currentText().toInt()<10)
    //name.append("0");

    name.append(this->ui->Num2->currentText());


  //  updater->updateName(name);
    emit updateName(name);



}

void Widget_SD_BL_IP::setEnabled_option_menu(bool val)
{
         ui->Num2->setEnabled(val);
         comm->setEnabled(val);
}

bool Widget_SD_BL_IP::timeout_brother(UnitNode *unit,UnitNode *un)
{

    if(un->getType()==TypeUnitNode::SD_BL_IP)
        return true;
    if(un->getType()==TypeUnitNode::IU_BL_IP)
        return true;


    return false;
}

bool Widget_SD_BL_IP::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{


//Куда может быть добавлен

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}
    if((parent->getType()!=TypeUnitNode::GROUP)&&(parent->getType()!=TypeUnitNode::SYSTEM))    {
    QMessageBox::critical(0,"Ошибка","СД может быть добавлен только к группе или к системе");
    return false;

    }
    //Num2 от нуля до восьми
    if(unit->getNum1()!=255){
        QMessageBox::critical(0,"Ошибка","У БЛ IP СД Num1 должен быть равен 255");
        return false;
    }
//Num2 от нуля до восьми
if(unit->getNum2()<0||unit->getNum2()>8){
    QMessageBox::critical(0,"Ошибка","СД - от нуля до восьми!!");
    return false;
}

//Проверка на двойника в дереве
if(already_in_the_tree(unit,modelTreeUN,current))
    return false;



return true;
}

bool Widget_SD_BL_IP::equal(UnitNode *unit, UnitNode *un)
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
    if(un->getType()==unit->getType())
    if(un->getNum2()==unit->getNum2())
    return true;


    return false;
}

QString Widget_SD_BL_IP::get_string(UnitNode *unit)
{
    QString str=" СД";
    str+=QString::number(unit->getNum2());

    if(unit->getBazalt()==1){
        str+=" + ИУ"+QString::number(unit->getNum2());
    }


    if(unit->getBazalt()){
        str+=" "+m_SD_BL_IP_OutType.value(8);
    }else{
        int val = unit->getOutType();
        if(val)
        str+=" "+m_SD_BL_IP_OutType.value(unit->getOutType());
    }
    return str;
}



void Widget_SD_BL_IP::on_Num2_currentIndexChanged(int index)
{




}

void Widget_SD_BL_IP::on_OutType_activated(const QString &arg1)
{
    update_name();
}

void Widget_SD_BL_IP::on_Num2_currentTextChanged(const QString &arg1)
{
    update_name();
    int res=arg1.toInt();



    ui->OutType->clear();
    for(int i=0;i<8;i++)    {
        ui->OutType->insertItem(i,m_SD_BL_IP_OutType.value(i));
    }
    switch(res)
    {
    case 1:
    case 2:
    case 3:
    ui->OutType->insertItem(8,m_SD_BL_IP_OutType.value(8));
    }


}
