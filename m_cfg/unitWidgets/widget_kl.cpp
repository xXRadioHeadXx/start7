#include "widget_kl.h"
#include "ui_widget_kl.h"

Widget_KL::Widget_KL(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_KL)
{
    ID=TypeUnitNode::KL;
    ui->setupUi(this);
}

Widget_KL::~Widget_KL()
{
    delete ui;
}

void Widget_KL::get_option(UnitNode *unit)
{

}

void Widget_KL::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_KL::update_name()
{
    emit updateName("Группа ");

}

void Widget_KL::setEnabled(bool val)
{

}

QString Widget_KL::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
