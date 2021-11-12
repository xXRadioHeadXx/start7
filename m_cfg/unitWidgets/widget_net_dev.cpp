#include "widget_net_dev.h"
#include "ui_widget_net_dev.h"

Widget_NET_DEV::Widget_NET_DEV(QWidget *parent, communicationTypeWidget *comm) :
    UnitWidget(parent,comm),
    ui(new Ui::Widget_NET_DEV)
{
    ID=TypeUnitNode::NET_DEV;
    ui->setupUi(this);
}

Widget_NET_DEV::~Widget_NET_DEV()
{
    delete ui;
}

void Widget_NET_DEV::get_option(UnitNode *unit)
{

}

void Widget_NET_DEV::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_NET_DEV::update_name()
{
    emit updateName("Группа ");

}

void Widget_NET_DEV::setEnabled(bool val)
{

}

QString Widget_NET_DEV::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
