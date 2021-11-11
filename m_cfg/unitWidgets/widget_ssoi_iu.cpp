#include "widget_ssoi_iu.h"
#include "ui_widget_ssoi_iu.h"

Widget_SSOI_IU::Widget_SSOI_IU(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_SSOI_IU)
{
    ID=TypeUnitNode::SSOI_IU;
    ui->setupUi(this);
}

Widget_SSOI_IU::~Widget_SSOI_IU()
{
    delete ui;
}

void Widget_SSOI_IU::get_option(UnitNode *unit)
{

}

void Widget_SSOI_IU::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_SSOI_IU::update_name()
{
    emit updateName("Группа ");

}

void Widget_SSOI_IU::setEnabled(bool val)
{

}

QString Widget_SSOI_IU::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
