#ifndef ADD_SQL_USER_FORM_H
#define ADD_SQL_USER_FORM_H

#include <QDialog>

namespace Ui {
class add_SQL_user_form;
}

class add_SQL_user_form : public QDialog
{
    Q_OBJECT

public:
    explicit add_SQL_user_form(QWidget *parent = nullptr);
    ~add_SQL_user_form();

private:
    Ui::add_SQL_user_form *ui;
};

#endif // ADD_SQL_USER_FORM_H
