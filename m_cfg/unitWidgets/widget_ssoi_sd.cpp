#include "widget_ssoi_sd.h"
#include "ui_widget_ssoi_sd.h"

Widget_SSOI_SD::Widget_SSOI_SD(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_SSOI_SD)
{
    ID=TypeUnitNode::SSOI_SD;
    ui->setupUi(this);
}

Widget_SSOI_SD::~Widget_SSOI_SD()
{
    delete ui;
}

void Widget_SSOI_SD::get_option(UnitNode *unit)
{

}

void Widget_SSOI_SD::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_SSOI_SD::update_name()
{
    emit updateName("Группа ");

}

void Widget_SSOI_SD::setEnabled(bool val)
{

}

QString Widget_SSOI_SD::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
