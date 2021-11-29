#include "widget_adam.h"
#include "ui_widget_adam.h"
#include <QDebug>
#include <QMessageBox>

Widget_ADAM::Widget_ADAM(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
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


    setEnabled_option_menu(false);
    }else{
    qDebug()<<"2";
    setEnabled_option_menu(true);
    }
}
*/

void Widget_ADAM::set_to(UnitNode *unit)
{
unit->setUdpUse(0);
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

void Widget_ADAM::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
}

bool Widget_ADAM::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
/*
 * Это исполнительное устройство - может быть добавлено в нескольких местах дерева
 * Вход - RS485
 * На выходе 8 реле


 * Два АДАМА сравнивай по след параметрам
 *
 *
 * Num1 - адрес на линии
 * Num2 - номер реле
 *
 *
 *
*/

 //Это устройство висит только на RS485
 //Но это устройство висит на автономной линии - не принимай его во внимание,
 //когда будешь проверять другие устройства на адреса в линии.

int Num1 = unit->getNum1();
if((Num1>255)||
    (Num1<0)){
    QMessageBox::critical(0,"Ошибка","Num1 некорректное значение");
    return false;
}

int Num2 = unit->getNum2();
if((Num2>255)||
    (Num2<0)){
    QMessageBox::critical(0,"Ошибка","Num2 некорректное значение");
    return false;
}

//Куда может быть доабавлен
// АДАМ может быть добавлен ни к чему кроме как
// к любому датчику группе системе сморти ссои конфигуратор
  UnitNode* parent;
  parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}
  if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP)||
       (parent->getType()==TypeUnitNode::ADAM))
        return false;


//В дереве есть двойник? - может появляться несколько раз в дереве
//проверку на двойника в дереве не проводим

//Проверка на двойника в ветке
    if(already_on_the_branch(unit,modelTreeUN,current))
     return false;

    return true;

}

bool Widget_ADAM::equal(UnitNode *one, UnitNode *second)
{
    if(one->getType()==second->getType())
    if(one->getNum1()==second->getNum1())
    if(one->getNum2()==second->getNum2())
    return true;

    return false;
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
