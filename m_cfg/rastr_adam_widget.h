#ifndef RASTR_ADAM_WIDGET_H
#define RASTR_ADAM_WIDGET_H

#include <QWidget>

namespace Ui {
class RASTR_ADAM_Widget;
}

class RASTR_ADAM_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit RASTR_ADAM_Widget(QWidget *parent = nullptr);
    ~RASTR_ADAM_Widget();

private:
    Ui::RASTR_ADAM_Widget *ui;
};

#endif // RASTR_ADAM_WIDGET_H
