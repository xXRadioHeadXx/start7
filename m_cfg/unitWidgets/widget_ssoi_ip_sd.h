#ifndef WIDGET_SSOI_IP_SD_H
#define WIDGET_SSOI_IP_SD_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>
namespace Ui {
class Widget_SSOI_IP_SD;
}

class Widget_SSOI_IP_SD : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_SSOI_IP_SD(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);

    ~Widget_SSOI_IP_SD();

private:
    Ui::Widget_SSOI_IP_SD *ui;
};

#endif // WIDGET_SSOI_IP_SD_H
