#ifndef SSOIWIDGET_H
#define SSOIWIDGET_H

#include <QWidget>

namespace Ui {
class SSOIwidget;
}

class SSOIwidget : public QWidget
{
    Q_OBJECT

public:
    explicit SSOIwidget(QWidget *parent = nullptr);
    ~SSOIwidget();

    void default_options();

private:
    Ui::SSOIwidget *ui;
};

#endif // SSOIWIDGET_H
