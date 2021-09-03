#ifndef FINDUNITFORM_H
#define FINDUNITFORM_H

#include <QDialog>

namespace Ui {
class findUnitForm;
}

class findUnitForm : public QDialog
{
    Q_OBJECT

public:
    explicit findUnitForm(QWidget *parent = nullptr);
    ~findUnitForm();

private:
    Ui::findUnitForm *ui;
};

#endif // FINDUNITFORM_H
