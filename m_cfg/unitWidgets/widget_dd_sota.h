#ifndef WIDGET_DD_SOTA_H
#define WIDGET_DD_SOTA_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_DD_SOTA;
}

class Widget_DD_SOTA : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_DD_SOTA(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr);

    ~Widget_DD_SOTA();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num2_2_currentTextChanged(const QString &arg1);

private:
    Ui::Widget_DD_SOTA *ui;
};


#endif // WIDGET_DD_SOTA_H