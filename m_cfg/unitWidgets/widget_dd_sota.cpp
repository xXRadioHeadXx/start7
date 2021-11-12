#include "widget_dd_sota.h"
#include "ui_widget_dd_sota.h"

Widget_DD_SOTA::Widget_DD_SOTA(QWidget *parent, communicationTypeWidget *comm) :
    UnitWidget(parent,comm),
    ui(new Ui::Widget_DD_SOTA)
{
    ID=TypeUnitNode::DD_SOTA;
    ui->setupUi(this);
}

Widget_DD_SOTA::~Widget_DD_SOTA()
{
    delete ui;
}

void Widget_DD_SOTA::get_from(UnitNode *unit)
{

}

void Widget_DD_SOTA::get_default()
{

}



void Widget_DD_SOTA::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_DD_SOTA::update_name()
{
    emit updateName("Группа ");

}

void Widget_DD_SOTA::setEnabled(bool val)
{

}

QString Widget_DD_SOTA::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_DD_SOTA::on_Num2_2_currentTextChanged(const QString &arg1)
{
    update_name();
}