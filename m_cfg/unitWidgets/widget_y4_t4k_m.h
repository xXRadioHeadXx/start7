#ifndef WIDGET_Y4_T4K_M_H
#define WIDGET_Y4_T4K_M_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_Y4_T4K_M;
}

class Widget_Y4_T4K_M : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_Y4_T4K_M(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr);
    ~Widget_Y4_T4K_M();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_Y4_T4K_M *ui;
};

#endif // WIDGET_Y4_T4K_M_H
