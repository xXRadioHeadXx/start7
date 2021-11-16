#ifndef WIDGET_BOD_T4K_M_H
#define WIDGET_BOD_T4K_M_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_BOD_T4K_M;
}

class Widget_BOD_T4K_M : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_BOD_T4K_M(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr);

    ~Widget_BOD_T4K_M();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num1_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget_BOD_T4K_M *ui;
};

#endif // WIDGET_BOD_T4K_M_H
