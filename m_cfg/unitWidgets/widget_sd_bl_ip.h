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
    explicit Widget_SD_BL_IP(QWidget *parent = nullptr);
    ~Widget_SD_BL_IP();

    virtual void get_option(UnitNode* unit);
    virtual void set_option(UnitNode* unit);
    void update_name() override;
private slots:
    void on_Num2_currentIndexChanged(int index);

    void on_OutType_activated(const QString &arg1);

private:
    Ui::Widget_SD_BL_IP *ui;
};

#endif // WIDGET_SD_BL_IP_H
