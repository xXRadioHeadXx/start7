#ifndef WIDGET_ONVIF_H
#define WIDGET_ONVIF_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_ONVIF;
}

class Widget_ONVIF : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_ONVIF(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr);
    ~Widget_ONVIF();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_ONVIF_IPaddr_combobox_currentTextChanged(const QString &arg1);

private:
    Ui::Widget_ONVIF *ui;
};

#endif // WIDGET_ONVIF_H
