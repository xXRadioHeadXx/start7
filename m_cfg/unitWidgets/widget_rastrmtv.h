#ifndef WIDGET_RASTRMTV_H
#define WIDGET_RASTRMTV_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_RASTRMTV;
}

class Widget_RASTRMTV : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_RASTRMTV(QWidget *parent = nullptr);
    ~Widget_RASTRMTV();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_RASTRMTV *ui;
};

#endif // WIDGET_RASTRMTV_H
