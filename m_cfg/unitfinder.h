#ifndef UNITFINDER_H
#define UNITFINDER_H

#include <QWidget>
#include "model_unit_params.h"

namespace Ui {
class UnitFinder;
}

class UnitFinder : public QWidget
{
    Q_OBJECT

public:
    explicit UnitFinder(QWidget *parent = nullptr);
    ~UnitFinder();

private:
    Model_Unit_Params* model;
    Ui::UnitFinder *ui;
};

#endif // UNITFINDER_H
