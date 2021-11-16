#include "widget_dd_sota.h"
#include "ui_widget_dd_sota.h"

Widget_DD_SOTA::Widget_DD_SOTA(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_DD_SOTA)
{
    ID=TypeUnitNode::DD_SOTA;
    ui->setupUi(this);

    for(int i=1;i<101;i++){
        ui->Num2->addItem(QString::number(i));
    }
}

Widget_DD_SOTA::~Widget_DD_SOTA()
{
    delete ui;
}

void Widget_DD_SOTA::get_from(UnitNode *unit)
{
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
}

void Widget_DD_SOTA::get_default()
{
ui->Num2->setCurrentIndex(0);
}



void Widget_DD_SOTA::set_to(UnitNode *unit)
{

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());


    int val=parent->getNum2();


    unit->setNum2(this->ui->Num2->currentText().toInt()+val-1);


    unit->setNum1(parent->getNum1());
    unit->setNum3(parent->getNum3());

    unit->setUdpUse(parent->getUdpUse());
    unit->setUdpPort(parent->getUdpPort());
    unit->setUdpAdress(parent->getUdpAdress());
    unit->setUdpTimeout(parent->getUdpTimeout());
}

void Widget_DD_SOTA::update_name()
{
    QString Name;
    Name.clear();

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());


    Name.append(" ДД");
    if(parent){
        Name.append(QString::number(parent->getNum2()/100));
    Name.append("-");
    }
    Name.append(this->ui->Num2->currentText());

    emit updateName(Name);

}

void Widget_DD_SOTA::setEnabled_option_menu(bool val)
{
ui->Num2->setEnabled(val);
}

QString Widget_DD_SOTA::get_string(UnitNode *unit)
{
    QString string1;
    QModelIndex ind = this->modelTreeUN->findeIndexUN(unit);
    QModelIndex ind_Y4 = this->modelTreeUN->parent(ind);
    UnitNode* Y4= static_cast<UnitNode*>(ind_Y4.internalPointer());

    QModelIndex ind_BOD = this->modelTreeUN->parent(ind_Y4);
    UnitNode* BOD= static_cast<UnitNode*>(ind_BOD.internalPointer());



        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Сота/Сота-М</b> ");

    string1.append("Кан:");

    string1.append(QString::number(BOD->getNum3()));

    string1.append(" БОД:");

    string1.append(QString::number(BOD->getNum1()));

    string1.append(" Участок:");

    string1.append(QString::number(Y4->getNum2()/100));

    string1.append(" ДД:");

    string1.append(UnitWidget::get_dd(unit));

   return string1;
}



void Widget_DD_SOTA::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}
