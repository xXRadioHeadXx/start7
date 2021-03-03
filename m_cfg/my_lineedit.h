#ifndef MY_LINEEDIT_H
#define MY_LINEEDIT_H


#include <QLineEdit>
#include <QWidget>
class My_lineEdit : public QLineEdit
{
    Q_OBJECT
public:
    My_lineEdit(QWidget *parent = 0);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

signals:

};

#endif // MY_LINEEDIT_H
