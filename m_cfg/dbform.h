#ifndef DBFORM_H
#define DBFORM_H

#include <QDialog>

namespace Ui {
class DBform;
}

class DBform : public QDialog
{
    Q_OBJECT

public:
    explicit DBform(QWidget *parent = nullptr);
    ~DBform();

private:
    Ui::DBform *ui;
};

#endif // DBFORM_H
