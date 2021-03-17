#include "my_doublespinbox.h"
#include <QDebug>
#include <QMenu>
#include <QLineEdit>
#include <QContextMenuEvent>
#include <QtCore>

My_DoubleSpinBox::My_DoubleSpinBox(QWidget *parent)
{
this->setContextMenuPolicy(Qt::DefaultContextMenu);
    this->setMaximum(99999999999999999);
}

void My_DoubleSpinBox::contextMenuEvent(QContextMenuEvent *event)
{
QMenu* menu=this->lineEdit()->createStandardContextMenu();

    for(int i=0;i<menu->actions().count();i++)
    {
    QAction* action=menu->actions().at(i);
    //qDebug()<<i<<" "<<action->text();
    }
    menu->actions().at(0)->setText("Отмена\tCtrl+Z");
    menu->actions().at(1)->setText("Вернуть\tCtrl+Y");
    menu->actions().at(3)->setText("Вырезать\tCtrl+X");
    menu->actions().at(4)->setText("Копировать\tCtrl+C");
    menu->actions().at(5)->setText("Вставить\tCtrl+V");
    menu->actions().at(6)->setText("Удалить");
    menu->actions().at(8)->setText("Выбрать все\tCtrl+A");
//    menu->actions().at(9)->setText("Выбрать все\tCtrl+A");
//    menu->actions().at(10)->setText("Выбрать все\tCtrl+A");
      menu->exec(event->globalPos());
}

