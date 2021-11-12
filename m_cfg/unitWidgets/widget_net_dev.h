#ifndef WIDGET_NET_DEV_H
#define WIDGET_NET_DEV_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_NET_DEV;
}

class Widget_NET_DEV : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_NET_DEV(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr);
    ~Widget_NET_DEV();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_NET_DEV *ui;
};

#endif // WIDGET_NET_DEV_H
