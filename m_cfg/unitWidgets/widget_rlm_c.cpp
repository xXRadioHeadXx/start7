#include "widget_rlm_c.h"
#include "ui_widget_rlm_c.h"

Widget_RLM_C::Widget_RLM_C(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_RLM_C)
{
    ID=TypeUnitNode::RLM_C;
    ui->setupUi(this);
}

Widget_RLM_C::~Widget_RLM_C()
{
    delete ui;
}

void Widget_RLM_C::get_option(UnitNode *unit)
{

}

void Widget_RLM_C::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_RLM_C::update_name()
{
    emit updateName("Группа ");

}

void Widget_RLM_C::setEnabled(bool val)
{

}

QString Widget_RLM_C::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
