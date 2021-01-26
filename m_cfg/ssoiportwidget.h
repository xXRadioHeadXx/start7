#ifndef SSOIPORTWIDGET_H
#define SSOIPORTWIDGET_H

#include <QWidget>

namespace Ui {
class SSOIPortWidget;
}

class SSOIPortWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SSOIPortWidget(QWidget *parent = nullptr);
    ~SSOIPortWidget();

    void set_SsoiMOprosVariant_interface(int i);

    void set_SsoiM_PortNum(int val);
    int  get_SsoiM_PortNum();

    void set_SsoiM_Interval(int val);
    int  get_SsoiM_Interval();

    void set_SsoiM_Interval_(int val);
    int  get_SsoiM_Interval_m();

    void set_SsoiM_MaxErrCnt(int val);
    int  get_SsoiM_MaxErrCnt();

private:
    Ui::SSOIPortWidget *ui;
};

#endif // SSOIPORTWIDGET_H
