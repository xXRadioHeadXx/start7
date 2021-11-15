#include "widget_iu_bl_ip.h"
#include "ui_widget_iu_bl_ip.h"
#include <QDebug>

Widget_IU_BL_IP::Widget_IU_BL_IP(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord) :
    UnitWidget(parent,comm,coord),
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



void Widget_IU_BL_IP::set_option(UnitNode *unit)
{
    comm->set_options(unit);
    unit->setNum1(255);
    unit->setNum2(ui->Num2->currentText().toInt());
}

void Widget_IU_BL_IP::update_name()
{

    QString name;

    name.append("БЛ");


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


    name.append(" ИУ");
    name.append("-");

    //if(this->ui->SD_BL_IP_num_combobox->currentText().toInt()<10)
    //name.append("0");

    name.append(this->ui->Num2->currentText());


  //  updater->updateName(name);
    emit updateName(name);



}

void Widget_IU_BL_IP::setEnabled(bool val)
{
    ui->Num2->setEnabled(val);
    comm->setEnabled(val);
}

QString Widget_IU_BL_IP::get_string(UnitNode *unit)
{

QString str;

str.append("<b>");str.append(m_TypeUnitNode_d.value(unit->getType()));str.append("</b> ");//  БЛ-IP</b> ");
        str.append(": Кан:");


if(unit->getUdpUse()==0)
{
str.append(QString::number(unit->getNum3()));
str.append(" ИУ:");
str.append(QString::number(unit->getNum2()));

if(unit->getUdpAdress()!="")
{
str.append(" ");
str.append("(");
str.append(unit->getUdpAdress());
str.append(")");
}
}
if(unit->getUdpUse()==1)
{
str.append(unit->getUdpAdress());
str.append("::");
str.append(QString::number(unit->getUdpPort()));
str.append(" ");
str.append("ИУ:");
str.append(QString::number(unit->getNum2()));
str.append("\n");
str.append("Таймаут: ");
str.append(QString::number(unit->getUdpTimeout()));
str.append("\n");
}

return str;


}



void Widget_IU_BL_IP::on_Num2_currentIndexChanged(int index)
{
    update_name();
}
