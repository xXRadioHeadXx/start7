#include "widget_adam.h"
#include "ui_widget_adam.h"


Widget_ADAM::Widget_ADAM(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_ADAM)
{
    ID=TypeUnitNode::ADAM;
    ui->setupUi(this);
}

Widget_ADAM::~Widget_ADAM()
{
    delete ui;
}

void Widget_ADAM::get_option(UnitNode *unit)
{

}

void Widget_ADAM::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_ADAM::update_name()
{
    emit updateName("Группа ");

}

void Widget_ADAM::enable()
{

}

QString Widget_ADAM::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
