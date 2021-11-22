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


}

void Widget_RASTRMTV::get_default()
{

    qDebug()<<"mSerNum_Name:";

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



void Widget_RASTRMTV::set_to(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_RASTRMTV::update_name()
{
    emit updateName("Группа ");

}

void Widget_RASTRMTV::setEnabled_option_menu(bool val)
{

}

QString Widget_RASTRMTV::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_RASTRMTV::on_Icon1Path_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_RASTRMTV::on_Num3_currentIndexChanged(const QString &arg1)
{
    update_name();
}
