#include "tablo_widget.h"
#include "ui_tablo_widget.h"

TABLO_Widget::TABLO_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TABLO_Widget)
{
    ui->setupUi(this);
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
    return Blinking;
}

void TABLO_Widget::setBlinking(int value)
{
    Blinking = value;
}

void TABLO_Widget::default_options()
{

}
