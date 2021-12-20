#include "widget_toros.h"
#include "ui_widget_toros.h"

Widget_TOROS::Widget_TOROS(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_TOROS)
{
    ID=TypeUnitNode::TOROS;
    comm_is_needed=true;
    coord_mode=coordinateWigget_mode::for_all;
    ui->setupUi(this);

    for(int i=1;i<101;i++)
    {
     /*
    QString str;

    str.clear();

    if(i/10<1)
        str.append("0");
    //if(i/100<1)
    //    str.append("0");
    str.append(QString::number(i));
    */
    ui->Num1->addItem(QString::number(i));


    }
}

Widget_TOROS::~Widget_TOROS()
{
    delete ui;
}

void Widget_TOROS::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
}

void Widget_TOROS::get_default()
{
    ui->Num1->setCurrentIndex(0);
}



void Widget_TOROS::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
}

void Widget_TOROS::update_name()
{
    QString Name("Торос-");
    if(ui->Num1->currentText().toInt()<10)
    Name.append("0");
    Name.append(this->ui->Num1->currentText());
    emit updateName(Name);

}

void Widget_TOROS::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
}

bool Widget_TOROS::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}

    if((parent->getType()!=TypeUnitNode::GROUP)&&(parent->getType()!=TypeUnitNode::SYSTEM))
    {
//        QMessageBox::critical(0,"Ошибка",("может быть добавлен только к группе или к системе"));
//            dialog.exec();
        return false;

    }

    if(already_in_the_tree(unit,modelTreeUN,current))
        return false;

    return true;
}

bool Widget_TOROS::equal(UnitNode *un, UnitNode *unit)
{
    bool res=false;
    if(unit->getUdpUse()==0)
    if((un->getUdpUse()==unit->getUdpUse()))
    if((un->getNum3()==unit->getNum3())) //ищем юниты котрые всият на одном порте с нашим
    res=true;
                //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

    if(unit->getUdpUse()==1)
    if((un->getUdpUse()==unit->getUdpUse()))
    if((un->getUdpAdress()==unit->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
    if((un->getUdpPort()==unit->getUdpPort()))
    res=true;

    if(res==true)
    if(un->getType()==unit->getType())
    if(un->getNum1()==unit->getNum1())
        return  true;
        return false;

}

QString Widget_TOROS::get_string(UnitNode *unit)
{

   return "";
}

void Widget_TOROS::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
}
