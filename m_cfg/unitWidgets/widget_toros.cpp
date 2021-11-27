#include "widget_toros.h"
#include "ui_widget_toros.h"

Widget_TOROS::Widget_TOROS(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_TOROS)
{
    ID=TypeUnitNode::TOROS;
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

    return no_equal_unit(unit);
}

bool Widget_TOROS::equal(UnitNode *un, UnitNode *unit)
{
    if(un->getType()==unit->getType())
    if(un->getNum1()==unit->getNum1())
        return  true;
        return false;

}

QString Widget_TOROS::get_string(UnitNode *unit)
{
    QString string1;

    string1.append("Торос\n");
    string1.append("Трасса: ");
    string1.append(QString::number(unit->getNum1()));
    string1.append("\n");
    string1.append("Канал: ");
    string1.append(QString::number(unit->getUdpPort()));
    string1.append("\n");
    string1.append("Таймаут: ");
    string1.append(QString::number(unit->getUdpTimeout()));
    string1.append("\n");
   return string1;
}

void Widget_TOROS::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
}
