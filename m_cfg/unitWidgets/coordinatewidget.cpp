#include "coordinatewidget.h"
#include "ui_coordinatewidget.h"
#include <QDebug>

coordinateWidget::coordinateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::coordinateWidget)
{
    ui->setupUi(this);

    qDebug()<<"coordinateWidget::coordinateWidget(QWidget *parent)";

    timer = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    timer->setInterval(10); // Задаем интервал таймера
    connect(timer, SIGNAL(timeout()), this, SLOT(update_coordinates())); // Подключаем сигнал таймера к нашему слоту
    timer->start(); // Запускаем таймер
}

coordinateWidget::~coordinateWidget()
{
    delete ui;
}

void coordinateWidget::get_options(UnitNode *unit)
{
 if(this->isVisible()){

     switch (mode) {

     case coordinateWigget_mode::nothing:


     break;

     case coordinateWigget_mode::for_all:

         ui->Lan->setValue(unit?unit->getLan():0);
         ui->Lon->setValue(unit?unit->getLon():0);
         ui->Description->setText(unit?unit->getDescription():"");


     break;

     case coordinateWigget_mode::devline:


         ui->Num2->setValue(unit?unit->getNum2():0);
         ui->Num3->setValue(unit?unit->getNum3():0);
         ui->X->setValue(unit?unit->getX():0);
         ui->Y->setValue(unit?unit->getY():0);


     break;

     }

 }
}

void coordinateWidget::set_options(UnitNode *unit)
{
    this->mode=mode;
    switch (mode) {

    case coordinateWigget_mode::nothing:



    break;

    case coordinateWigget_mode::for_all:

        unit->setLan(ui->Lan->value());
        unit->setLon(ui->Lon->value());
        unit->setDescription(ui->Description->text());

    break;

    case coordinateWigget_mode::devline:

        unit->setNum2(this->ui->Num2->value());
        unit->setNum3(this->ui->Num3->value());
        unit->setX(this->ui->X->value());
        unit->setY(this->ui->Y->value());

    break;

    }
}

void coordinateWidget::set_mode(int mode)
{
    timer->stop();
    this->mode=mode;
    switch (mode) {

        case coordinateWigget_mode::nothing:

                this->setVisible(false);

        break;

    case coordinateWigget_mode::for_all:

        this->setVisible(true);
        this->ui->stack->setCurrentWidget(this->ui->coordinates_for_all);

    break;

    case coordinateWigget_mode::devline:

        this->setVisible(true);
        this->ui->stack->setCurrentWidget(this->ui->devline_coordinates);
        timer->start();


    break;

    }
}

void coordinateWidget::update_coordinates()
{
    QPoint mouseLoc = QCursor::pos();

    ui->mouse_X->setText(QString::number(mouseLoc.x()));
    ui->mouse_Y->setText(QString::number(mouseLoc.y()));

    timer->start(10);
}


