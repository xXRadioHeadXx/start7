#ifndef WIDGET_BOD_SOTA_H
#define WIDGET_BOD_SOTA_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_BOD_SOTA;
}

class Widget_BOD_SOTA : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_BOD_SOTA(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr);

    ~Widget_BOD_SOTA();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_BOD_SOTA *ui;
};

#endif // WIDGET_BOD_SOTA_H



