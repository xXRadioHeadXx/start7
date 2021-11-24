#ifndef WIDGET_SD_BL_IP_H
#define WIDGET_SD_BL_IP_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>


namespace Ui {
class Widget_SD_BL_IP;
}

class Widget_SD_BL_IP : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_SD_BL_IP(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);
    ~Widget_SD_BL_IP();

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
    void on_Num2_currentIndexChanged(int index);

    void on_OutType_activated(const QString &arg1);

    void on_Num2_currentTextChanged(const QString &arg1);

private:
    Ui::Widget_SD_BL_IP *ui;
};

#endif // WIDGET_SD_BL_IP_H
