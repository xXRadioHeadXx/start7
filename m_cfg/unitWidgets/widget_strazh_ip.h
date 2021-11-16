#ifndef WIDGET_STRAZH_IP_H
#define WIDGET_STRAZH_IP_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_STRAZH_IP;
}

class Widget_STRAZH_IP : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_STRAZH_IP(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr);
    ~Widget_STRAZH_IP();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_STRAZH_IP *ui;
};

#endif // WIDGET_STRAZH_IP_H
