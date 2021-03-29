#ifndef FIRST_DIALOG_H
#define FIRST_DIALOG_H

#include <QDialog>

namespace Ui {
class First_Dialog;
}

class First_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit First_Dialog(QWidget *parent = nullptr);
    ~First_Dialog();

private:
    Ui::First_Dialog *ui;

signals:
    void rif();
    void ssoi();
private slots:
    void on_pushButton_RIF_clicked();
    void on_pushButton_SSOI_clicked();
};

#endif // FIRST_DIALOG_H
