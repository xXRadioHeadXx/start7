#include "widget_tg.h"
#include "ui_widget_tg.h"

Widget_TG::Widget_TG(QWidget *parent, communicationTypeWidget *comm) :
    UnitWidget(parent,comm),
    ui(new Ui::Widget_TG)
{
    ID=TypeUnitNode::TG;
    ui->setupUi(this);



}

Widget_TG::~Widget_TG()
{
    delete ui;
}

void Widget_TG::get_from(UnitNode *unit)
{

}

void Widget_TG::get_default()
{

}



void Widget_TG::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_TG::update_name()
{
    emit updateName("Группа ");

}

void Widget_TG::setEnabled(bool val)
{

}

QString Widget_TG::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
