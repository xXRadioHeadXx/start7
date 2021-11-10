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

}

void Widget_SD_BL_IP::set_option(UnitNode *unit)
{
    qDebug()<<"SD_BL_IP::set_option";

    UnitWidget::set_option(unit);

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


