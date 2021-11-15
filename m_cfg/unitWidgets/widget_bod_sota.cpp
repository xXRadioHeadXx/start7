#include "widget_bod_sota.h"
#include "ui_widget_bod_sota.h"

Widget_BOD_SOTA::Widget_BOD_SOTA(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord):
    UnitWidget(parent,comm,coord),
    ui(new Ui::Widget_BOD_SOTA)
{
    ID=TypeUnitNode::BOD_SOTA;
    ui->setupUi(this);
}

Widget_BOD_SOTA::~Widget_BOD_SOTA()
{
    delete ui;
}

void Widget_BOD_SOTA::get_from(UnitNode *unit)
{

}

void Widget_BOD_SOTA::get_default()
{

}



void Widget_BOD_SOTA::set_option(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_BOD_SOTA::update_name()
{
    emit updateName("Группа ");

}

void Widget_BOD_SOTA::setEnabled(bool val)
{

}

QString Widget_BOD_SOTA::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_BOD_SOTA::on_Num1_currentTextChanged(const QString &arg1)
{

}
