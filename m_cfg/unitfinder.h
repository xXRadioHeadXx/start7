#ifndef UNITFINDER_H
#define UNITFINDER_H

#include <QWidget>
#include "model_unit_params.h"
#include <unit_finder_delegate.h>
#include "rif_widget_delegate.h"

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
    unit_finder_delegate* delegate;
    rif_widget_delegate* delegate_1;
    Model_Unit_Params* model;
    Ui::UnitFinder *ui;
};

#endif // UNITFINDER_H
