#include "adam_widget.h"
#include "ui_adam_widget.h"

ADAM_Widget::ADAM_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ADAM_Widget)
{
    ui->setupUi(this);

    this->ui->Port->addItem(" ВЫКЛ"," ВЫКЛ");
    for(int i(1), n(100); i < n; i++)
    {
     //   qDebug()<<"i= "<<i;
        QString str(" COM%1");
        str = str.arg(i);
        this->ui->Port->addItem(str,str);


    }
    default_options();

}



ADAM_Widget::~ADAM_Widget()
{
    delete ui;
}

void ADAM_Widget::default_options()
{
    this->ui->Port->setCurrentIndex(0);



    this->ui->Interval->setValue(100);

}

int ADAM_Widget::get_Port() const
{
  return this->ui->Port->currentIndex();
}

void ADAM_Widget::set_Port(int value)
{
  this->ui->Port->setCurrentIndex(value);
}

int ADAM_Widget::get_Interval() const
{
    return this->ui->Interval->value();
}

void ADAM_Widget::set_Interval(int value)
{
    this->ui->Interval->setValue(value);
}

void ADAM_Widget::on_Interval_textChanged(const QString &arg1)
{

}
