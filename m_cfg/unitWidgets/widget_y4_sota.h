#ifndef WIDGET_Y4_SOTA_H
#define WIDGET_Y4_SOTA_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_Y4_SOTA;
}

class Widget_Y4_SOTA : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_Y4_SOTA(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr);
    ~Widget_Y4_SOTA();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num2_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget_Y4_SOTA *ui;
};

#endif // WIDGET_Y4_SOTA_H
