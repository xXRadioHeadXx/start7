#include "widget_iu_bl_ip.h"
#include "ui_widget_iu_bl_ip.h"
#include <QDebug>

Widget_IU_BL_IP::Widget_IU_BL_IP(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_IU_BL_IP)
{
    ID=TypeUnitNode::IU_BL_IP;
    ui->setupUi(this);


}

Widget_IU_BL_IP::~Widget_IU_BL_IP()
{
    delete ui;
}


