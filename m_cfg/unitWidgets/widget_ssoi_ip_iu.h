#ifndef WIDGET_SSOI_IP_IU_H
#define WIDGET_SSOI_IP_IU_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_SSOI_IP_IU;
}

class Widget_SSOI_IP_IU : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_SSOI_IP_IU(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);

    ~Widget_SSOI_IP_IU();

private:
    Ui::Widget_SSOI_IP_IU *ui;
};

#endif // WIDGET_SSOI_IP_IU_H
