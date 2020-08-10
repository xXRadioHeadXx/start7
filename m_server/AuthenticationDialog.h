#ifndef AUTHENTICATIONDIALOG_H
#define AUTHENTICATIONDIALOG_H

#include <QDialog>
#include <Operator.h>

namespace Ui {
class AuthenticationDialog;
}

class AuthenticationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenticationDialog(QWidget *parent = nullptr);
    ~AuthenticationDialog();

    int getInitialResult() const;
    void setInitialResult(int value);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AuthenticationDialog *ui;

    QList<Operator> listUser;
    int initialResult = 0;

    int initialForm(const QString fileName = "rifx.ini");
};

#endif // AUTHENTICATIONDIALOG_H
