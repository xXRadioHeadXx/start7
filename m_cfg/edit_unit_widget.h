#ifndef EDIT_UNIT_WIDGET_H
#define EDIT_UNIT_WIDGET_H

#include <QDialog>

namespace Ui {
class edit_unit_widget;
}

class edit_unit_widget : public QDialog
{
    Q_OBJECT

public:
    explicit edit_unit_widget(QWidget *parent = nullptr);
    ~edit_unit_widget();

private:
    Ui::edit_unit_widget *ui;
};

#endif // EDIT_UNIT_WIDGET_H
