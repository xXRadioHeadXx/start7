#ifndef AUTHENTICATIONDIALOG_H
#define AUTHENTICATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AuthenticationDialog;
}

struct Operator {
    QString FN;
    QString N1;
    QString N2;
    QString PW;
};

class AuthenticationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenticationDialog(QWidget *parent = nullptr);
    ~AuthenticationDialog();

private:
    Ui::AuthenticationDialog *ui;

    QList<Operator> listUser;

    void initialForm(const QString fileName = "rifx.ini");
};

#endif // AUTHENTICATIONDIALOG_H
