#include "widget_adam.h"
#include "ui_widget_adam.h"


Widget_ADAM::Widget_ADAM(QWidget *parent) :
    UnitWidget(parent),
    ui(new Ui::Widget_ADAM)
{
    ID=TypeUnitNode::ADAM;
    ui->setupUi(this);
//Num1
    for(int i=1;i<256;i++){
        QString str;
        str.clear();
        if(i/10<1)
            str.append("0");
        if(i/100<1)
            str.append("0");
        str.append(QString::number(i));
        ui->Num1->addItem(str);
    }
//Num2
    for(int i=0;i<8;i++){
        ui->Num2->addItem(QString::number(i));
    }
}

Widget_ADAM::~Widget_ADAM()
{
    delete ui;
}

void Widget_ADAM::get_option(UnitNode *unit)
{
    if(unit){
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
    ui->Num2->setCurrentText(QString::number(unit->getNum1()));
    setEnabled(false);
    }else{
    setEnabled(true);
    }
}

void Widget_ADAM::set_option(UnitNode *unit)
{

}

void Widget_ADAM::update_name()
{
    QString name;
    name.append("ADAM ");
    name.append(ui->Num1->currentText());
    name.append("-");
    name.append(ui->Num2->currentText());
    emit updateName(name);
}

void Widget_ADAM::setEnabled(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
}

QString Widget_ADAM::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_ADAM::on_Num1_currentIndexChanged(int index)
{
    update_name();
}

void Widget_ADAM::on_Num2_currentIndexChanged(int index)
{
    update_name();
}
