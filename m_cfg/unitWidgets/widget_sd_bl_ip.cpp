#include "widget_sd_bl_ip.h"
#include "ui_widget_sd_bl_ip.h"

Widget_SD_BL_IP::Widget_SD_BL_IP(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_SD_BL_IP)
{
    ID=TypeUnitNode::SD_BL_IP;
    ui->setupUi(this);
}

Widget_SD_BL_IP::~Widget_SD_BL_IP()
{
    delete ui;
}
