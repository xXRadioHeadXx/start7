#include "widget_kl.h"
#include "ui_widget_kl.h"

Widget_KL::Widget_KL(QWidget *parent, communicationTypeWidget *comm) :
    UnitWidget(parent,comm),
    ui(new Ui::Widget_KL)
{
    ID=TypeUnitNode::KL;
    ui->setupUi(this);
/*
    for(int i=0;i<100;i++){
        ui->Num1->addItem(QString::number(i));
    }

    for(int i=0;i<4;i++){
        ui->Num2->addItem(QString::number(i));
    }
    */

}

Widget_KL::~Widget_KL()
{
    delete ui;
}

void Widget_KL::get_from(UnitNode *unit)
{

}

void Widget_KL::get_default()
{

}
/*
void Widget_KL::get_option(UnitNode *unit)
{
    comm->setVisible(true);
    comm->get_options(unit,getID());

    if(unit){

        ui->Num1->setCurrentText(QString::number(unit->getNum1()));
        ui->Num2->setCurrentText(QString::number(unit->getNum2()));
        setEnabled(false);
    }else{

        ui->Num1->setCurrentIndex(0);
        ui->Num2->setCurrentText(0);
        setEnabled(true);


    }


}
*/


void Widget_KL::set_option(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
    unit->setNum2(ui->Num2->currentText().toInt());

}

void Widget_KL::update_name()
{
    emit updateName("Группа ");

}

void Widget_KL::setEnabled(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
}

QString Widget_KL::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_KL::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
}
void Widget_KL::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}
