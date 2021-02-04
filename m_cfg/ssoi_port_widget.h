#ifndef ssoi_port_widget_H
#define ssoi_port_widget_H

#include <QWidget>

namespace Ui {
class ssoi_port_widget;
}

class ssoi_port_widget : public QWidget
{
    Q_OBJECT

public:
    explicit ssoi_port_widget(QWidget *parent = nullptr);
    ~ssoi_port_widget();

    void set_SsoiMOprosVariant_interface(int i);

    void set_SsoiM_PortNum(int val);
    int  get_SsoiM_PortNum();

    void set_SsoiM_Interval(int val);
    int  get_SsoiM_Interval();

    void set_SsoiM_Interval_(int val);
    int  get_SsoiM_Interval_m();

    void set_SsoiM_MaxErrCnt(int val);
    int  get_SsoiM_MaxErrCnt();

    void default_options();

private:
    Ui::ssoi_port_widget *ui;
};

#endif // ssoi_port_widget_H
