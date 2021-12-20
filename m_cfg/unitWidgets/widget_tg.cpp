#include "widget_tg.h"
#include "ui_widget_tg.h"

Widget_TG::Widget_TG(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_TG)
{
    ID=TypeUnitNode::TG;
    comm_is_needed=true;
        coord_mode=coordinateWigget_mode::for_all;
    ui->setupUi(this);

    for(int i=1;i<101;i++)                         {
        this->ui->Num1->addItem(QString::number(i));
    }

    for(int i=1;i<5;i++)                         {
        this->ui->Num2->addItem(QString::number(i));
    }



}

Widget_TG::~Widget_TG()
{
    delete ui;
}

void Widget_TG::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
}

void Widget_TG::get_default()
{
    ui->Num1->setCurrentIndex(0);
    ui->Num2->setCurrentIndex(0);
}



void Widget_TG::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
    unit->setNum2(ui->Num2->currentText().toInt());
}

void Widget_TG::update_name()
{
    QString Name("Точка-");
    if(this->ui->Num1->currentText().toInt()<10)
    Name.append("0");
    Name.append(this->ui->Num1->currentText());
    Name.append("-ЧЭ");
    Name.append(this->ui->Num2->currentText());

    emit updateName(Name);

}

void Widget_TG::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
}

bool Widget_TG::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}

    //ЧЭ от одного до четырех
      if(unit->getNum2()<0||unit->getNum2()>4)
      {
       //   QMessageBox::critical(0,"Ошибка","ЧЭ от одного до четырех !");
          return false;

      }
    //только к группе
     if((parent->getType()!=TypeUnitNode::GROUP)&&
        (parent->getType()!=TypeUnitNode::SYSTEM)

             )
     {
     //    QMessageBox::critical(0,"Ошибка","устройство Точка/Гарда может быть добавлено только к группе !");
         return false;

     }

     if(already_in_the_tree(unit,modelTreeUN,current))
         return false;

     return true;

}

bool Widget_TG::equal(UnitNode *origin, UnitNode *current)
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
    if(origin->getType()==current->getType())
    if((origin->getNum1()==current->getNum1()))
    if(origin->getNum2()==current->getNum2())
        return true;
        return false;
}

bool Widget_TG::timeout_brother(UnitNode *unit, UnitNode *un){

    if(unit->getType()==un->getType())
    if(unit->getNum1()==un->getNum1())
        return true;

    return false;
     }

QString Widget_TG::get_string(UnitNode *unit)
{
    QString string1;


    string1.append(" : ");
    string1.append("ЧЭ ");
    string1.append(QString::number(unit->getNum2()));



   return string1;
}

void Widget_TG::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_TG::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}
