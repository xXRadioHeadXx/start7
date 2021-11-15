#include "coordinatewidget.h"
#include "ui_coordinatewidget.h"

coordinateWidget::coordinateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::coordinateWidget)
{
    ui->setupUi(this);
}

coordinateWidget::~coordinateWidget()
{
    delete ui;
}

void coordinateWidget::get_options(UnitNode *unit)
{
 if(this->isVisible()){


 }
}

void coordinateWidget::set_mode(int mode)
{
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


    break;

    }
}


