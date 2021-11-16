#include "widget_y4_sota.h"
#include "ui_widget_y4_sota.h"

Widget_Y4_SOTA::Widget_Y4_SOTA(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current ) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_Y4_SOTA)
{
    ID=TypeUnitNode::Y4_SOTA;
    ui->setupUi(this);

    for(int i=1;i<5;i++){
        ui->Num2->addItem(QString::number(i));
    }
}

Widget_Y4_SOTA::~Widget_Y4_SOTA()
{
    delete ui;
}

void Widget_Y4_SOTA::get_from(UnitNode *unit)
{
    ui->Num2->setCurrentText(QString::number(unit->getNum2()/100));
}

void Widget_Y4_SOTA::get_default()
{
    ui->Num2->setCurrentIndex(0);
}



void Widget_Y4_SOTA::set_to(UnitNode *unit)
{
    if(modelTreeUN){
        qDebug()<<"[PROFIT]";

  //      QModelIndex ind=modelTreeUN->findeIndexUN(unit);
  //      QModelIndex parent_ind=modelTreeUN->parent(ind);
  //  UnitNode* parent= static_cast<UnitNode*>(parent_ind.internalPointer());

     if(current->isValid()){

        qDebug()<<"[current->isValid]";

      UnitNode* parent;
      parent = static_cast<UnitNode*>(current->internalPointer());

      if(parent){

        qDebug()<<"[parent->isValid]";
      qDebug()<<parent->getName();


      unit->setNum2(this->ui->Num2->currentText().toInt()*100);

      unit->setNum1(parent->getNum1());
      unit->setNum3(parent->getNum3());

      unit->setUdpUse(parent->getUdpUse());
      unit->setUdpPort(parent->getUdpPort());
      unit->setUdpAdress(parent->getUdpAdress());
      unit->setUdpTimeout(parent->getUdpTimeout());
      }
      }







    }else{
        qDebug()<<"[NULLPTR]";
    }
}

void Widget_Y4_SOTA::update_name()
{
  QString Name;
Name.clear();

UnitNode* parent;
parent = static_cast<UnitNode*>(current->internalPointer());

    if(parent){
        Name.append("БОД");
        if(parent->getNum1()<100)
        Name.append("0");
        Name.append(QString::number(parent->getNum1()));
                    Name.append(" ");
    }
Name.append("Участок ");
Name.append(ui->Num2->currentText());
    emit updateName(Name);

}

void Widget_Y4_SOTA::setEnabled_option_menu(bool val)
{
    ui->Num2->setEnabled(val);
}

QString Widget_Y4_SOTA::get_string(UnitNode *unit)
{
    QString string1;
    QModelIndex ind = this->modelTreeUN->findeIndexUN(unit);
    QModelIndex ind_BOD = this->modelTreeUN->parent(ind);
    UnitNode* BOD= static_cast<UnitNode*>(ind_BOD.internalPointer());



    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Сота/Сота-М</b> ");

    string1.append("Кан:");

    string1.append(QString::number(BOD->getNum3()));

    string1.append(" БОД:");

    string1.append(QString::number(BOD->getNum1()));

    string1.append(" Участок:");

    string1.append(QString::number(unit->getNum2()/100));


   return string1;
}

void Widget_Y4_SOTA::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}
