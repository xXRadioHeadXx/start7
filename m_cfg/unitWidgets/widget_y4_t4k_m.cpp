#include "widget_y4_t4k_m.h"
#include "ui_widget_y4_t4k_m.h"

Widget_Y4_T4K_M::Widget_Y4_T4K_M(QWidget *parent, communicationTypeWidget *comm) :
    UnitWidget(parent,comm),
    ui(new Ui::Widget_Y4_T4K_M)
{
    ID=TypeUnitNode::Y4_T4K_M;
    ui->setupUi(this);
}

Widget_Y4_T4K_M::~Widget_Y4_T4K_M()
{
    delete ui;
}

void Widget_Y4_T4K_M::get_option(UnitNode *unit)
{

}

void Widget_Y4_T4K_M::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_Y4_T4K_M::update_name()
{
    emit updateName("Группа ");

}

void Widget_Y4_T4K_M::setEnabled(bool val)
{

}

QString Widget_Y4_T4K_M::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
