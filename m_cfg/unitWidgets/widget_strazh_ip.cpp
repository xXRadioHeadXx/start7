#include "widget_strazh_ip.h"
#include "ui_widget_strazh_ip.h"

Widget_STRAZH_IP::Widget_STRAZH_IP(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_STRAZH_IP)
{
    ID=TypeUnitNode::STRAZH_IP;
    ui->setupUi(this);
}

Widget_STRAZH_IP::~Widget_STRAZH_IP()
{
    delete ui;
}

void Widget_STRAZH_IP::get_option(UnitNode *unit)
{

}

void Widget_STRAZH_IP::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_STRAZH_IP::update_name()
{
    emit updateName("Группа ");

}

void Widget_STRAZH_IP::enable()
{

}

QString Widget_STRAZH_IP::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
