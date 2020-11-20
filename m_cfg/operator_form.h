#ifndef OPERATOR_FORM_H
#define OPERATOR_FORM_H

#include <QDialog>
#include <QAbstractButton>
#include <QString>

namespace Ui {
class operator_form;
}

class operator_form : public QDialog
{
    Q_OBJECT

public:
    explicit operator_form(QWidget *parent = nullptr);
    ~operator_form();

private slots:


    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::operator_form *ui;

signals:

    void res(QString FN, QString N1, QString N2, QString ps);
};

#endif // OPERATOR_FORM_H
