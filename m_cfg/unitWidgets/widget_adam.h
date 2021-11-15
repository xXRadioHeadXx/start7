#ifndef WIDGET_ADAM_H
#define WIDGET_ADAM_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_ADAM;
}

class Widget_ADAM : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_ADAM(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr);

    ~Widget_ADAM();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num1_currentIndexChanged(int index);

    void on_Num2_currentIndexChanged(int index);

private:
    Ui::Widget_ADAM *ui;
};

#endif // WIDGET_ADAM_H









