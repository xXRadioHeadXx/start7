#include "widget_rlm_krl.h"
#include "ui_widget_rlm_krl.h"

Widget_RLM_KRL::Widget_RLM_KRL(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN) :
    UnitWidget(parent,comm,coord,modelTreeUN),
    ui(new Ui::Widget_RLM_KRL)
{
    ID=TypeUnitNode::RLM_KRL;
    ui->setupUi(this);
}

Widget_RLM_KRL::~Widget_RLM_KRL()
{
    delete ui;
}

void Widget_RLM_KRL::get_from(UnitNode *unit)
{

}

void Widget_RLM_KRL::get_default()
{

}



void Widget_RLM_KRL::set_to(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_RLM_KRL::update_name()
{
    emit updateName("Группа ");

}

void Widget_RLM_KRL::setEnabled(bool val)
{

}

QString Widget_RLM_KRL::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
