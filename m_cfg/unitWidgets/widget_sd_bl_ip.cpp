#include "widget_sd_bl_ip.h"
#include "ui_widget_sd_bl_ip.h"
#include <QDebug>

Widget_SD_BL_IP::Widget_SD_BL_IP(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_SD_BL_IP)
{
    ID=TypeUnitNode::SD_BL_IP;
    ui->setupUi(this);

    for(int i=0;i<m_SSOI_SD_OutType.size();i++)
    {
        this->ui->OutType->insertItem(i,m_SD_BL_IP_OutType.value(i));
    }

}

Widget_SD_BL_IP::~Widget_SD_BL_IP()
{
    delete ui;
}

void Widget_SD_BL_IP::get_option(UnitNode *unit)
{
    qDebug()<<"SD_BL_IP::get_option";
    ui->communicationType->get_options(unit);

    if(unit){
        ui->OutType->setCurrentText(m_SSOI_SD_OutType.value(unit->getOutType()));
        ui->Num2->setCurrentText(QString::number(unit->getNum2()));
        ui->Num2->setEnabled(false);

    }else{
        ui->OutType->setCurrentText(m_SSOI_SD_OutType.value(0));
        ui->Num2->setCurrentIndex(0);
       ui->Num2->setEnabled(true);


    }








}

void Widget_SD_BL_IP::set_option(UnitNode *unit)
{
    qDebug()<<"SD_BL_IP::set_option";

  ui->communicationType->set_options(unit);

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
    qDebug()<<"SD_BL_IP::update_name";
    QString name;

    name.append("БЛ");


    QString ip_str=this->ui->communicationType->get_udpAdress();

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


    name.append(" СД");
    name.append("-");

    //if(this->ui->SD_BL_IP_num_combobox->currentText().toInt()<10)
    //name.append("0");

    name.append(this->ui->Num2->currentText());


  //  updater->updateName(name);
    emit updateName(name);



}

QString Widget_SD_BL_IP::get_string(UnitNode *unit)
{

QString UdpAdress=unit->getUdpAdress();
QString str;
str.append("<b>");str.append(m_TypeUnitNode_d.value(unit->getType()));str.append("</b> ");//  БЛ-IP</b> ");
str.append(" :");
str.append(" СД:");
str.append(QString::number(unit->getNum2()));

if(unit->getBazalt()==1)
{
    str.append(" +");
    str.append(" ИУ:");
    str.append(QString::number(unit->getNum2()));
}

    str.append("\n");
    str.append(" Кан:");

if(unit->getUdpUse()==0)
{
    str.append(QString::number(unit->getNum3()));

if(unit->getUdpAdress()!="")
{
    str.append(" (");
    str.append(unit->getUdpAdress());
    str.append(")");
}
}
if(unit->getUdpUse()==1)
{
    str.append(unit->getUdpAdress());
    str.append("::");
    str.append(QString::number(unit->getUdpPort()));

    str.append("\n");
    str.append("Таймаут: ");
    str.append(QString::number(unit->getUdpTimeout()));
    str.append("\n");
}

    str.append(" ");
if(unit->getBazalt())
{
    str.append(m_SD_BL_IP_OutType.value(8));
}
else
{
    int val = unit->getOutType();
    if(val)
    str.append(m_SD_BL_IP_OutType.value(unit->getOutType()));
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
        ui->OutType->insertItem(i,m_SSOI_SD_OutType.value(i));
    }
    switch(res)
    {
    case 1:
    case 2:
    case 3:
    ui->OutType->insertItem(8,m_SSOI_SD_OutType.value(8));
    }
}
