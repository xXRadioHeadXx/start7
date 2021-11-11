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
    explicit Widget_BOD_T4K_M(QWidget *parent = nullptr);
    ~Widget_BOD_T4K_M();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_BOD_T4K_M *ui;
};

#endif // WIDGET_BOD_T4K_M_H
