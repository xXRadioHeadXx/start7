#ifndef WIDGET_SSOI_SD_H
#define WIDGET_SSOI_SD_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_SSOI_SD;
}

class Widget_SSOI_SD : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_SSOI_SD(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr);
    ~Widget_SSOI_SD();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_SSOI_SD *ui;
};

#endif // WIDGET_SSOI_SD_H
