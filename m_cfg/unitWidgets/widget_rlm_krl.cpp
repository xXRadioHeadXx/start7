#include "widget_rlm_krl.h"
#include "ui_widget_rlm_krl.h"

Widget_RLM_KRL::Widget_RLM_KRL(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN) :
    UnitWidget(parent,comm,coord,modelTreeUN),
    ui(new Ui::Widget_RLM_KRL)
{
    ID=TypeUnitNode::RLM_KRL;
    ui->setupUi(this);

    for(int i=1;i<100;i++) {

    ui->Num1->addItem(QString::number(i));
    }

    for(int i=0;i<m_RLM_KRL_type.size();i++)    {
    ui->AdamOff->addItem(m_RLM_KRL_type.value(i));
    }
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

void Widget_RLM_KRL::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_RLM_KRL::on_AdamOff_currentIndexChanged(const QString &arg1)
{
    update_name();
}
