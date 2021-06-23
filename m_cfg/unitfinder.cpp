#include "unitfinder.h"
#include "ui_unitfinder.h"

UnitFinder::UnitFinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitFinder)
{
    ui->setupUi(this);
}

UnitFinder::~UnitFinder()
{
    delete ui;
}
