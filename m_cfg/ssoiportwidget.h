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

private:
    Ui::SSOIPortWidget *ui;
};

#endif // SSOIPORTWIDGET_H
