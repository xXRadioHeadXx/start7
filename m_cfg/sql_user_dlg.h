#ifndef SQL_USER_DLG_H
#define SQL_USER_DLG_H

#include <QDialog>

namespace Ui {
class sql_User_dlg;
}

class sql_User_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit sql_User_dlg(QWidget *parent = nullptr);
    ~sql_User_dlg();

private:
    Ui::sql_User_dlg *ui;
};

#endif // SQL_USER_DLG_H
