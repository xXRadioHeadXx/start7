#include "widget_info_tablo.h"
#include "ui_widget_info_tablo.h"
#include <QMessageBox>

Widget_INFO_TABLO::Widget_INFO_TABLO(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_INFO_TABLO)
{
    ID=TypeUnitNode::INFO_TABLO;
    ui->setupUi(this);



    //Num2
    for(int i=1;i<1000;i++){
        QString str;
        if(i/10<1){
        str.append("0");
        }
        if(i/100<1){
         str.append("0");
        }
        str.append(QString::number(i));
        ui->Num2->addItem(str);
    }
}

Widget_INFO_TABLO::~Widget_INFO_TABLO()
{
    delete ui;
}

void Widget_INFO_TABLO::get_from(UnitNode *unit)
{

}

void Widget_INFO_TABLO::get_default()
{

}



void Widget_INFO_TABLO::set_to(UnitNode *unit)
{

}

void Widget_INFO_TABLO::update_name()
{
    QString Name;Name.clear();
    Name.append("Участок: ");
    Name.append(ui->Num2->currentText());
    emit updateName(Name);

}

void Widget_INFO_TABLO::setEnabled_option_menu(bool val)
{

}

bool Widget_INFO_TABLO::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}



    if(parent->getType()!=TypeUnitNode::SSOI_SD)
    {
        QMessageBox::critical(0,"Ошибка"," может быть добавлен только к ССОИ-СД");
        return false;

    }

    if(already_on_the_branch(unit,modelTreeUN,current))
     return false;

    return true;




    return true;

}

bool Widget_INFO_TABLO::equal(UnitNode *one, UnitNode *second)
{
    if(one->getType()==second->getType())
    if(one->getNum2()==second->getNum2())
        return true;

        return false;
}

QString Widget_INFO_TABLO::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_INFO_TABLO::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}
