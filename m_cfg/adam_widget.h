#ifndef ADAM_WIDGET_H
#define ADAM_WIDGET_H

#include <QWidget>

namespace Ui {
class ADAM_Widget;
}

class ADAM_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit ADAM_Widget(QWidget *parent = nullptr);
    ~ADAM_Widget();

    void default_options();

    int get_Port() const;
    void set_Port(int value);

    int get_Interval() const;
    void set_Interval(int value);

private slots:
    void on_Interval_textChanged(const QString &arg1);

private:
    Ui::ADAM_Widget *ui;
};

#endif // ADAM_WIDGET_H
