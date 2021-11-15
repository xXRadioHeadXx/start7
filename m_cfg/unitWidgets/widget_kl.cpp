#include "widget_kl.h"
#include "ui_widget_kl.h"

Widget_KL::Widget_KL(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN) :
    UnitWidget(parent,comm,coord,modelTreeUN),
    ui(new Ui::Widget_KL)
{
    ID=TypeUnitNode::KL;
    ui->setupUi(this);

    comm_is_needed=true;
    coord_mode=coordinateWigget_mode::for_all;


    for(int i=0;i<100;i++){
        ui->Num1->addItem(QString::number(i));
    }

    for(int i=1;i<5;i++){
        ui->Num2->addItem(QString::number(i));
    }


}

Widget_KL::~Widget_KL()
{
    delete ui;
}

void Widget_KL::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
}

void Widget_KL::get_default()
{
    ui->Num1->setCurrentIndex(0);
    ui->Num2->setCurrentIndex(0);
}


void Widget_KL::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
    unit->setNum2(ui->Num2->currentText().toInt());


}

void Widget_KL::update_name()
{
    QString Name;
    Name.append("КЛ-");
    if(this->ui->Num1->currentText().toInt()<10)
    Name.append("0");
    Name.append(this->ui->Num1->currentText());
    Name.append(" СД");
    Name.append(this->ui->Num2->currentText());
    emit updateName(Name);

}

void Widget_KL::setEnabled(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
}

QString Widget_KL::get_string(UnitNode *unit)
{
    QString string1;

    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Концентратор</b> ");
    string1.append(" : ");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");
    string1.append("СД: ");
    string1.append(QString::number(unit->getNum2()));
    string1.append(" ");
    string1.append("Кан: ");

    if(unit->getUdpUse()==0)
    {



   string1.append(QString::number(unit->getNum3()));
   if(unit->getUdpAdress()!="")
   {
       string1.append(" ");
       string1.append("(");
       string1.append(unit->getUdpAdress());
       string1.append(")");
   }


    }

    if(unit->getUdpUse()==1)
    {
        string1.append(unit->getUdpAdress());
        string1.append("::");
        string1.append(QString::number(unit->getUdpPort()));
        string1.append(" ");
        string1.append("\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\n");
    }
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


