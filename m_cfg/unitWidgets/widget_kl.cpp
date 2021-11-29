#include "widget_kl.h"
#include "ui_widget_kl.h"

Widget_KL::Widget_KL(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_KL)
{
    ID=TypeUnitNode::KL;
    ui->setupUi(this);

    comm_is_needed=true;
    coord_mode=coordinateWigget_mode::for_all;


    for(int i=1;i<101;i++){
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

void Widget_KL::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
}

bool Widget_KL::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}

    if(unit->getNum2()<0||unit->getNum2()>4)
    {
//        QMessageBox::critical(0,"Ошибка","СД от одного до четырех !");
        return false;

    }


  // может быть добавлен только к группе
      if(parent->getType()!=TypeUnitNode::GROUP)
      if(parent->getType()!=TypeUnitNode::SYSTEM)
      {
//          QMessageBox::critical(0,"Ошибка"," может быть добавлен только к группе");
          return false;
      }


      //Проверка на двойника в дереве
      if(already_in_the_tree(unit,modelTreeUN,current))
          return false;


    return true;
}

bool Widget_KL::equal(UnitNode *origin, UnitNode *current)
{
    bool res=false;
    if(origin->getUdpUse()==0)
    if((current->getUdpUse()==origin->getUdpUse()))
    if((current->getNum3()==origin->getNum3())) //ищем юниты котрые всият на одном порте с нашим
    res=true;
                //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

    if(origin->getUdpUse()==1)
    if((current->getUdpUse()==origin->getUdpUse()))
    if((current->getUdpAdress()==origin->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
    if((current->getUdpPort()==origin->getUdpPort()))
    res=true;

    if(res==true)
    if(origin->getType()==current->getType()) //если на этом адресе этого порта есть СД - проверить на номер СД
    if(origin->getNum1()==current->getNum1())
    if(origin->getNum2()==current->getNum2())
    return true;
    return false;
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


