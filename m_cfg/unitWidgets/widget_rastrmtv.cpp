#include "widget_rastrmtv.h"
#include "ui_widget_rastrmtv.h"

Widget_RASTRMTV::Widget_RASTRMTV(QWidget *parent, communicationTypeWidget *comm) :
    UnitWidget(parent,comm),
    ui(new Ui::Widget_RASTRMTV)
{
    ID=TypeUnitNode::RASTRMTV;
    ui->setupUi(this);
}

Widget_RASTRMTV::~Widget_RASTRMTV()
{
    delete ui;
}

void Widget_RASTRMTV::get_option(UnitNode *unit)
{

}

void Widget_RASTRMTV::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_RASTRMTV::update_name()
{
    emit updateName("Группа ");

}

void Widget_RASTRMTV::setEnabled(bool val)
{

}

QString Widget_RASTRMTV::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
