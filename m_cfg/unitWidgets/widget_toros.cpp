#include "widget_toros.h"
#include "ui_widget_toros.h"

Widget_TOROS::Widget_TOROS(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_TOROS)
{
    ID=TypeUnitNode::TOROS;
    ui->setupUi(this);
}

Widget_TOROS::~Widget_TOROS()
{
    delete ui;
}

void Widget_TOROS::get_option(UnitNode *unit)
{

}

void Widget_TOROS::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_TOROS::update_name()
{
    emit updateName("Группа ");

}

void Widget_TOROS::setEnabled(bool val)
{

}

QString Widget_TOROS::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
