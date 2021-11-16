#ifndef WIDGET_IU_BL_IP_H
#define WIDGET_IU_BL_IP_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>
namespace Ui {
class Widget_IU_BL_IP;
}

class Widget_IU_BL_IP : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_IU_BL_IP(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);
    ~Widget_IU_BL_IP();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;

    QString get_string(UnitNode* unit) override;

private slots:
    void on_Num2_currentIndexChanged(int index);

private:
    Ui::Widget_IU_BL_IP *ui;
};

#endif // WIDGET_IU_BL_IP_H
