#include "my_lineedit.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>


My_lineEdit::My_lineEdit(QWidget *parent) : QLineEdit(parent)
{

  // this->setContextMenuPolicy(Qt::CustomContextMenu);
}

void My_lineEdit::contextMenuEvent(QContextMenuEvent *event)
{
//qDebug()<<"!!!!!!!!!!!!!!!!!!";
QMenu *menu = this->createStandardContextMenu();

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

  menu->exec(event->globalPos());
}
