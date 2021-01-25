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

private:
    Ui::SSOIPortWidget *ui;
};

#endif // SSOIPORTWIDGET_H
