#include "tablo_widget.h"
#include "ui_tablo_widget.h"

TABLO_Widget::TABLO_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TABLO_Widget)
{
    ui->setupUi(this);

    this->ui->Port->addItem(" ВЫКЛ"," ВЫКЛ");


     for(int i(1), n(100); i < n; i++)
     {
      //   //qDebug()<<"i= "<<i;
         QString str(" COM%1");
         str = str.arg(i);
         this->ui->Port->addItem(str,str);
     }

    this->default_options();
}

TABLO_Widget::~TABLO_Widget()
{
    delete ui;
}

int TABLO_Widget::getPort() const
{
    return this->ui->Port->currentIndex();
}

void TABLO_Widget::setPort(int val)
{
    this->ui->Port->setCurrentIndex(val);

}

int TABLO_Widget::getBlinking() const
{
   if(this->ui->Blinking->isChecked())
       return 1;
   return 0;
}

void TABLO_Widget::setBlinking(int val)
{
    switch (val)
    {
    case 0:
    this->ui->Blinking->setChecked(false);
    break;

    case 1:
    this->ui->Blinking->setChecked(true);
    break;

    default:
    break;
    }
}

void TABLO_Widget::default_options()
{
    this->ui->Port->setCurrentText(" ВЫКЛ");
    this->ui->Blinking->setChecked(false);
}
