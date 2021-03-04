#ifndef MY_DOUBLESPINBOX_H
#define MY_DOUBLESPINBOX_H

#include <QObject>
#include <QWidget>
#include <QDoubleSpinBox>

class My_DoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit My_DoubleSpinBox(QWidget *parent = 0);

   void contextMenuEvent(QContextMenuEvent *event);

signals:

};

#endif // MY_DOUBLESPINBOX_H
