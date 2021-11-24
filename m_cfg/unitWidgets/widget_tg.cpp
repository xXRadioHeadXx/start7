#include "widget_tg.h"
#include "ui_widget_tg.h"

Widget_TG::Widget_TG(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_TG)
{
    ID=TypeUnitNode::TG;
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

bool Widget_TG::accepted(UnitNode *unit)
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

     return no_equal_unit(unit);

}

bool Widget_TG::equal(UnitNode *origin, UnitNode *current)
{
    if(origin->getType()==current->getType())
    if((origin->getNum1()==current->getNum1()))
    if(origin->getNum2()==current->getNum2())
        return true;
        return false;
}

QString Widget_TG::get_string(UnitNode *unit)
{
    QString string1;

        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Точка/Гарда</b> ");
            string1.append(" : ");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" : ");
    string1.append("ЧЭ: ");
    string1.append(QString::number(unit->getNum2()));
    string1.append("\r\n");
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
        string1.append("\r\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\r\n");
    }
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
