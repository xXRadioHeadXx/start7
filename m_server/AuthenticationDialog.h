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
    bool isNull() {
        return FN.isEmpty() && N1.isEmpty() && N2.isEmpty() && PW.isEmpty();
    };
};

class AuthenticationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenticationDialog(QWidget *parent = nullptr);
    ~AuthenticationDialog();


    Operator getApprovedOperator() const;
    void setApprovedOperator(const Operator &value);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AuthenticationDialog *ui;

    QList<Operator> listUser;
    Operator approvedOperator;

    void initialForm(const QString fileName = "rifx.ini");
};

#endif // AUTHENTICATIONDIALOG_H
