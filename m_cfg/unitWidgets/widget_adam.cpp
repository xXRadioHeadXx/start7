#include "widget_adam.h"
#include "ui_widget_adam.h"
#include <QDebug>


Widget_ADAM::Widget_ADAM(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN) :
    UnitWidget(parent,comm,coord,modelTreeUN),
    ui(new Ui::Widget_ADAM)
{
    ID=TypeUnitNode::ADAM;
    ui->setupUi(this);

//Num1
    for(int i=1;i<256;i++){
    //    QString str;
   //     str.clear();
    //    if(i/10<1)
   //         str.append("0");
    //    if(i/100<1)
     //       str.append("0");
    //    str.append(QString::number(i));
        ui->Num1->addItem(QString::number(i));
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

void Widget_ADAM::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
}

void Widget_ADAM::get_default()
{
ui->Num1->setCurrentIndex(0);
ui->Num2->setCurrentIndex(0);
}
/*
void Widget_ADAM::get_option(UnitNode *unit)
{
    comm->setVisible(false);
    if(unit){
    qDebug()<<"1";
 qDebug()<<QString::number(unit->getNum1());
  qDebug()<<ui->Num1->currentText();



     qDebug()<<QString::number(unit->getNum1());
      qDebug()<<ui->Num1->currentText();


    setEnabled(false);
    }else{
    qDebug()<<"2";
    setEnabled(true);
    }
}
*/

void Widget_ADAM::set_to(UnitNode *unit)
{
unit->setNum1(ui->Num1->currentText().toInt());
unit->setNum2(ui->Num2->currentText().toInt());
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

    string1.append("Адам-406х/4168:");

    if(unit->getNum1()/10<1)
    string1.append("0");
    if(unit->getNum1()/100<1)
    string1.append("0");
    string1.append(QString::number(unit->getNum1()));
    string1.append("-");
    string1.append(QString::number(unit->getNum2()));
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
