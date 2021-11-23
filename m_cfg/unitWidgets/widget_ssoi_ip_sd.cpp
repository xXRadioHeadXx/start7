#include "widget_ssoi_ip_sd.h"
#include "ui_widget_ssoi_ip_sd.h"

Widget_SSOI_IP_SD::Widget_SSOI_IP_SD(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_SSOI_IP_SD)
{
    ui->setupUi(this);
}

Widget_SSOI_IP_SD::~Widget_SSOI_IP_SD()
{
    delete ui;
}
