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

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;
    bool timeout_brother(UnitNode *unit,UnitNode* un) override;

    bool accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr) override;
    bool equal(UnitNode* one,UnitNode* secons) override;

    QString get_string(UnitNode* unit) override;

private slots:
    void on_Num1_currentIndexChanged(const QString &arg1);

    void on_Num2_currentIndexChanged(const QString &arg1);

    void on_OutType_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget_SSOI_IP_SD *ui;
};

#endif // WIDGET_SSOI_IP_SD_H
