#include "widget_ssoi_ip_iu.h"
#include "ui_widget_ssoi_ip_iu.h"

Widget_SSOI_IP_IU::Widget_SSOI_IP_IU(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_SSOI_IP_IU)
{
    ui->setupUi(this);
}

Widget_SSOI_IP_IU::~Widget_SSOI_IP_IU()
{
    delete ui;
}
