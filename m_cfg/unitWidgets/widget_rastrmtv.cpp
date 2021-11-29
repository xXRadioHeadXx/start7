#include "widget_rastrmtv.h"
#include "ui_widget_rastrmtv.h"

Widget_RASTRMTV::Widget_RASTRMTV(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current,QMap<QString, SerNum_Name>* mSerNum_Name) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_RASTRMTV)
{
    ID=TypeUnitNode::RASTRMTV;
    this->mSerNum_Name=mSerNum_Name;
    ui->setupUi(this);

    for(int i=1;i<129;i++)
    {
        QString str;
        str.clear();
        if(i/10<1)
            str.append("0");
        str.append(QString::number(i));
        ui->Num3->addItem(str);


    }
}

Widget_RASTRMTV::~Widget_RASTRMTV()
{
    delete ui;
}

void Widget_RASTRMTV::get_from(UnitNode *unit)
{
get_cameras();
ui->Icon1Path->setCurrentText(unit->getIcon1Path());
ui->Num3->setCurrentText(QString::number(unit->getNum3()));


}

void Widget_RASTRMTV::get_default()
{
get_cameras();

ui->Icon1Path->setCurrentText("");
ui->Num3->setCurrentIndex(0);



}



void Widget_RASTRMTV::set_to(UnitNode *unit)
{
unit->setIcon1Path(ui->Icon1Path->currentText());
unit->setNum3(ui->Num3->currentText().toInt());
}

void Widget_RASTRMTV::update_name()
{
    QString Name("Камера-");



    Name.append(this->ui->Num3->currentText());

    emit updateName(Name);

}

void Widget_RASTRMTV::setEnabled_option_menu(bool val)
{
    ui->Icon1Path->setEnabled(val);
    ui->Num3->setEnabled(val);
}

bool Widget_RASTRMTV::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}


    //qDebug()<<"RASTRMTV";
    if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }

    if(unit->getIcon1Path()==""){
        return false;
    }

    return 
!already_on_the_branch(unit,modelTreeUN,current);

}

bool Widget_RASTRMTV::equal(UnitNode *un, UnitNode *unit)
{
    if(un->getType()==unit->getType())
    if(un->getIcon1Path()==unit->getIcon1Path())
    if(un->getNum3()==unit->getNum3())
    return  true;
    return false;
}

QString Widget_RASTRMTV::get_string(UnitNode *unit)
{
    QString str;

    str.append("камера РАСТР-М-ТВ ");
    str.append("\n");
    str.append(unit->getIcon2Path());
    str.append("(");
    str.append(unit->getIcon1Path());
    str.append(")");
    str.append(" - ");
    str.append(QString::number(unit->getNum3()));
   return str;
}

void Widget_RASTRMTV::on_Icon1Path_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_RASTRMTV::on_Num3_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_RASTRMTV::get_cameras()
{
    if(mSerNum_Name){

  foreach(SerNum_Name snn, *mSerNum_Name)    {

      qDebug()<<snn.Name<<" "<<snn.SerNum;
  }

    ui->Icon1Path->clear();


    foreach(SerNum_Name snn, *mSerNum_Name)    {

        QString str;
        str.clear();
        str.append(snn.Name);
        str.append(" (");
        str.append(snn.SerNum);
        str.append(")");
        this->ui->Icon1Path->addItem(str);

    }

}else{
        qDebug()<<"YOU FUCKING FAIL !!!!!";
    }
}
