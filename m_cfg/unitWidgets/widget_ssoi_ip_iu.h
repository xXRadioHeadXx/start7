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

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;
    bool timeout_brother(UnitNode *unit,UnitNode* un) override;

    bool accepted(UnitNode* unit) override;
    bool equal(UnitNode* one,UnitNode* secons) override;

    QString get_string(UnitNode* unit) override;

private slots:
    void on_Num1_currentTextChanged(const QString &arg1);

    void on_Num2_currentTextChanged(const QString &arg1);

private:
    Ui::Widget_SSOI_IP_IU *ui;
};

#endif // WIDGET_SSOI_IP_IU_H
